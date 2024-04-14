#include <stdio.h>
#include <stdlib.h>
#include "pantallas.h"
#include <string.h>
#include "utils.h"
#include <ctype.h>
#include "sqlUtils.h"
#include "sqlite3.h"
#include "time.h"


char* palabras_usadas[7];
char letras_conocidas[15];
char pista[5];


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

    char correo[20];
    printf("Correo: ");
    scanf("%s", correo);

    char contrasena[20];
    printf("Contrasena: ");
    scanf("%s", contrasena);

    char contrasenaNue[20];
    printf("Repite la contrasena: ");
    scanf("%s", contrasenaNue);

    if (strlen(nombre) != 0 && strlen(apellido) != 0 && strlen(correo) != 0 && strlen(nick) != 0 && strlen(contrasena) != 0 && strlen(contrasenaNue) != 0 && strcmp(contrasena, contrasenaNue) == 0) {
        Usuario *usuarioLeido= leerUsuario(nick);
        if (usuarioLeido==NULL){
            printf("Hola, %s. Has sido registrado correctamente!\n", nick);
            char opc[2];
            Usuario usuarioNuevo;
            usuarioNuevo.Nombre=nombre;
            usuarioNuevo.Apellido=apellido;
            usuarioNuevo.Apodo=nick;
            usuarioNuevo.Correo=correo;
            usuarioNuevo.Contrasenya= contrasena;
            Estadisticas estadisticaNueva;
            estadisticaNueva.Aciertos=0;
            estadisticaNueva.fallos=0;
            int ID_estadistica= crearEstadisticas(estadisticaNueva);

            Estadisticas *estadisticaNueva2= leerEstadisticas(ID_estadistica);
            usuarioNuevo.ID_Estadistica= (*estadisticaNueva2).ID_Estadistica;
            free(estadisticaNueva2);
            estadisticaNueva2=NULL;
            
            int resultado=crearUsuario(usuarioNuevo);
            if(resultado==SQLITE_OK){
                printf("Pulsa cualquier tecla para continuar: ");
                scanf("%s", opc);
                pantalla1();
            }
            free(usuarioLeido);
            usuarioLeido=NULL;
        }
        else{
            printf("No has podido ser registrado, ese usuario ya existe. Quieres volver a intentarlo? \n");
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
    printf("H");
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
    Usuario *usu= leerUsuario(nick);
    
        if(usu!=NULL){
            if (strcmp((*usu).Contrasenya, contrasena)==0){
                pantalla2(nick, usu); 
            }
            else{
                free(usu);
                usu=NULL;
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
        }
    
        else{
            free(usu);
            usu=NULL;
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
    
}


void pantalla2(char *nick, Usuario* usuario)
{
    system("cls");
    logo();
    printf("       P A N T A L L A  P R I N C I P A L        \n");
    printf("=================================================\n");
    printf("\n");
    printf("Hola, %s!\n", nick);
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
        pantalla31(nick, usuario);
    }
    else if (*opc == '2')
    {
        pantalla4(nick, usuario);
    }
    else if (*opc == '3')
    {
        pantalla5(nick, usuario);
    }
    else if (*opc == '4')
    {
        pantalla65(2, nick, usuario);
    }
    else
    {
        free(usuario);
        usuario=NULL;
        pantalla64();
    }
}

void pantalla31(char *nick, Usuario *usu)
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
    char **alfabeto;
    alfabeto = (char**) malloc(26* sizeof(char*));

    if (*opc == '1') 
    {
        system("cls");
        alfabeto= crearAlfabeto("Traducciones/internacional.txt", alfabeto);
        
        for (int i = 0; i < 15; i++) {
            if (palabras_usadas[i] != NULL) {
                palabras_usadas[i][0] = '\0'; // Asignar el carácter nulo al primer carácter de la cadena
            }

            pista[0]='\0';
            letras_conocidas[0]='\0';
        }
        Partida nuevaPartida;
        nuevaPartida.ID_Morse=1;
        nuevaPartida.ID_Usuario= (*usu).ID_Usuario;
        time_t tiempo_actual = time(NULL);
        struct tm *hora_local = localtime(&tiempo_actual);
        nuevaPartida.Fecha= asctime(hora_local);
        nuevaPartida.Resultado="nulo";
        nuevaPartida.Puntuacion=0;
        nuevaPartida.Intentos=0;
        nuevaPartida.ID_Palabra=1;
        int idPartida= crearPartida(nuevaPartida);
        Partida *partidaDefinitiva = leerPartida(idPartida);
        printf("%s",partidaDefinitiva->Fecha);
        printf("%i",partidaDefinitiva->ID_Morse);
        printf("%i",partidaDefinitiva->ID_Palabra);
        printf("%i",partidaDefinitiva->ID_Usuario);
        printf("%i",partidaDefinitiva->Intentos);
        printf("%i",partidaDefinitiva->Puntuacion);
        printf("%s\n",partidaDefinitiva->Resultado);
        char* adivinanza = sortear_palabra((*usu).ID_Usuario);  //mandarle el usuario, acceder a la base de datos y darle una palabra que no haya hecho
        
          

        pantalla3(nick, 7, palabras_usadas, letras_conocidas, pista, 0, 0, 0, 0,alfabeto, partidaDefinitiva, usu, adivinanza); // habra que pasar como parametro el idioma 
    }
    else if (*opc == '2')
    {
        alfabeto= crearAlfabeto("Traducciones/americano.txt", alfabeto);
        system("cls");


        for (int i = 0; i < 15; i++) {
            if (palabras_usadas[i] != NULL) {
                palabras_usadas[i][0] = '\0'; // Asignar el carácter nulo al primer carácter de la cadena
            }

            pista[0]='\0';
            letras_conocidas[0]='\0';
        }

        Partida nuevaPartida;
        nuevaPartida.ID_Morse=2;
        time_t tiempo_actual = time(NULL);
        struct tm *hora_local = localtime(&tiempo_actual);
        nuevaPartida.Fecha= asctime(hora_local);
        nuevaPartida.ID_Usuario= (*usu).ID_Usuario;
        int idPartida= crearPartida(nuevaPartida);
        Partida *partidaDefinitiva= leerPartida(idPartida);

        char* adivinanza = sortear_palabra((*usu).ID_Usuario);  //mandarle el usuario, acceder a la base de datos y darle una palabra que no haya hecho
        
    
        pantalla3(nick, 7, palabras_usadas, letras_conocidas, pista, 0, 0, 0, 0, alfabeto, partidaDefinitiva, usu, adivinanza);
    }
    else
    {
        pantalla31(nick, usu);
    }
}

void display_pantalla3(int intentos_restantes, char** palabras_usadas, char* letras_conocidas, char* pista, int puntuacion, int fallado, int mal_input, int pista_mostrada, char** alfabeto, char* adivinanza){
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

    printf("Puntuacion: %i\n\n", puntuacion); 
    printf("Intentos restantes: %i\n\n", intentos_restantes); 
    printf("La palabra esta siendo impresa en los LEDs\n");
    //printf("%s", adivinanza);
    //printf("%c\n", alfabeto[0][1]);
    mostrar_palabra_LEDS(adivinanza, alfabeto);     //se imprime por pantalla
    //printf("%s", adivinanza);
    printf("\n");
    printf("Palabras usadas: \n");         
    for(int i=0; i<7;i++){
        if(palabras_usadas[i]!=NULL && palabras_usadas[i][0]!= '\0'){
            printf("\t-  %s\n", palabras_usadas[i]);
        }
    }
    
    printf("Pistas: \n");
    for(int a=0; a<strlen(pista);a++){
        if(pista!=NULL && isalpha(pista[a])){
            printf("\t-  %c\n", tolower(pista[a]));
        }
    }
    printf("Conoces las letras: \n");
    if(strlen(letras_conocidas)!=0){
        for(int i=0; i<strlen(letras_conocidas);i++){
            printf("\t-  %c\n", letras_conocidas[i]);
        }
    }
    printf("\n");

    printf("Opciones: \n");
    printf("1. Insertar palabra\n");
    printf("2. Mostrar pista (Recuerda que tu puntuacion disminuira)\n");
    printf("3. Rendirse\n");
}

int recalcular_puntuacion(char* adivinanza, int intentos_restantes, char *pista){
    int puntuacion= ((int)strlen(adivinanza))*20 + intentos_restantes*15 - ((int)strlen(pista))*40;
    if(puntuacion<0){
        puntuacion=0;
    }
    return puntuacion;
}

typedef struct{
        char nick[15];
        int puntuacion;
    } Registro;

/*
void guardar_puntuacion_en_archivo(char *nick, int puntuacion) {
    FILE *archivo;
    archivo = fopen("Ranking/ranking.txt", "a"); // Abre el archivo en modo de apéndice

    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

   Registro ranking[500]; // Se asume un máximo de 500 registros
    int num_registros = 0;

    // Leer los datos existentes del archivo
    while (fscanf(archivo, "%s %d", ranking[num_registros].nick, &ranking[num_registros].puntuacion) == 2) {
        num_registros++;
    }

    // Agregar el nuevo dato
    strcpy(ranking[num_registros].nick, nick);
    ranking[num_registros].puntuacion = puntuacion;
    num_registros++;

    // Ordenar los registros según la puntuación de mayor a menor
    for (int i = 0; i < num_registros - 1; i++) {
        for (int j = 0; j < num_registros - i - 1; j++) {
            if (ranking[j].puntuacion < ranking[j + 1].puntuacion) {
                // Intercambiar los registros
                Registro temp = ranking[j];
                ranking[j] = ranking[j + 1];
                ranking[j + 1] = temp;
            }
        }
    }

    // Regresar al inicio del archivo
    rewind(archivo);

    // Escribir los datos ordenados en el archivo
    for (int i = 0; i < num_registros; i++) {
        fprintf(archivo, "%s %d\n", ranking[i].nick, ranking[i].puntuacion);
    }

    // Cerrar el archivo
    fclose(archivo);
}*/

void pantalla3(char *nick, int intentos_restantes, char** palabras_usadas, char* letras_conocidas, char* pista, int puntuacion, int fallado, int mal_input, int pista_mostrada, char** alfabeto, Partida *nuevaPartida, Usuario *usu, char* adivinanza)
{   
    int jugando= 1;
    while(jugando==1){
        logo();                          
        int puntuacion= recalcular_puntuacion(adivinanza, intentos_restantes, pista);
        display_pantalla3(intentos_restantes, palabras_usadas, letras_conocidas, pista, puntuacion, fallado, mal_input, pista_mostrada, alfabeto, adivinanza); //añadir aqui las pistas y las letras acertadas 
        printf("%s",nuevaPartida->Fecha);
        printf("%i",nuevaPartida->ID_Morse);
        printf("%i",nuevaPartida->ID_Palabra);
        printf("%i",nuevaPartida->ID_Usuario);
        printf("%i",nuevaPartida->Intentos);
        printf("%i",nuevaPartida->Puntuacion);
        printf("%s\n",nuevaPartida->Resultado);
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

                (*nuevaPartida).Intentos= intentos_restantes;
                //int id_palabra= leerPalabra(adivinanza);
                //(*nuevaPartida).ID_Palabra=id_palabra;
                printf("ACTUALIZAR PARTIDA");
                actualizarPartida((*nuevaPartida).ID_Partida, *nuevaPartida);
                system("cls");
                printf("LEER PARTIDA");
                nuevaPartida= leerPartida(nuevaPartida->ID_Partida);
                pantalla32(nick, puntuacion, nuevaPartida, usu);
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
                    puntuacion=-10;
                    printf("Puntuacion: %i\n", puntuacion);

                    //guardar_puntuacion_en_archivo(nick, puntuacion);

                    int id_palabra= leerPalabra(adivinanza);
                    (*nuevaPartida).ID_Palabra= id_palabra;
                    (*nuevaPartida).ID_Usuario= (*usu).ID_Usuario;
                    (*nuevaPartida).Intentos= intentos_restantes;
                    (*nuevaPartida).Puntuacion= puntuacion;
                    (*nuevaPartida).Resultado= "fallado";
                    (*nuevaPartida).Resultado= "fallado";
                    actualizarPartida((*nuevaPartida).ID_Partida, (*nuevaPartida));

                    Estadisticas *estadisActuales= leerEstadisticas((*usu).ID_Estadistica);
                    (*estadisActuales).fallos=(*estadisActuales).fallos+1;
                    actualizarEstadisticas((*estadisActuales).ID_Estadistica, *estadisActuales);
                    free(estadisActuales);
                    estadisActuales=NULL;
                    //MIRAR ESTOS FREE
                    free(nuevaPartida);
                    nuevaPartida = NULL;


                    printf("Quieres jugar otra vez?\n");
                    printf("1. Si, quiero jugar otra partida!\n");
                    printf("2. No, quiero volver a la pantalla principal\n");
                    printf("Introduzca la opcion deseada:");
                    scanf("%s", opc);
                    if (*opc == '1')
                    {
                        system("cls");
                        pantalla31(nick, usu);
                    } 
                    else if(*opc == '2')
                    {
                        system("cls");
                        pantalla2(nick, usu);
                    }
                }
                else{
                    pantalla3(nick, intentos_restantes, palabras_usadas, letras_conocidas, pista, puntuacion, fallado, mal_input, pista_mostrada,alfabeto, nuevaPartida, usu, adivinanza);
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
                //penalizar_pista();
                //mostrar_puntuacion();
                //mostrar_pistas_utilizadas();
                //printf("\n");

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
            int id_palabra= leerPalabra(adivinanza);
            (*nuevaPartida).ID_Palabra= id_palabra;
            actualizarPartida((*nuevaPartida).ID_Partida, (*nuevaPartida));
            pantalla62(nick, intentos_restantes, palabras_usadas, letras_conocidas, pista, puntuacion, alfabeto, nuevaPartida, usu, adivinanza);
        }
        else{
            mal_input=1;
            fallado=0;
        }

    }
}



