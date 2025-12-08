#define _WIN32_WINNT 0x0601
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <process.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER_PORT 5000
#define MAX_LINE 1024
#define LOG_FILE "server.log"

HANDLE logMutex;

// Get timestamp
void get_timestamp(char *buf, size_t size) {
    SYSTEMTIME st;
    GetLocalTime(&st);
    snprintf(buf, size, "%04d-%02d-%02d %02d:%02d:%02d",
             st.wYear, st.wMonth, st.wDay,
             st.wHour, st.wMinute, st.wSecond);
}

// Thread-safe logging
void log_message(const char *client_ip, const char *message) {
    char timestamp[64];
    get_timestamp(timestamp, sizeof(timestamp));

    WaitForSingleObject(logMutex, INFINITE);
    FILE *f = fopen(LOG_FILE, "a");
    if (f) {
        fprintf(f, "[%s] [%s] %s\n", timestamp, client_ip, message);
        fclose(f);
    }
    ReleaseMutex(logMutex);
}

// Thread function
unsigned __stdcall client_thread(void *arg) {
    SOCKET client = *(SOCKET*)arg;
    free(arg);

    char buffer1[MAX_LINE], buffer2[MAX_LINE], buffer3[MAX_LINE];
    char client_ip[INET_ADDRSTRLEN];
    char logbuf[512];

    struct sockaddr_in client_addr;
    int addr_len = sizeof(client_addr);
    getpeername(client, (struct sockaddr*)&client_addr, &addr_len);

    inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip));

    sprintf(logbuf, "New connection from %s", client_ip);
    log_message(client_ip, logbuf);

    int n;

    // Read 3 lines
    n = recv(client, buffer1, sizeof(buffer1)-1, 0);
    buffer1[n] = 0;

    n = recv(client, buffer2, sizeof(buffer2)-1, 0);
    buffer2[n] = 0;

    n = recv(client, buffer3, sizeof(buffer3)-1, 0);
    buffer3[n] = 0;

    sprintf(logbuf, "Request:\n %s\n %s\n %s", buffer1, buffer2, buffer3);
    log_message(client_ip, logbuf);

    // Parse
    double a,b;
    char op;

    if (strncmp(buffer1, "NUMBER:", 7) != 0 ||
        strncmp(buffer2, "NUMBER:", 7) != 0 ||
        strncmp(buffer3, "OPERATOR:", 9) != 0) {

        send(client, "ERROR:Invalid format\n", 22, 0);
        closesocket(client);
        return 0;
    }

    a = atof(buffer1+7);
    b = atof(buffer2+7);
    op = buffer3[9];

    if (op=='/' && b==0) {
        send(client, "ERROR:Division by zero\n", 24, 0);
        closesocket(client);
        return 0;
    }

    double result;
    switch(op) {
        case '+': result = a+b; break;
        case '-': result = a-b; break;
        case '*': result = a*b; break;
        case '/': result = a/b; break;
        default:
            send(client, "ERROR:Invalid operator\n", 23, 0);
            closesocket(client);
            return 0;
    }

    char result_msg[128];
    sprintf(result_msg, "RESULT:%lf\n", result);
    send(client, result_msg, strlen(result_msg), 0);

    sprintf(logbuf, "Result sent: %s", result_msg);
    log_message(client_ip, logbuf);

    closesocket(client);
    return 0;
}

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    logMutex = CreateMutex(NULL, FALSE, NULL);

    SOCKET server = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERVER_PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(server, (struct sockaddr*)&addr, sizeof(addr));
    listen(server, 10);

    printf("Server listening on port %d...\n", SERVER_PORT);

    while (1) {
        SOCKET *client = malloc(sizeof(SOCKET));
        *client = accept(server, NULL, NULL);

        _beginthreadex(NULL, 0, client_thread, client, 0, NULL);
    }

    closesocket(server);
    WSACleanup();
    return 0;
}
