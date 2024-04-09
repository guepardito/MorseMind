#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

//#define INTER "Traducciones/internacional.txt"  //1
//#define AMER "Traducciones/americano.txt"       //2



void exportarEstadisticas(float porcentaje, int partidas, float media){
    FILE* f;
    int c;

    f = fopen("nombreArchivo.txt", "w");
    if(f == NULL){
        printf("Error 403");
        return;
    }
    fprintf(f, "Porcentaje de aciertos: %.2f\n", porcentaje);
    fprintf(f, "Numero de partidas jugadas: %i\n", partidas);
    fprintf(f, "Media de intentos: %.2f\n", media);
            
    fclose(f);
}


