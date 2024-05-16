#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define SERVER_ADDR "192.168.1.16" // Dirección IP de tu Raspberry Pi

int crearSocket(WSADATA wsa, SOCKET *sock, struct sockaddr_in *server) {
    printf("Inicializando Winsock...\n");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Error al iniciar Winsock: %d\n", WSAGetLastError());
        return 1;
    }

    printf("Creando socket...\n");
    if ((*sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("No se pudo crear el socket: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA...\n");
    server->sin_addr.s_addr = inet_addr(SERVER_ADDR);
    server->sin_family = AF_INET;
    server->sin_port = htons(PORT);

    printf("Conectando al servidor...\n");
    if (connect(*sock, (struct sockaddr *)server, sizeof(*server)) < 0) {
        printf("Error al conectar con el servidor: %d\n", WSAGetLastError());
        closesocket(*sock);
        WSACleanup();
        return 1;
    }

    printf("Conectado al servidor\n");
    return 0;
}

char* mandarMensaje(char* morse, SOCKET sock) {
    char server_reply[2000];
    int recv_size;

    if (send(sock, morse, strlen(morse), 0) < 0) {
        printf("Fallo al enviar el mensaje\n");
        return NULL;
    }

    printf("Mensaje enviado: %s\n", morse);

    if ((recv_size = recv(sock, server_reply, 2000, 0)) == SOCKET_ERROR) {
        printf("Error al recibir respuesta\n");
        return NULL;
    } else {
        server_reply[recv_size] = '\0';
        printf("Respuesta del servidor: %s\n", server_reply);
        return server_reply;
    }
}

void cerrarSocket(SOCKET sock) {
    closesocket(sock);
    WSACleanup();
}
/*
int main() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;
    char morse[1000];
    char jolines[1000];

    // Inicializar Winsock y crear el socket
    if (crearSocket(wsa, &sock, &server) != 0) {
        return 1;
    }

    // Ejemplo de uso: Mandar un mensaje y recibir la respuesta
    strcpy(morse, "Mensaje de prueba");
    char *respuesta = mandarMensaje(morse, sock);
    
    if (respuesta != NULL) {
        printf("Respuesta recibida: %s\n", respuesta);
    }

    // Cerrar el socket y limpiar Winsock
    cerrarSocket(sock);

    return 0;
}*/
