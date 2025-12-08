#include <stdio.h>
#include <winsock2.h>
#include <process.h>
#pragma comment(lib, "ws2_32.lib")

#define PORT 5000

unsigned __stdcall client_handler(void *arg) {
    SOCKET client = *(SOCKET*)arg;
    free(arg);
    
    char buffer[1024];
    int n = recv(client, buffer, sizeof(buffer)-1, 0);
    
    if (n > 0) {
        buffer[n] = '\0';
        printf("Received:\n%s\n", buffer);
        
        // Simple response
        send(client, "RESULT:42.000000\n", 18, 0);
    }
    
    closesocket(client);
    return 0;
}

int main() {
    WSADATA wsa;
    SOCKET server;
    struct sockaddr_in addr;
    
    WSAStartup(MAKEWORD(2,2), &wsa);
    
    server = socket(AF_INET, SOCK_STREAM, 0);
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;
    
    bind(server, (struct sockaddr*)&addr, sizeof(addr));
    listen(server, 5);
    
    printf("Simple Server listening on port %d...\n", PORT);
    
    while (1) {
        SOCKET *client = malloc(sizeof(SOCKET));
        *client = accept(server, NULL, NULL);
        printf("New connection accepted\n");
        _beginthreadex(NULL, 0, client_handler, client, 0, NULL);
    }
    
    closesocket(server);
    WSACleanup();
    return 0;
}