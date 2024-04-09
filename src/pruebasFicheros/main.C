 #include <stdio.h>
#include <stdlib.h>

#define INTER "Traducciones/internacional.txt"
#define AMER "Traducciones/americano.txt"

int main(){
    //Matriz alfabeto:
    /* [A][.][-]...
       [B][-][-]...
       [C][.][.]...
       [D][.][-]...
       [E][.][.]...
    */

    char *alfabeto[26];

    //FICHERO
    FILE *archivo;
    archivo = fopen(AMER, "r");
    if(archivo == NULL){
        perror("ERROR 404: No se ha podido encontrar el archivo");
        return 1;
    }
    int fila = 0;
    int col = 0;
    char c;
    int size = 0;
    int i = 0;
    while((c = fgetc(archivo)) != EOF){
        //printf("%c\n", c);
        if(c == ' ' || c == ':'){
            continue;
        }else if(c != '\n'){
            size ++;
        }else if(c == '\n'){
            alfabeto[i] = (char*)malloc((size+1)*sizeof(char));
            //printf("Tamaño para fila %d: %d\n", i, size+1);
            i++;
            //printf("%i\n", i);
            size = 0;
        }
    }
    //Para guardar memoria cuando llegue al final del fichero porque el anterior solo se ejecuta cuando llega a \n
    alfabeto[i] = (char*)malloc((size+1)*sizeof(char));
    //fclose(archivo);
    
    fila = 0;
    col = 0;
    fseek(archivo, 0, SEEK_SET); //Para volver arriba del fichero porque en el anterior bucle
    //ya se ha llegado al final
    while((c = fgetc(archivo))!= EOF){
        if(c == ':' || c == ' '){
            continue;
        }
        else if(c == '\n'){
            alfabeto[fila][col] = '\0';
            printf("Tamaño de la fila %d: %d\n", fila, col);
            fila++;
            col = 0;
        }
        else if(c == '_'){
            alfabeto[fila][col] = ' ';
            col++;
        }
        else{
            alfabeto[fila][col] = c;
            printf("Guardado en alfabeto[%d][%d]: %c\n", fila, col, c);
            col++;
        }
    }
    fseek(archivo, 0, SEEK_SET);
    //printf("Datos guardados en la matriz\n");


    fclose(archivo);
    for(int i = 0; i<26; i++){
        printf("%s\n", alfabeto[i]);
    }

    for(int i = 0; i<26; i++){
        free(alfabeto[i]);
    }

}