#include <stdio.h>
#include <stdlib.h>
#include "pantallas.h"
#include <string.h>
#include "utils.h"
#include <ctype.h>

char **alfabeto;

void crearAlf() {
    alfabeto = (char**) malloc(26* sizeof(char*));
}

void logo()
{
    printf("=================================================\n");
    printf("___  ___                   ___  ____           _ \n");
    printf("|  \\/  |                   |  \\/  (_)         | |\n");
    printf("| .  . | ___  _ __ ___  ___| .  . |_ _ __   __| |\n");
    printf("| |\\/| |/ _ \\| '__/ __|/ _ \\ |\\/| | | '_ \\ / _` |\n");
    printf("| |  | | (_) | |  \\__ \\  __/ |  | | | | | | (_| |\n");
    printf("\\_|  |_/\\___/|_|  |___/\\___\\_|  |_/_|_| |_|\\__,_|\n");
    printf("=================================================\n");
}

void cerrar()
{
    exit(-1);
}

void pantalla1()
{
    crearAlf();
    system("cls");
    logo();
    printf("                  I N I C I O                    \n");
    printf("=================================================\n");
    printf("1. Registro\n");
    printf("2. LogIn\n");
    printf("3. Cerrar\n");
    char opc[2];
    printf("Introduzca la opcion deseada:");
    scanf("%s", opc);
    if (*opc == '1')
    {
        pantalla11();
    }
    else if (*opc == '2')
    {
        pantalla12();
    }
    else
    {
        pantalla64();
    }
}

void pantalla11()
{
    system("cls");
    logo();
    printf("                R E G I S T R O                  \n");
    printf("=================================================\n");

    char nombre[15];
    printf("Nombre: ");
    scanf("%s", nombre);

    char apellido[25];
    printf("Apellido: ");
    scanf("%s", apellido);

    char nick[15];
    printf("Nickname: ");
    scanf("%s", nick);

    char contrasena[20];
    printf("Contrasena: ");
    scanf("%s", contrasena);

    char contrasenaNue[20];
    printf("Repite la contrasena: ");
    scanf("%s", contrasenaNue);

    if (strlen(nombre) != 0 && strlen(apellido) != 0 && strlen(nick) != 0 && strlen(contrasena) != 0 && strlen(contrasenaNue) != 0 && strcmp(contrasena, contrasenaNue) == 0) 
    {
        printf("Hola, %s. Has sido registrado correctamente!\n", nick);
        char opc[2];
        printf("Pulsa cualquier tecla para continuar: ");
        scanf("%s", opc);
        pantalla1();
    }
    else
    {
        printf("No has podido ser registrado. Quieres volver a intentarlo? \n");
        printf("1. Si\n");
        printf("2. No\n");
        char opc[2];
        printf("Introduzca la opcion deseada:");
        scanf("%s", opc);
        if (*opc == '1')
        {
            pantalla11();
        }
        else if (*opc == '2')
        {
            pantalla1();
        }
    }
}

void pantalla12()
{
    system("cls");
    logo();
    printf("                  L O G  I N                     \n");
    printf("=================================================\n");

    char nick[15];
    printf("Nickname: ");
    scanf("%s", nick);

    char contrasena[25];
    printf("Contrasena: ");
    scanf("%s", contrasena);

    pantalla2(); // esto está para hacer pruebas, cuando conectemos a la BD, quitar!
    /*
    if (aquí hay que comprobar con la base de datos)
    {
        pantalla2(); //a lo mejor tambien tenemos que pasarle el usuario como parámetro
    }else{
        printf("No has podido iniciar sesion. Quieres volver a intentarlo? \n");
        printf("1. Si\n");
        printf("2. No\n");
        char opc[2];
        printf("Introduzca la opcion deseada:");
        scanf("%s", opc);
        if (*opc == '1')
        {
            pantalla12();
        }
        else if (*opc == '2')
        {
            pantalla1();
        }
    }
    */
}

