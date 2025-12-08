/**
 * C TCP Client for Calculation System - WORKING VERSION
 * Task 3 - Member 3 (M3)
 * Fix: Proper string handling and protocol formatting
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

// Clear input buffer
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;
    char num1[50], num2[50], op[10];
    char request[BUFFER_SIZE];
    char response[BUFFER_SIZE];
    
    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed: %d\n", WSAGetLastError());
        return 1;
    }
    printf("[✓] Winsock initialized\n");
    
    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Socket creation failed: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    printf("[✓] Socket created\n");
    
    // Setup server address
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &server.sin_addr);
    
    // Connect to server
    printf("[•] Connecting to %s:%d...\n", SERVER_IP, SERVER_PORT);
    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
        printf("[✗] Connection failed: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    printf("[✓] Connected to server\n");
    
    // Set receive timeout (3 seconds)
    DWORD timeout = 3000;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
    
    // Get user input - USING scanf FOR SAFETY
    printf("\n--- ENTER CALCULATION ---\n");
    
    printf("First number: ");
    if (scanf("%49s", num1) != 1) {
        printf("[✗] Invalid input for first number\n");
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    clear_input_buffer();
    
    printf("Second number: ");
    if (scanf("%49s", num2) != 1) {
        printf("[✗] Invalid input for second number\n");
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    clear_input_buffer();
    
    printf("Operator (+, -, *, /): ");
    if (scanf("%9s", op) != 1) {
        printf("[✗] Invalid input for operator\n");
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    clear_input_buffer();
    
    // DEBUG: Show what we got
    printf("\n[DEBUG] Got: num1='%s', num2='%s', op='%s'\n", num1, num2, op);
    
    // Build request - SIMPLE AND SAFE
    sprintf(request, "NUMBER:%s\nNUMBER:%s\nOPERATOR:%s\n", num1, num2, op);
    
    printf("\n[DEBUG] Request (%d bytes):\n%s", (int)strlen(request), request);
    
    printf("=== DEBUG PROTOCOL DUMP ===\n");
    printf("Bytes to send: %d\n", (int)strlen(request));
    printf("Hex dump:\n");
    for(int i = 0; i < strlen(request); i++) {
      printf("%02X ", (unsigned char)request[i]);
      if(request[i] == '\n') printf(" [LF]\n");
      else if(request[i] == '\r') printf(" [CR]");
  }
      printf("\n=== END DUMP ===\n\n");

    // Send request
    printf("\n--- SENDING REQUEST ---\n");
    
    int bytes_sent = send(sock, request, strlen(request), 0);
    if (bytes_sent == SOCKET_ERROR) {
        printf("[✗] Send failed: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    printf("[✓] Sent %d bytes\n", bytes_sent);
    
    // Receive response
    printf("\n--- SERVER RESPONSE ---\n");
    
    memset(response, 0, sizeof(response));
    int bytes_received = recv(sock, response, sizeof(response) - 1, 0);
    
    if (bytes_received > 0) {
        response[bytes_received] = '\0';
        printf("Server: %s\n", response);
    } else if (bytes_received == 0) {
        printf("[!] Server closed connection\n");
    } else {
        int error = WSAGetLastError();
        if (error == WSAETIMEDOUT) {
            printf("[!] Timeout: Server did not respond\n");
            printf("[!] Server received: %s", request);
        } else {
            printf("[✗] Receive error: %d\n", error);
        }
    }
    
    // Cleanup
    closesocket(sock);
    WSACleanup();
    
    printf("\nPress Enter to exit...");
    getchar();
    
    return 0;
}