void pantalla32(char* nick, int puntuacion, Partida *nuevaPartida, Usuario *usu)
{
    //guardar_puntuacion_en_archivo(nick, puntuacion);
    
    system("cls");
    logo();
    printf("                 A D I V I N A !                 \n");
    printf("=================================================\n\n");
    printf("Enhorabuena! Has acertado la palabra.\n\n");
    printf("Puntuacion: %i\n", puntuacion);
    printf("1. Salir\n");
    printf("2. Volver a jugar\n");
    
    
    (*nuevaPartida).Puntuacion = puntuacion;
    (*nuevaPartida).Resultado = "acertado";
    printf("ID usu: %i", (*nuevaPartida).ID_Usuario);
    printf("puntos: %i", (*nuevaPartida).Puntuacion);
    printf("resultado: %s", (*nuevaPartida).Resultado);
    printf("ID PARTIDA: %i", (*nuevaPartida).ID_Partida);
    
    actualizarPartida((*nuevaPartida).ID_Partida, *nuevaPartida);
    
    Partida *actualizada = leerPartida((*nuevaPartida).ID_Partida);

    
    printf("ACTUALIZADO\n");
    printf("Puntuacion: %i\n", (*actualizada).Puntuacion);
    printf("ID usu: %i\n", (*actualizada).ID_Usuario);
    printf("FECHA: %s\n", (*actualizada).Fecha);
    printf("resultado: %s\n", (*actualizada).Resultado);
    
    Estadisticas *estadisActuales= leerEstadisticas((*usu).ID_Estadistica);
    (*estadisActuales).Aciertos=(*estadisActuales).Aciertos+1;
    actualizarEstadisticas((*estadisActuales).ID_Estadistica, *estadisActuales);
    Estadisticas *estadisticasActualizadas = leerEstadisticas((*usu).ID_Estadistica);
    
    free(estadisActuales);
    estadisActuales=NULL;
    
    printf("AYUDA\n");
    free(estadisActuales);
    estadisActuales=NULL;


    char opc[2];
    printf("Introduzca la opcion deseada:");
    scanf("%s", opc);
    if(puntuacion!=0){ // importante que sea diferente de 0 -Nora
         //almacenar puntuacion de partida
    }
    if (*opc == '1')
    {
        pantalla63(32, nick, usu);
    }

    if (*opc == '2')
    {
        pantalla31(nick, usu);
    }
}

