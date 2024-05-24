#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include "string.h"

#include "ws2811.h"
#include "morse.h"
#include "version.h"
#include "rpihw.h"
#include "pwm.h"
#include "pcm.h"

#include "gpio.h"
#include "dma.h"
#include "mailbox.h"
#include "clk.h"

#define PORT 8080

/*extern "C" {
    void display_ganar();
    void display_perder();
    void display_morse_string(char* morse_string);
}*/

#define WIDTH 8
#define HEIGHT 8
#define LED_COUNT (WIDTH * HEIGHT)

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    socklen_t addrlen = sizeof(address);
    char buffer[1024] = {0};
    const char *verificacion = "Mensaje recibido correctamente";
    int valread;

    // Crear el socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Configurar opciones del socket
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Asignar dirección y puerto al socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Escuchar en el socket
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    std::cout << "Servidor esperando conexiones..." << std::endl;

    while(1){
      // Aceptar conexión entrante
      if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) < 0) {
          perror("accept");
          exit(EXIT_FAILURE);
      }
      std::cout << "Conexión aceptada." << std::endl;
  
      // Leer datos del cliente
      if ((valread = recv(new_socket, buffer, 1024, 0)) < 0) {
          perror("recv");
          exit(EXIT_FAILURE);
      }
      std::cout << "Mensaje del cliente: " << buffer << std::endl; // en vez de mandar esto, llamar a leds
      
      
      if (strcmp(buffer,"1")==0){
        display_ganar();
      }
      else if (strcmp(buffer,"0")==0){
        display_perder();
      }
      else if (strcmp(buffer,"2")==0){
        display_apagar();
      }
      else{
        display_morse_string(buffer);
      }
      
  
      // Enviar el mensaje de verificación al cliente
      send(new_socket, verificacion, strlen(verificacion), 0);
      std::cout << "Mensaje enviado al cliente: " << verificacion << std::endl;
  
      // Limpiar el buffer después de procesar el mensaje
      memset(buffer, 0, sizeof(buffer));
  
      // Cerrar el socket de la conexión cuando se termina de leer
      close(new_socket);
      std::cout << "Conexión cerrada." << std::endl;
    }

    close(server_fd);
    
    return 0;
}