void pantalla2()
{
    system("cls");
    logo();
    printf("       P A N T A L L A  P R I N C I P A L        \n");
    printf("=================================================\n");
    printf("\n");
    printf("Hola!\n");
    printf("\n");
    printf("1. Jugar\n");
    printf("2. Mostrar ranking\n");
    printf("3. Ver traducciones hechas\n");
    printf("4. Atras\n");
    char opc[2];
    printf("Introduzca la opcion deseada:");
    scanf("%s", opc);
    if (*opc == '1')
    {
        pantalla31();
    }
    else if (*opc == '2')
    {
        pantalla4();
    }
    else if (*opc == '3')
    {
        pantalla5();
    }
    else if (*opc == '4')
    {
        pantalla65(2);
    }
    else
    {
        pantalla64();
    }
}

void pantalla31()
{
    system("cls");
    logo();
    printf("                  I D I O M A                    \n");
    printf("=================================================\n");
    printf("1. Codigo morse internacional\n");
    printf("2. Codigo morse americano\n");
    char opc[2];
    printf("Introduzca la opcion deseada:");
    scanf("%s", opc);

    static char* palabras_usadas[7];

    static char letras_conocidas[15];

    static char pista[5];

    if (*opc == '1')
    {
        system("cls");
        crearAlfabeto("Traducciones/internacional.txt");
        for(int i = 0; i<26; i++){
            printf("%s\n", alfabeto[i]);
        }
        
        pantalla3(7, palabras_usadas, letras_conocidas, pista, 0, 0, 0); // habra que pasar como parametro el idioma 
    }
    else if (*opc == '2')
    {
        crearAlfabeto("Traducciones/americano.txt");
        system("cls");
        pantalla3(7, palabras_usadas, letras_conocidas, pista, 0, 0, 0);
    }
    else
    {
        pantalla31();
    }
}

void display_pantalla3(int intentos_restantes, char** palabras_usadas, char* letras_conocidas, char* pista, int fallado, int mal_input, int pista_mostrada){
    printf("                 A D I V I N A !                 \n");
    printf("=================================================\n\n");
    
     if (mal_input==1){
        mal_input=0;
        printf("Intentalo otra vez, esa opcion no existe\n");
    }

    else if (fallado==1){
        fallado=0;
        printf("Lo siento. Intentalo otra vez!\n");
    }

    else if (pista_mostrada==1){
        pista_mostrada=0;
        printf("Se ha guardado la pista correctamente\n");
    }


    printf("Intentos restantes: %i\n\n", intentos_restantes); 
    printf("La palabra esta siendo impresa en los LEDs\n\n");
    printf("Palabras usadas: \n");         
    for(int i=0; i<7;i++){
        if(palabras_usadas[i]!=NULL){
            printf("\t-  %s\n", palabras_usadas[i]);
        }
    }
    
    printf("Pistas: \n");
    for(int a=0; a<strlen(pista);a++){
        if(pista!=NULL & isalpha(pista[a])){
            printf("\t-  %c\n", pista[a]);
        }
    }
    printf("Conoces las letras: \n");
    if(strlen(letras_conocidas)!=0){
        for(int i=0; i<strlen(letras_conocidas);i++){
            printf("\t-  %c\n", letras_conocidas[i]);
        }
    }
    printf("\n");

    //PRUEBA    PRUEBA  PRUEBA  PRUEBA
    //PRUEBA    PRUEBA  PRUEBA  PRUEBA
    //PRUEBA    PRUEBA  PRUEBA  PRUEBA 
    actualizar_puntuacion(15);
    mostrar_puntuacion();
    printf("\n");

    printf("Opciones: \n");
    printf("1. Insertar palabra\n");
    printf("2. Mostrar pista (Recuerda que tu puntuacion disminuira)\n");
    printf("3. Rendirse\n");
}

//PRUEBA    //PRUEBA
//PRUEBA    //PRUEBA
//PRUEBA    //PRUEBA
//PRUEBA    //PRUEBA    
//PRUEBA    //PRUEBA
//PRUEBA    //PRUEBA

// Variables globales para la puntuacion y las pistas utilizadas
int puntuacion = 0;
int pistas_utilizadas = 0;
int penalizacion_pistas = 7;    // Puntuacion que se resta por cada pista utilizada

// Funcion para actualizar la puntuacion
void actualizar_puntuacion(int puntos) {
    puntuacion += puntos;
}

