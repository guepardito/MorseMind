#include <stdio.h>

// Copiar esto cada vez que se necesite usar sockets, para tener compatibilidad entre windows y linux
#if defined(_WIN32) || defined(_WIN64)
    #include <winsock2.h>
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
#endif

#pragma comment(lib, "ws2_32.lib")

#include "serverUtils.h"

SOCKET crearSocketServer() {
    SOCKET s;
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET) {
        printf("No se pudo crear el socket. Codigo de error: %d", WSAGetLastError());
        WSACleanup();
        exit(1);
    }
    return s;
}

void enlazarServerSocket(SOCKET s, int port) {
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    if (bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Bind fallido. Codigo de error: %d", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        exit(1);
    }
}

void entrarEnEscucha(SOCKET s, int backlog) {
    listen(s, backlog);
}

SOCKET aceptarConexion(SOCKET s) {
    SOCKET new_socket;
    struct sockaddr_in client;
    int c = sizeof(struct sockaddr_in);

    new_socket = accept(s, (struct sockaddr *)&client, &c);
    if (new_socket == INVALID_SOCKET) {
        printf("Accept fallido. Codigo de error: %d", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        exit(1);
    }
    return new_socket;
}

void enviarCliente(SOCKET clientSocket, const char *message) {
    send(clientSocket, message, strlen(message), 0);
}

void cerrarSocketServer(SOCKET s) {
    closesocket(s);
    WSACleanup();
}
