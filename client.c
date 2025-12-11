#include <stdio.h>
#include <winsock2.h>
#include <stdlib.h>
#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        printf("Erreur de création du socket\n");
        return 1;
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(5000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Connexion au serveur...\n");

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Erreur de connexion.\n");
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    printf("Connecté.\n");

    // ENVOI DES LIGNES
    send(sock, "NUMBER:10\n", strlen("NUMBER:10\n"), 0);
    send(sock, "NUMBER:5\n", strlen("NUMBER:5\n"), 0);
    send(sock, "OPERATOR:+\n", strlen("OPERATOR:+\n"), 0);

    // RÉCEPTION DU SERVEUR
    char buffer[1024];
    int n = recv(sock, buffer, sizeof(buffer)-1, 0);

    if (n <= 0) {
        printf("Aucune réponse du serveur.\n");
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    buffer[n] = '\0';

    // AFFICHAGE DE LA RÉPONSE
    printf("\nRéponse brute du serveur (%d octets):\n%s\n", n, buffer);

    closesocket(sock);
    WSACleanup();
    return 0;
}