// Funcion para penalizar el uso de pistas
void penalizar_pista() {
    puntuacion -= penalizacion_pistas;
    pistas_utilizadas++;
}

// Funcion para mostrar la puntuacion actual
void mostrar_puntuacion() {
    printf("Puntuacion actual: %d\n", puntuacion);
}

// Funcion para mostrar el numero de pistas utilizadas
void mostrar_pistas_utilizadas() {
    printf("Pistas utilizadas: %d\n", pistas_utilizadas);
}




void pantalla3(int intentos_restantes, char** palabras_usadas, char* letras_conocidas, char* pista, int fallado, int mal_input, int pista_mostrada)
{   
    int jugando= 1;
    while(jugando==1){
        logo();
        display_pantalla3(intentos_restantes, palabras_usadas, letras_conocidas, pista, fallado, mal_input, pista_mostrada); //añadir aqui las pistas y las letras acertadas 
        char* adivinanza;                               
        adivinanza = sortear_palabra();                   //mandarle el usuario, acceder a la base de datos y darle una palabra que no haya hecho
        //mostrar_palabra_LEDS(alfabeto, adivinanza);     //se imprime por pantalla
        char opc[2];
        printf("Introduzca la opcion deseada:");
        scanf("%s", opc);
        if (*opc == '1')
        {
            char palabra[15];
            printf("Introduce palabra:");
            scanf("%s", palabra);

            if(strcasecmp(palabra, adivinanza)==0){         
                jugando=0;
                system("cls");
                pantalla32();
            }
            else{
                //anyadir palabras usadas, letras que coincidan
                system("cls");
                //char opc[2];
                //printf("Pulsa cualquier tecla para continuar: ");
                //scanf("%s", opc);
                fallado=1;
                mal_input=0;
                pista_mostrada=0;

                intentos_restantes-=1;
                palabras_usadas[7-intentos_restantes-1]= palabra;

                int indice=strlen(letras_conocidas);

                for(int i=0; i< strlen(palabra); i++){
                    for(int j=0; j < strlen(adivinanza); j++){
                        if (tolower(palabra[i])==tolower(adivinanza[j])){
                            int encontrado=0;
                            for(int k=0; k<strlen(letras_conocidas); k++){
                                if(tolower(palabra[i])== tolower(letras_conocidas[k])){
                                    encontrado=1;
                                } 
                            }
                            if(encontrado==0){
                                letras_conocidas[indice]= tolower(palabra[i]);
                                indice++;
                            }
                            
                        }
                    }
                }

                


//programar letras acertadas

                if (intentos_restantes==0){
                    system("cls");
                    logo();
                    printf("                    V A Y A !                    \n");
                    printf("=================================================\n\n");
                    printf("Parece que te has quedado sin intentos, es una pena!\n");
                    printf("Quieres jugar otra vez?\n");
                    printf("1. Si, quiero jugar otra partida!\n");
                    printf("2. No, quiero volver a la pantalla principal\n");
                    printf("Introduzca la opcion deseada:");
                    scanf("%s", opc);
                    if (*opc == '1')
                    {
                        system("cls");
                        pantalla31();
                    } 
                    else if(*opc == '2')
                    {
                        system("cls");
                        pantalla2();
                    }
    

                }
                else{
                    pantalla3(intentos_restantes, palabras_usadas, letras_conocidas, pista, fallado, mal_input, pista_mostrada);
                }
            }

        }
        else if (*opc == '2')
        {
            if( strlen(pista)<5){
                int i=0;
                int j;
                int encontrada=0;

                //PRUEBA    PRUEBA  PRUEBA  PRUEBA
                //PRUEBA    PRUEBA  PRUEBA  PRUEBA
                //PRUEBA    PRUEBA  PRUEBA  PRUEBA 
                printf("\n Has solicitado una pista.\n");
                penalizar_pista();
                mostrar_puntuacion();
                mostrar_pistas_utilizadas();
                printf("\n");

                mal_input=0;
                
                while(i<strlen(adivinanza)& encontrada==0){
                    j=0;
                    int encontrar=1;
                    while(j<strlen(letras_conocidas)& encontrar==1){
                        if(tolower(adivinanza[i])==tolower(letras_conocidas[j])){
                            encontrar=0;
                        }
                        j++;
                    }
                    if(encontrar==1){
                        int mostrada=0;
                        int k=0;
                        while(k< strlen(pista)&mostrada==0){
                            if(pista[k]==adivinanza[i]){
                                mostrada=1;
                            }
                            k++;
                        }
                        if(mostrada==0){
                            encontrada=1;
                            printf("Una de las letras de la palabra a adivinar es... '%c'\n", adivinanza[i]);
                            pista_mostrada=1;
                            fallado=0;
                            int indice=strlen(pista);
                            pista[indice]=adivinanza[i];

                            char opc[2];
                            printf("Pulsa cualquier tecla para continuar: ");
                            scanf("%s", opc);
                        }
                    }

                    i++;
                }

                if(encontrada==0){
                    printf("Lo siento, no se ha podido encontrar una pista en este momento\n");
                    fallado=1;
                    pista_mostrada=0;
                    char opc[2];
                    printf("Pulsa cualquier tecla para continuar: ");
                    scanf("%s", opc);
                }
                
            }
            else{
                printf("Lo siento, no puedes pedir mas pistas. Ya has gastado tus 5 pistas disponibles\n");
                fallado=1;
                pista_mostrada=0;
                char opc[2];
                printf("Pulsa cualquier tecla para continuar: ");
                scanf("%s", opc);
            }
        }
        else if (*opc == '3')
        {
            system("cls");
            jugando=0;
            pantalla62(intentos_restantes, palabras_usadas, letras_conocidas, pista);
        }
        else{
            mal_input=1;
            fallado=0;
        }

    }
}