void pantalla4(char *nick, Usuario *usu)
{
    system("cls");
    logo();
    printf("                 R A N K I N G                   \n");
    printf("=================================================\n\n");

    //Abrimos el archivo del ranking
    FILE *archivo;
    archivo = fopen("Ranking/ranking.txt", "r");
    if (archivo == NULL){
        printf("Error al abrir el archivo de ranking, \n");
        return;
    }



    //Prueba  Prueba  Prueba  Prueba
    //Prueba  Prueba  Prueba  Prueba
    //Prueba  Prueba  Prueba  Prueba
    //Prueba  Prueba  Prueba  Prueba


    //definimos una estructura para almacenar 
    //los datos de nick y puntuacion
    

    /*Registro ranking[500]; //No hay mas de 500 registros
    int num_registros = 0;
    while(fscanf(archivo, "%s, %d \n", ranking[num_registros].nick, &ranking[num_registros].puntuacion) == 2){
        num_registros++;
    }


    //Ordenamos los registros segun la puntuacion de mayor a menor 
    for (int i = 0; i < num_registros - 1; i++) {
        for (int j = 0; j < num_registros - i - 1; j++) {
            if (ranking[j].puntuacion < ranking[j + 1].puntuacion) {
                // Intercambiar los registros
                Registro temp = ranking[j];
                ranking[j] = ranking[j + 1];
                ranking[j + 1] = temp;
            }
        }
    }

    // Mostramos los 5 primeros registros ordenados por puntuacion
    //printf("Puntuacion\tUsuario\n");
    for (int i = 0; i < num_registros && i < 5; i++) {
        printf("%d, %s\n", ranking[i].puntuacion, ranking[i].nick);
    }

    // Cerrar el archivo
    fclose(archivo);*/

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
        pantalla41(nick, usu);
    }
    else if (*opc == '2')
    {
        pantalla63(4, nick, usu);
    }
}

