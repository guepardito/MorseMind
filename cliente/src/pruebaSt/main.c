#include <stdio.h>
#include "pruebaStatemt.h"

int main(void)
{
    conectarBaseDeDatos();  
    Partida p;

    p.Fecha = "JD";
    p.ID_Morse = 1;
    p.ID_Palabra = 2;
    p.ID_Usuario = 567;
    p.Resultado = "acertado";
    
    // Crear la partida y obtener el ID
    int id = crearPartida(p);
    printf("ID de la nueva partida: %i\n", id);

    // Leer la partida usando el ID obtenido
    Partida *p2 = leerPartida(id);  // Aquí usamos el ID devuelto por crearPartida

    if(p2 != NULL && p2->ID_Partida == id){
        printf("La partida con ID %i ha sido creada y leída correctamente.\n", id);
    } else {
        printf("Error al leer la partida con ID %i.\n", id);
    }

    if(id == p2->ID_Partida){
      printf("Miercoles de Jesus\n");
    }
    
    if(p2 != NULL) {
        printf("ID 2: %i\n", p2->ID_Partida);
    }

    desconectarBaseDeDatos();
    
    return 0;
}
