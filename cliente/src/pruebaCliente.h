#ifndef _PRUEBACLIENTE_H_
#define _PRUEBACLIENTE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define PORT 8080
#define SERVER_ADDR "10.207.0.42"

int crearSocket(WSADATA wsa, SOCKET *sock, struct sockaddr_in *server);
int mandarMensaje(char* morse, SOCKET sock);
int cerrarSocket(SOCKET sock);


#endif