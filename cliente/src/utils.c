
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "time.h"

//#define INTER "Traducciones/internacional.txt"  //1
//#define AMER "Traducciones/americano.txt"       //2



void exportarEstadisticas(float porcentaje, int partidas){
    
    FILE* f1;
    int c1;
    f1=fopen("Estadisticas/Estadisticas.txt", "r");
    if(f1 == NULL){
        printf("Error 403");
        return;
    }
    int num_lines=0;
    while ((c1 = fgetc(f1)) != EOF)
    {
        if (c1 == '\n')
            num_lines++; 
  
        printf("%c", c1);
    }
    fclose(f1);


    if(num_lines==0){
        FILE* f2;

        f2 = fopen("Estadisticas/Estadisticas.txt", "w");
        if(f2 == NULL){
            printf("Error 403");
            return;
        }
        fprintf(f2, "         T U S  E S T A D I S T I C A S          \n");
        fprintf(f2, "=================================================\n\n");
        fprintf(f2, "Porcentaje de aciertos: %.2f%%\n", porcentaje);
        fprintf(f2, "Numero de partidas jugadas: %i\n", partidas);
        time_t tiempo_actual = time(NULL);
        struct tm *hora_local = localtime(&tiempo_actual);
        fprintf(f2, "Fecha: %i\n", asctime(hora_local));
                
        fclose(f2);
    }
    else{
        FILE* f3;
        f3 = fopen("Estadisticas/Estadisticas.txt", "a");
        if(f3 == NULL){
            printf("Error 403");
            return;
        }
        fprintf(f3, "         T U S  E S T A D I S T I C A S          \n");
        fprintf(f3, "=================================================\n\n");
        fprintf(f3, "Porcentaje de aciertos: %.2f%%\n", porcentaje);
        fprintf(f3, "Numero de partidas jugadas: %i\n", partidas);
        
        time_t tiempo_actual = time(NULL);
        struct tm *hora_local = localtime(&tiempo_actual);
        fprintf(f3, "Fecha: %i\n", asctime(hora_local));
                
        fclose(f3);
    }
}


