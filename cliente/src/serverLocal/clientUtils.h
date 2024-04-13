#ifndef _CLIENT_UTILS_H_
#define _CLIENT_UTILS_H_

#include <stdio.h>

// Copiar esto cada vez que se necesite usar sockets, para tener compatibilidad entre windows y linux
#if defined(_WIN32) || defined(_WIN64)
    #include <winsock2.h>
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
#endif

#pragma comment(lib, "ws2_32.lib")

// Funcion para crear un socket cliente
SOCKET crearSocketCliente();

// Funcion para conectar el socket del cliente al servidor local
void conectarServer(SOCKET s, const char *ip, int port);

// Función para recibir datos del servidor
int recibirServer(SOCKET s, char *buffer, int bufferSize);

// Funcion para cerrar el socket cliente
void cerrarSocketCliente(SOCKET s);

#endif