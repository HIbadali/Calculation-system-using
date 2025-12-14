#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <process.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER_PORT 5000

unsigned __stdcall client_thread(void *arg) {
    SOCKET client = (SOCKET)arg;

    char buffer[2048];
    int n = recv(client, buffer, sizeof(buffer)-1, 0);
    if (n <= 0) { closesocket(client); return 0; }

    buffer[n] = '\0';
    printf("\n[SERVER RAW RECEIVED]\n%s\n", buffer);

    double a, b;
    char op;

    // Accepte \n ou \r\n
    if (sscanf(buffer,
        "NUMBER:%lf%*[\r\n]"
        "NUMBER:%lf%*[\r\n]"
        "OPERATOR:%c",
        &a, &b, &op) != 3)
    {
        send(client, "ERROR:Invalid format\n", 22, 0);
        shutdown(client, SD_BOTH);
        closesocket(client);
        return 0;
    }

    if (op == '/' && b == 0) {
        send(client, "ERROR:Division by zero\n", 24, 0);
        shutdown(client, SD_BOTH);
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
            shutdown(client, SD_BOTH);
            closesocket(client);
            return 0;
    }

    char msg[64];
    sprintf(msg, "RESULT:%lf\n", result);
    send(client, msg, (int)strlen(msg), 0);

    printf("[SERVER SENT] %s\n", msg);

    shutdown(client, SD_BOTH);
    closesocket(client);
    return 0;
}

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    SOCKET server = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERVER_PORT);
    addr.sin_addr.s_addr = inet_addr("192.168.197.216");

    bind(server, (struct sockaddr*)&addr, sizeof(addr));
    listen(server, 10);

    printf("Server listening on port %d...\n", SERVER_PORT);

    while (1) {
        SOCKET client = accept(server, NULL, NULL);
        printf("New client accepted.\n");
        _beginthreadex(NULL, 0, client_thread, (void*)client, 0, NULL);
    }

    closesocket(server);
    WSACleanup();
    return 0;
}