void pantalla41(char *nick, Usuario *usu)
{
    Estadisticas *misEstadisticas= leerEstadisticas((*usu).ID_Estadistica);
    int total= (*misEstadisticas).Aciertos + (*misEstadisticas).fallos;
    system("cls");
    logo();
    printf("         T U S  E S T A D I S T I C A S          \n");
    printf("=================================================\n\n");
    printf("Porcentaje de aciertos: %i\n", (*misEstadisticas).Aciertos/total*100);
    printf("Numero de partidas jugadas: \n", total);

    //printf("Media de intentos: \n");
    printf("Opciones:\n");
    printf("1. Exportar mis estadisticas a fichero\n");
    printf("2. Atras\n");
    char opc[2];
    printf("Introduzca la opcion deseada:");
    scanf("%s", opc);
    if (*opc == '1')
    {
        FILE * f;
        f= fopen("misEstadisticas.txt", 'w');
        fprintf(f, "         T U S  E S T A D I S T I C A S          \n");
        fprintf(f, "=================================================\n\n");
        fprintf(f, "Porcentaje de aciertos: %i\n", (*misEstadisticas).Aciertos/total*100);
        fprintf(f, "Numero de partidas jugadas: %i\n", total);
        fclose(f);
        
        free(misEstadisticas);
        misEstadisticas=NULL;
    }
    else if (*opc == '2')
    {
        free(misEstadisticas);
        misEstadisticas=NULL;
        pantalla4(nick, usu);
    }
}

