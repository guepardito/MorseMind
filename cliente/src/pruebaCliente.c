#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
//#define SERVER_ADDR "10.207.0.42" // Dirección IP de tu Raspberry Pi

int crearSocket(WSADATA wsa, SOCKET *sock, struct sockaddr_in *server) {
    char ip_address[16];
    obtener_ip_serv(ip_address, sizeof(ip_address));
    #define SERVER_ADDR ip_address;
    //printf("Inicializando Winsock...\n");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("ERROR: No se ha podido conectar con el servidor\n");
        //printf("Error al iniciar Winsock: %d\n", WSAGetLastError());
        return 1;
    }

    //printf("Creando socket...\n");
    if ((*sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("ERROR: No se ha podido conectar con el servidor\n");
        //printf("No se pudo crear el socket: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    server->sin_addr.s_addr = inet_addr(ip_address);
    server->sin_family = AF_INET;
    server->sin_port = htons(PORT);

    //printf("Conectando al servidor...\n");
    if (connect(*sock, (struct sockaddr *)server, sizeof(*server)) < 0) {
        printf("ERROR: No se ha podido conectar con el servidor\n");
        //printf("Error al conectar con el servidor: %d\n", WSAGetLastError());
        closesocket(*sock);
        WSACleanup();
        return 1;
    }

    //printf("Conectado al servidor\n");
    return 0;
}

char* mandarMensaje(char* morse, SOCKET sock) {
    char server_reply[2000]; // Cambiado de char *server_reply[2000] a char server_reply[2000]
    int recv_size;

    if (send(sock, morse, strlen(morse), 0) < 0) {
        //printf("Fallo al enviar el mensaje\n");
        return NULL;
    }

    //printf("Mensaje enviado: %s\n", morse);

    if ((recv_size = recv(sock, server_reply, 2000, 0)) == SOCKET_ERROR) {
        //printf("Error al recibir respuesta\n");
        return NULL;
    } else {
        server_reply[recv_size] = '\0';
        //printf("Respuesta del servidor: %s\n", server_reply);
        return strdup(server_reply); //Copiar y devolver la respuesta utilizando strdup para evitar problemas de puntero
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

void obtener_ip_serv(char *ip_buffer, size_t buffer_size)
{
    FILE *file = fopen("config.txt", "r");
    if (file == NULL)
    {
        perror("Failed to open config file");
        exit(EXIT_FAILURE);
    }

    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        if (strncmp(line, "IP=", 3) == 0)
        {
            strncpy(ip_buffer, line + 3, buffer_size - 1);
            char *newline = strchr(ip_buffer, '\n');
            if (newline)
            {
                *newline = '\0';
            }
            break;
        }
    }

    fclose(file);
}