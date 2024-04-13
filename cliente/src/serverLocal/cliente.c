#include <stdio.h>

// Copiar esto cada vez que se necesite usar sockets, para tener compatibilidad entre windows y linux
#if defined(_WIN32) || defined(_WIN64)
    #include <winsock2.h>
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
#endif

#pragma comment(lib, "ws2_32.lib")

#define SERVER_IP "127.0.0.1" // Cambiar a la IP del servidor si es necesario
#define SERVER_PORT 8888       // Puerto en el que el servidor está escuchando

int main() {
    WSADATA wsa;
    SOCKET socketCliente;
    char server_reply[2000];
    int recv_size;

    // Inicializar Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Fallo al inicializar Winsock. Código de error: %d\n", WSAGetLastError());
        return 1;
    }

    // Crear socket del cliente
    socketCliente = crearSocketCliente();

    // Conectar el socket del cliente al servidor remoto
    conectarServer(socketCliente, SERVER_IP, SERVER_PORT);

    printf("Conectado al servidor %s en el puerto %d.\n", SERVER_IP, SERVER_PORT);

    // Recibir datos del servidor
    if ((recv_size = recibirServer(socketCliente, server_reply, sizeof(server_reply))) == SOCKET_ERROR) {
        printf("Recv fallido. Código de error: %d\n", WSAGetLastError());
        cerrarSocketCliente(socketCliente);
        return 1;
    }

    // Mostrar los datos recibidos del servidor
    printf("Respuesta del servidor: %.*s", recv_size, server_reply);

    // Cerrar el socket del cliente
    cerrarSocketCliente(socketCliente);

    return 0;
}
