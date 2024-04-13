#ifndef _SERVER_UTILS_H_
#define _SERVER__UTILS_H_

#include <stdio.h>

// Copiar esto cada vez que se necesite usar sockets, para tener compatibilidad entre windows y linux
#if defined(_WIN32) || defined(_WIN64)
    #include <winsock2.h>
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
#endif

#pragma comment(lib, "ws2_32.lib")

// Función para crear un socket del servidor
SOCKET crearSocketServer();

// Función para enlazar un socket del servidor al puerto especificado
void enlazarServerSocket(SOCKET s, int port);

// Función para escuchar conexiones en un socket del servidor
void entrarEnEscucha(SOCKET s, int backlog);

// Función para aceptar una conexión entrante
SOCKET aceptarConexion(SOCKET s);

// Función para enviar un mensaje a un cliente
void enviarCliente(SOCKET clientSocket, const char *message);

// Función para cerrar el socket del servidor
void cerrarSocketServer(SOCKET s);

#endif