void pantalla32()
{
    system("cls");
    logo();
    printf("                 A D I V I N A !                 \n");
    printf("=================================================\n\n");
    printf("Enhorabuena! Has acertado la palabra.\n\n");
    printf("1. Salir\n");
    printf("2. Volver a jugar\n");
    char opc[2];
    printf("Introduzca la opcion deseada:");
    scanf("%s", opc);
    if (*opc == '1')
    {
        pantalla63(32);
    }

    if (*opc == '2')
    {
        pantalla31();
    }
}

void pantalla4()
{
    system("cls");
    logo();
    printf("                 R A N K I N G                   \n");
    printf("=================================================\n\n");
    printf("1. usuario: puntos\n");
    printf("2. usuario: puntos\n");
    printf("3. usuario: puntos\n");
    printf("4. usuario: puntos\n");
    printf("5. usuario: puntos\n");
    printf("Opciones:\n");
    printf("1. Mostrar mis estadisticas\n");
    printf("2. Atras\n");
    char opc[2];
    printf("Introduzca la opcion deseada:");
    scanf("%s", opc);
    if (*opc == '1')
    {
        pantalla41();
    }
    else if (*opc == '2')
    {
        pantalla63(4);
    }
}

void pantalla41()
{
    system("cls");
    logo();
    printf("         T U S  E S T A D I S T I C A S          \n");
    printf("=================================================\n\n");
    printf("Porcentaje de aciertos: \n");
    printf("Numero de partidas jugadas: \n");
    printf("Media de intentos: \n");
    printf("Opciones:\n");
    printf("1. Exportar mis estadisticas a fichero\n");
    printf("2. Atras\n");
    char opc[2];
    printf("Introduzca la opcion deseada:");
    scanf("%s", opc);
    if (*opc == '1')
    {
        //funcion
    }
    else if (*opc == '2')
    {
        pantalla4();
    }
}

void pantalla5()
{
    system("cls");
    logo();
    printf("            T R A D U C C I O N E S              \n");
    printf("=================================================\n\n");
    //AQUI VAN LAS TRADUCCIONES
    char opc[2];
    printf("Para ir atras pulsa 1: ");
    scanf("%s", opc);
    if (*opc == '1')
    {
        pantalla2();
    }
}

void pantalla61(int pantalla)
{
    system("cls");
    logo();
    printf("                  A V I S O !                    \n");
    printf("=================================================\n\n");
    printf("Seguro que quieres volver atras?\n");
    printf("1. Si\n");
    printf("2. No\n");
    char opc[2];
    printf("Introduzca la opcion deseada:");
    scanf("%s", opc);
    if (*opc == '1')
    {
        //no se que va aqui
    }
    else if (*opc == '2')
    {
         //no se que va aqui
    }
}

