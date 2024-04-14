
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "time.h"

//#define INTER "Traducciones/internacional.txt"  //1
//#define AMER "Traducciones/americano.txt"       //2


int exportarEstadisticas(float porcentaje, int partidas){
    int error = 0;
    FILE* f1;
    int c1;
    int num_lines=0;
    f1=fopen("Estadisticas/Estadisticas.txt", "r");
    if(f1 == NULL){
        //printf("No se ha podido encontrar el archivo\n");
        f1=fopen("Estadisticas/Estadisticas.txt", "w");
        //error = 1;
        fclose(f1);
        //return error;
    }
    while ((c1 = fgetc(f1)) != EOF)
    {
        if (c1 == '\n')
            num_lines++; 
    }
    fclose(f1);


    if(num_lines==0){
        FILE* f2;

        f2 = fopen("Estadisticas/Estadisticas.txt", "w");
        if(f2 == NULL){
            printf("No se ha podido encontrar el archivo\n");
            error = 1;
            return error;
        }
        fprintf(f2, "         T U S  E S T A D I S T I C A S          \n");
        fprintf(f2, "=================================================\n\n");
        time_t tiempo_actual = time(NULL);
        struct tm *hora_local = localtime(&tiempo_actual);
        fprintf(f2, "FECHA: %s", asctime(hora_local));
        fprintf(f2, "-----------------------------------\n");
        fprintf(f2, "\t Porcentaje de aciertos: %.2f%%\n", porcentaje);
        fprintf(f2, "\t Numero de partidas jugadas: %i\n\n\n", partidas);
        
        fclose(f2);
    }
    else{
        FILE* f3;
        f3 = fopen("Estadisticas/Estadisticas.txt", "a");
        if(f3 == NULL){
            printf("No se ha podido encontrar el archivo\n");
            error = 1;
            return error;
        }
        
        time_t tiempo_actual = time(NULL);
        struct tm *hora_local = localtime(&tiempo_actual);
        fprintf(f3, "FECHA: %s", asctime(hora_local));
        fprintf(f3, "-----------------------------------\n");
        fprintf(f3, "\t Porcentaje de aciertos: %.2f%%\n", porcentaje);
        fprintf(f3, "\t Numero de partidas jugadas: %i\n\n\n", partidas);
                
        fclose(f3);
    }
}


