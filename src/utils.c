#include "utils.h"
#include <stdio.h>

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

