#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(5000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Connexion au serveur...\n");
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Erreur de connexion.\n");
        return 1;
    }

    printf("Connecté.\n");

    // On envoie les 3 lignes
    send(sock, "NUMBER:10\n", 10, 0);
    send(sock, "NUMBER:5\n", 9, 0);
    send(sock, "OPERATOR:+\n", 11, 0);

    // On lit la réponse du serveur
    char buffer[1024];
    int n = recv(sock, buffer, sizeof(buffer)-1, 0);
    buffer[n] = 0;

    printf("Réponse du serveur : %s\n", buffer);

    closesocket(sock);
    WSACleanup();
    return 0;
}
