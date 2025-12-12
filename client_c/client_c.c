/**
 * C TCP Client for Calculation System 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 5000
#define BUFFER_SIZE 1024

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;
    char request[BUFFER_SIZE];
    char response[BUFFER_SIZE];
    
    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }
    
    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Socket creation failed\n");
        WSACleanup();
        return 1;
    }
    
    // Setup server address
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    
    // Connect to server
    printf("Connecting to server...\n");
    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
        printf("Connection failed\n");
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    printf("Connected!\n");
    
    // Set timeout
    DWORD timeout = 5000;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
    
    
    // Build request with Windows line endings
    sprintf(request, "NUMBER:100\r\nNUMBER:50\r\nOPERATOR:+\r\n");
    // =========================================
    
    printf("\n=== DEBUG PROTOCOL DUMP ===\n");
    printf("Hex dump of request:\n");
    for(int i = 0; i < strlen(request); i++) {
        printf("%02X ", (unsigned char)request[i]);
        if(request[i] == '\n') printf(" [LF]\n");
        else if(request[i] == '\r') printf(" [CR]");
    }
    printf("\n=== END DUMP ===\n");
    
    // Send request
    printf("\n=== SENDING REQUEST ===\n");
    int bytes_sent = send(sock, request, strlen(request), 0);
    printf("Sent %d bytes\n", bytes_sent);
    
    // Receive response
    printf("\n=== SERVER RESPONSE ===\n");
    memset(response, 0, sizeof(response));
    int bytes_received = recv(sock, response, sizeof(response) - 1, 0);
    
    if (bytes_received > 0) {
        response[bytes_received] = '\0';
        printf("Server: %s\n", response);
    } else if (bytes_received == 0) {
        printf("Server closed connection\n");
    } else {
        int error = WSAGetLastError();
        if (error == WSAETIMEDOUT) {
            printf("Timeout: Server did not respond\n");
        } else {
            printf("Receive error: %d\n", error);
        }
    }
    
    closesocket(sock);
    WSACleanup();
    
    printf("\nPress Enter to exit...");
    getchar();
    
    return 0;
}