void pantalla5(char *nick, Usuario *usu)
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
        pantalla2(nick, usu);
    }
}
/*
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
*/
void pantalla62(char *nick, int intentos_restantes, char** palabras_usadas, char* letras_conocidas, char* pista, int puntuacion, char** alfabeto, Partida *nuevaPartida, Usuario *usu, char* adivinanza)
{
    system("cls");
    logo();
    printf("                  A V I S O !                    \n");
    printf("=================================================\n\n");
    printf("Recuerda que si te rindes se te restaran 10 puntos.\n");
    printf("Seguro que quieres rendirte?\n");
    printf("1. Si\n");
    printf("2. No\n");
    char opc[2];
    printf("Introduzca la opcion deseada:");
    scanf("%s", opc);
    if (*opc == '1')
    {
        
        puntuacion=-10;
        printf("Puntuacion: %i\n", puntuacion);
        //guardar_puntuacion_en_archivo(nick, puntuacion);
        (*nuevaPartida).ID_Usuario = (*usu).ID_Usuario;
        (*nuevaPartida).Intentos= intentos_restantes;
        (*nuevaPartida).Puntuacion= puntuacion;  
        (*nuevaPartida).Resultado= "renunciado";
        
        actualizarPartida((*nuevaPartida).ID_Partida, *nuevaPartida);
        printf("ACTUALIZAO");
        //Estadisticas *estadisActuales= leerEstadisticas((*usu).ID_Estadistica);

        //AQUI ESTA EL ERROR
        /*
        printf("AAAA: %s", estadisActuales->ID_Estadistica);
        (*estadisActuales).fallos=(*estadisActuales).fallos+1;
        actualizarEstadisticas((*estadisActuales).ID_Estadistica, *estadisActuales);
        free(estadisActuales);
        estadisActuales=NULL;
        
        printf("Es una pena, quiza logres adivinar la palabra en la siguiente. Pulsa cualquier tecla para continuar: ");
        scanf("%s", opc);
        pantalla2(nick, usu);*/
    }

    else if (*opc == '2')
    {   
        system("cls");
         pantalla3(nick, intentos_restantes, palabras_usadas, letras_conocidas, pista, puntuacion, 0, 0, 0, alfabeto, nuevaPartida, usu, adivinanza); 
    }
}

