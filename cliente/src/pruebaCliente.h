#ifndef _PRUEBACLIENTE_H_
#define _PRUEBACLIENTE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define PORT 8080
#define SERVER_ADDR "192.168.1.16"

int crearSocket(WSADATA wsa, SOCKET *sock, struct sockaddr_in *server);
int mandarMensaje(char* morse, SOCKET sock);
int cerrarSocket(SOCKET sock);


#endif