#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
 
#pragma comment(lib, "ws2_32.lib")
 
#define PORT 8080
#define SERVER_ADDR "192.168.1.16" // Dirección IP de tu Raspberry Pi
 
int main() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;
    char message[1000], server_reply[2000];
    int recv_size;
 
    printf("Inicializando Winsock...\n");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Error al iniciar Winsock: %d\n", WSAGetLastError());
        return 1;
    }
 
    printf("Creando socket...\n");
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("No se pudo crear el socket: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
 
    server.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
 
    printf("Conectando al servidor...\n");
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Error al conectar con el servidor: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }
 
    printf("Conectado al servidor\n");
 
    const char *hola = "Hola servidor";
    if (send(sock, hola, strlen(hola), 0) < 0) {
        printf("Fallo al enviar el mensaje\n");
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    printf("Mensaje enviado\n");
 
    if ((recv_size = recv(sock, server_reply, 2000, 0)) == SOCKET_ERROR) {
        printf("Error al recibir respuesta\n");
    } else {
        server_reply[recv_size] = '\0';
        printf("Respuesta del servidor: %s\n", server_reply);
    }
 
    closesocket(sock);
    WSACleanup();
 
    return 0;
}
