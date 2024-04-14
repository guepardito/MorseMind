#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

typedef struct {
    char server_ip[100];
    char server_port[100];
    char admin_user[100];
    char admin_password[100];
    char database_path[100];
} AppConfig;

void load_config(const char *filename, AppConfig *config) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open config file");
        return;
    }

    char key[100], value[100];
    while (fscanf(file, "%s %s", key, value) == 2) {
        if (strcmp(key, "server_ip") == 0) {
            strncpy(config->server_ip, value, 100);
        } else if (strcmp(key, "server_port") == 0) {
            strncpy(config->server_port, value, 100);
        } else if (strcmp(key, "admin_user") == 0) {
            strncpy(config->admin_user, value, 100);
        } else if (strcmp(key, "admin_password") == 0) {
            strncpy(config->admin_password, value, 100);
        } else if (strcmp(key, "database_path") == 0) {
            strncpy(config->database_path, value, 100);
        }
    }
    fclose(file);
}

int mainServidor() {
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct sockaddr_in clientService;
    AppConfig config = {0};
    char recvbuf[512];
    int recvbuflen = 512;

    load_config("config.txt", &config);

    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }

    ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ConnectSocket == INVALID_SOCKET) {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    memset(&clientService, 0, sizeof(clientService));
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr(config.server_ip);
    clientService.sin_port = htons(atoi(config.server_port));

    if (connect(ConnectSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
        printf("Failed to connect.\n");
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    printf("Connected to server.\n");
    printf("Admin User: %s\n", config.admin_user);
    printf("Using database at: %s\n", config.database_path);


    do {
        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0) {
            printf("Bytes received: %d\n", iResult);
        } else if (iResult == 0)
            printf("Connection closed\n");
        else
            printf("recv failed with error: %d\n", WSAGetLastError());
    } while (iResult > 0);

    closesocket(ConnectSocket);
    WSACleanup();
    return 0;
}