void pantalla62(int intentos_restantes, char** palabras_usadas, char* letras_acertadas, char* pista)
{
    system("cls");
    logo();
    printf("                  A V I S O !                    \n");
    printf("=================================================\n\n");
    printf("Recuerda que si te rindes no sumaras puntos.\n");
    printf("Seguro que quieres rendirte?\n");
    printf("1. Si\n");
    printf("2. No\n");
    char opc[2];
    printf("Introduzca la opcion deseada:");
    scanf("%s", opc);
    if (*opc == '1')
    {
        pantalla2();
    }
    else if (*opc == '2')
    {   
        system("cls");
         pantalla3(intentos_restantes, palabras_usadas, letras_acertadas, pista, 0, 0, 0); 
    }
}

void pantalla63(int pantalla)
{
    system("cls");
    logo();
    printf("                  A V I S O !                    \n");
    printf("=================================================\n\n");
    printf("Seguro que quieres volver a la pantalla principal?\n");
    printf("1. Si\n");
    printf("2. No\n");
    char opc[2];
    printf("Introduzca la opcion deseada:");
    scanf("%s", opc);
    if (*opc == '1')
    {   if(pantalla == 32 | pantalla == 4){
            pantalla2();
        }
    }
    else if (*opc == '2')
    {
        if(pantalla == 32){
            pantalla32();
        }
        else if(pantalla == 4){
            pantalla4();
        }
    }
}

void pantalla65(int pantalla)
{
    system("cls");
    logo();
    printf("                  A V I S O !                    \n");
    printf("=================================================\n\n");
    printf("Seguro que quieres volver al inicio?\n");
    printf("1. Si\n");
    printf("2. No\n");
    char opc[2];
    printf("Introduzca la opcion deseada:");
    scanf("%s", opc);
    if (*opc == '1')
    {   if (pantalla==2){
            pantalla1();
        }
    }
    else if (*opc == '2')
    {
        if(pantalla == 2){
            pantalla2();
        }
    }
}







void pantalla64()
{
    system("cls");
    logo();
    printf("                  A V I S O !                    \n");
    printf("=================================================\n\n");
    printf("Seguro que quieres cerrar el programa?\n");
    printf("1. Si\n");
    printf("2. No\n");
    char opc[2];
    printf("Introduzca la opcion deseada:");
    scanf("%s", opc);
    if (*opc == '1')
    {
        printf("Hasta la proxima!");
        cerrar();
    }
    else if (*opc == '2')
    {
        pantalla1();
    }
}


char* sortear_palabra(){ //recibir usuario para acceder a la base de datos y sortear entre palabras que el usu no haya hecho ya
    return "ADIVINANZA";
}


void mostrar_palabra_LEDS(char* adivinanza){
    
    for (int i=0; i<strlen(adivinanza); i++){
        int no_encontrado= 1;
        int j=0;
        while(no_encontrado==1){
            if(adivinanza[i]==alfabeto[j][0]){
                no_encontrado=0;
            }
            j++;
        }

        printf("%s", alfabeto[j][1]);
    }
}




void crearAlfabeto(char *fichero){
    //Matriz alfabeto:
    /* [A][.][-]...
       [B][-][-]...
       [C][.][.]...
       [D][.][-]...
       [E][.][.]...
    */

    

    //FICHERO
    FILE *archivo;
    archivo = fopen(fichero, "r");
    if(archivo == NULL){
        perror("ERROR 404: No se ha podido encontrar el archivo");
        return;
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
            //printf("Tamaño de la fila %d: %d\n", fila, col);
            fila++;
            col = 0;
        }
        else if(c == '_'){
            alfabeto[fila][col] = ' ';
            col++;
        }
        else{
            alfabeto[fila][col] = c;
            //printf("Guardado en alfabeto[%d][%d]: %c\n", fila, col, c);
            col++;
        }
    }
    fseek(archivo, 0, SEEK_SET);
    //printf("Datos guardados en la matriz\n");


    fclose(archivo);
    for(int i = 0; i<26; i++){
        printf("%s\n", alfabeto[i]);
    }

}
