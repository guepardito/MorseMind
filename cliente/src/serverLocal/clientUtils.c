#include <stdio.h>

// Copiar esto cada vez que se necesite usar sockets, para tener compatibilidad entre windows y linux
#if defined(_WIN32) || defined(_WIN64)
    #include <winsock2.h>
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
#endif

#pragma comment(lib, "ws2_32.lib")

#include "clientUtils.h"


SOCKET crearSocketCliente() {
    SOCKET s;
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET) {
        printf("No se pudo crear el socket. Código de error: %d\n", WSAGetLastError());
        WSACleanup();
        exit(1);
    }
    return s;
}

void conectarServer(SOCKET s, const char *ip, int port) {
    struct sockaddr_in server;
    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Error de conexión.\n");
        closesocket(s);
        WSACleanup();
        exit(1);
    }
}

int recibirServer(SOCKET s, char *buffer, int bufferSize) {
    int recv_size;
    recv_size = recv(s, buffer, bufferSize, 0);
    if (recv_size == SOCKET_ERROR) {
        printf("Recv fallido. Código de error: %d\n", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        exit(1);
    }
    return recv_size;
}

void cerrarSocketCliente(SOCKET s) {
    closesocket(s);
    WSACleanup();
}
