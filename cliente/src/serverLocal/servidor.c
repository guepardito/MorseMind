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


#define PORT 8888
#define MSG_SIZE 1024
#define REPLY_SIZE 65536

int main() {
    WSADATA wsa;
    SOCKET serverSocket, clientSocket;
    char *message = "200 | Conexion realizada con exito\n";

    // Inicializar Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Fallo al iniciar Winsock. Codigo de error: %d\n", WSAGetLastError());
        return 1;
    }

    serverSocket = crearSocketServer();

    enlazarServerSocket(serverSocket, PORT);

    entrarEnEscucha(serverSocket, SOMAXCONN);

    printf("Servidor escuchando en el puerto %d...\n", PORT);

    while (1) {
        // Aceptar conexión entrante
        clientSocket = aceptarConexion(serverSocket);
        printf("Cliente conectado.\n");

        enviarCliente(clientSocket, message);

        closesocket(clientSocket);
    }

    // Cerrar el socket del servidor
    cerrarSocketServer(serverSocket);

    return 0;
}