void pantalla63(int pantalla, char *nick, Usuario *usu)
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
            pantalla2(nick, usu);
        }
    }
    else if (*opc == '2')
    {
        if(pantalla == 32){
            Partida *partidanula;
            pantalla32(nick,0, partidanula, usu);
        }
        else if(pantalla == 4){
            pantalla4(nick, usu);
        }
    }
}

void pantalla65(int pantalla, char *nick, Usuario *usu)
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
            free(usu);
            usu=NULL;
            pantalla1();
        }
    }
    else if (*opc == '2')
    {
        if(pantalla == 2){
            pantalla2(nick, usu);
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


char* sortear_palabra(int ID_Usuario){ //recibir usuario para acceder a la base de datos y sortear entre palabras que el usu no haya hecho ya
    char* palabra = sortear_n_palabra(ID_Usuario);
    return palabra;
}


void mostrar_palabra_LEDS(char* adivinanza, char** alfabeto){
    // reocorremos cada letra de la palabra
    for (int i = 0; i < strlen(adivinanza); i++)
    {
        char letra = toupper(adivinanza[i]);

        // recorremos el abecedario
        for (int j = 0; j < 26; j++)
        {
            if (letra == alfabeto[j][0])
            {
                // imprimimos la traduccion sin la letra original abecedario[0]
                for (int k = 1; k < strlen(alfabeto[j]) + 1; k++)
                {
                    printf("%c", alfabeto[j][k]);
                }
                printf(" ");
                break;
            }
        }
    }
    printf("\n");
}




char** crearAlfabeto(char *fichero, char** alfabeto){
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
        return alfabeto;
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
            //printf("Tamano de la fila %d: %d\n", fila, col);
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


    fclose(archivo);/*
    for(int i = 0; i<26; i++){
        printf("%s\n", alfabeto[i]);
    }*/
return alfabeto;
}
