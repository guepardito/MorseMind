#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#include <unistd.h>
//#include <arpa/inet.h>

#include "pruebaCliente.h"

#pragma comment(lib, "ws2_32.lib")
 
#define PORT 8080
#define SERVER_ADDR "192.168.1.16" // Dirección IP de tu Raspberry Pi
// servidor.c

#define PORT 8080
/*
int main(void){
    WSADATA wsa; 
    SOCKET sock;
    struct sockaddr_in server;
    int creado= crearSocket(wsa, sock, server);
    char* morse= "....... ......";
    int mandado= mandarMensaje(morse,sock);
    cerrarSocket(sock);

}*/