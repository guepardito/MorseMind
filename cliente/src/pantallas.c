#include <stdio.h>
#include <stdlib.h>
#include "pantallas.h"
#include <string.h>
#include "utils.h"
#include <ctype.h>
#include "sqlUtils.h"
#include "sqlite3.h"
#include "time.h"
#include "pruebaCliente.h"
#include <time.h>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#define PORT 8080
#define SERVER_ADDR "10.207.0.42"//"192.168.1.16" // Dirección IP de tu Raspberry Pi





char* palabras_usadas[7];
char letras_conocidas[15];
char pista[5];
FILE *logFich;

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
    void cerrarLog();
    exit(-1);
}

void pantallaInicio()
{
    iniciarLog("loggerActividad.log");
    system("cls");
    logo();
    printf("                  I N I C I O                    \n");
    printf("=================================================\n");
    printf("1. Registro\n");
    printf("2. LogIn\n");
    printf("3. Cerrar\n");
    escribirLog("Se ha mostrado la pantalla de inicio");
    char opc[2];
    printf("Introduzca la opcion deseada:");
    scanf("%s", opc);
    if (*opc == '1')
    {
        pantallaRegistro();
    }
    else if (*opc == '2')
    {
        pantallaLogin();
    }
    else
    {
        pantallaAvisoCierre();
    }
}

void pantallaRegistro()
{
  system("cls");
    logo();
    printf("                R E G I S T R O                  \n");
    printf("=================================================\n");

    escribirLog("El usuario quiere registrarse");

    char nombre[15];
    printf("Nombre: ");
    scanf("%s", nombre);

    char apellido[25];
    printf("Apellido: ");
    scanf("%s", apellido);

    char nick[15];
    printf("Nickname: ");
    scanf("%s", nick);

    char correo[40];
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
                escribirLog("Usuario registrado");
                printf("Pulsa cualquier tecla para continuar: ");
                scanf("%s", opc);
                pantallaInicio();
            }
            free(usuarioLeido);
            usuarioLeido=NULL;
        }
        else{
            escribirLog("Error al registrar");
            printf("No has podido ser registrado, ese usuario ya existe. Quieres volver a intentarlo? \n");
            printf("1. Si\n");
            printf("2. No\n");
            char opc[2];
            printf("Introduzca la opcion deseada:");
            scanf("%s", opc);
            if (*opc == '1')
            {
                pantallaRegistro();
            }
            else if (*opc == '2')
            {
                pantallaInicio();
            }
        }
       
    }
    else
    {
        escribirLog("Error al registrar");
        printf("No has podido ser registrado. Quieres volver a intentarlo? \n");
        printf("1. Si\n");
        printf("2. No\n");
        char opc[2];
        printf("Introduzca la opcion deseada:");
        scanf("%s", opc);
        if (*opc == '1')
        {
            pantallaRegistro();
        }
        else if (*opc == '2')
        {
            pantallaInicio();
        }
    }
}

void pantallaLogin()
{
    system("cls");
    logo();
    printf("                  L O G  I N                     \n");
    printf("=================================================\n");

    escribirLog("El usuario quiere iniciar sesion");

    char nick[15];
    printf("Nickname: ");
    scanf("%s", nick);

    char contrasena[25];
    printf("Contrasena: ");
    scanf("%s", contrasena);
    Usuario *usu= leerUsuario(nick);
    
        if(usu!=NULL){
            if (strcmp((*usu).Contrasenya, contrasena)==0){
                escribirLog("Sesion iniciada");
                pantallaPrincipal(nick, usu); 
            }
            else{
                free(usu);
                usu=NULL;
                escribirLog("No se ha podido iniciar sesión");
                printf("No has podido iniciar sesion. Quieres volver a intentarlo? \n");
                printf("1. Si\n");
                printf("2. No\n");
                char opc[2];
                printf("Introduzca la opcion deseada:");
                scanf("%s", opc);
                if (*opc == '1')
                {
                    pantallaLogin();
                }   
                else if (*opc == '2')
                {
                    pantallaInicio();
                }
            }
        }
    
        else{
            free(usu);
            usu=NULL;
            escribirLog("No se ha podido iniciar sesion");
            printf("No has podido iniciar sesion. Quieres volver a intentarlo? \n");
            printf("1. Si\n");
            printf("2. No\n");
            char opc[2];
            printf("Introduzca la opcion deseada:");
            scanf("%s", opc);
            if (*opc == '1')
            {
                pantallaLogin();
            }
            else if (*opc == '2')
            {
                pantallaInicio();
            }
        }
    
}


void pantallaPrincipal(char *nick, Usuario* usuario)
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
    escribirLog("Pantalla principal mostrada");
    char opc[2];
    printf("Introduzca la opcion deseada:");
    scanf("%s", opc);
    if (*opc == '1')
    {
        pantallaCrearAlfabeto(nick, usuario);
    }
    else if (*opc == '2')
    {
        pantallaRanking(nick, usuario);
    }
    else if (*opc == '3')
    {
        pantallaTraducciones(nick, usuario);
    }
    else if (*opc == '4')
    {
        pantallaAvisoCierre(2, nick, usuario);
    }
    else
    {
        free(usuario);
        usuario=NULL;
        pantallaAvisoCierre();
    }
}

void pantallaCrearAlfabeto(char *nick, Usuario *usu)
{
    system("cls");
    logo();
    printf("                  I D I O M A                    \n");
    printf("=================================================\n");
    printf("1. Codigo morse internacional\n");
    printf("2. Codigo morse americano\n");
    escribirLog("Se muestra la pantalla de idioma");
    char opc[2];
    printf("Introduzca la opcion deseada:");
    scanf("%s", opc);
    char **alfabeto;
    alfabeto = (char**) malloc(26* sizeof(char*));

    if (*opc == '1') 
    {
        escribirLog("Idioma internacional seleccionado");
        system("cls");
        alfabeto= crearAlfabeto("Traducciones/internacional.txt", alfabeto);

        for (int i = 0; i < 7; i++) {
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
        char* adivinanza = sortearPalabra((*usu).ID_Usuario);  //mandarle el usuario, acceder a la base de datos y darle una palabra que no haya hecho
        nuevaPartida.ID_Palabra= leerPalabra(adivinanza); 

        int idPartida = crearPartida(nuevaPartida);
        Partida *partidaDefinitiva = leerPartida(idPartida);  
        pantallaJuego(nick, 7, palabras_usadas, letras_conocidas, pista, 0, 0, 0, 0, alfabeto, partidaDefinitiva, usu, adivinanza); 
    }
    else if (*opc == '2')
    {
        escribirLog("Idioma americano seleccionado");
        alfabeto= crearAlfabeto("Traducciones/americano.txt", alfabeto);
        system("cls");


        for (int i = 0; i < 7; i++) {
            if (palabras_usadas[i] != NULL) {
                palabras_usadas[i][0] = '\0'; // Asignar el carácter nulo al primer carácter de la cadena
            }

            pista[0]='\0';
            letras_conocidas[0]='\0';
        }

        Partida nuevaPartida;
        nuevaPartida.ID_Morse=2;
        nuevaPartida.ID_Usuario= (*usu).ID_Usuario;
        time_t tiempo_actual = time(NULL);
        struct tm *hora_local = localtime(&tiempo_actual);
        nuevaPartida.Fecha= asctime(hora_local);
        nuevaPartida.Resultado="nulo";
        nuevaPartida.Puntuacion=0;
        nuevaPartida.Intentos=0;
        char* adivinanza = sortearPalabra((*usu).ID_Usuario);  //mandarle el usuario, acceder a la base de datos y darle una palabra que no haya hecho
        nuevaPartida.ID_Palabra= leerPalabra(adivinanza); 

        int idPartida = crearPartida(nuevaPartida);
        Partida *partidaDefinitiva = leerPartida(idPartida);  
        pantallaJuego(nick, 7, palabras_usadas, letras_conocidas, pista, 0, 0, 0, 0, alfabeto, partidaDefinitiva, usu, adivinanza);
    }
    else
    {
        pantallaCrearAlfabeto(nick, usu);
    }
}

int displayPantallaJuego(int intentos_restantes, char** palabras_usadas, char* letras_conocidas, char* pista, int puntuacion, int fallado, int mal_input, int pista_mostrada, char** alfabeto, char* adivinanza){
    int error = mostrarPalabraLEDS(adivinanza, alfabeto); //se imprime por pantalla. Si devuelve 1, ha habido error
    escribirLog("El usuario ha empezado a jugar");
    if(error == 1){ //HA OCURRIDO ERROR
        return error;
    }else{
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
        //int mostrarLeds = mostrarPalabraLEDS(adivinanza, alfabeto);     //se imprime por pantalla
        //if(mostrarLeds == 1){ //HA OCURRIDO ERROR
        //    
        //}
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
        return error;
    }
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


void pantallaJuego(char *nick, int intentos_restantes, char** palabras_usadas, char* letras_conocidas, char* pista, int puntuacion, int fallado, int mal_input, int pista_mostrada, char** alfabeto, Partida *nuevaPartida, Usuario *usu, char* adivinanza)
{   
    int jugando= 1;
    while(jugando==1){
        logo();                         
        int puntuacion= recalcular_puntuacion(adivinanza, intentos_restantes, pista);                 

        int mostrar = displayPantallaJuego(intentos_restantes, palabras_usadas, letras_conocidas, pista, puntuacion, fallado, mal_input, pista_mostrada, alfabeto, adivinanza); //Si devuelve 1, ha habido error, no se puede jugar
        if(mostrar == 1){
            jugando = 0;
            char opcErr[2];
            printf("Introduzca cualquier tecla para continuar: ");
            scanf("%s", opcErr);
            pantallaPrincipal(nick, usu);
        }else{
        
            char opc[2];
            printf("Introduzca la opcion deseada:");
            scanf("%s", opc);
            if (*opc == '1')
            {
                char palabra[15];
                printf("Introduce palabra:");
                scanf("%s", palabra);
                if(strcasecmp(palabra, adivinanza)==0){ 
                    system("cls");  
                    logo();
                    printf("              E N H O R A B U E N A !             \n");
                    printf("=================================================\n\n");
                    printf("Has acertado!\n");
                    escribirLog("EL usuario ha acertado la palabra");
                    printf("Puntuacion: %i\n", puntuacion);
                    (*nuevaPartida).ID_Usuario= (*usu).ID_Usuario;
                    (*nuevaPartida).Intentos= intentos_restantes;
                    (*nuevaPartida).Puntuacion= puntuacion;
                    (*nuevaPartida).Resultado= "acertado";
                    actualizarPartida((*nuevaPartida).ID_Partida, (*nuevaPartida));

                    Estadisticas *estadisActuales= leerEstadisticas((*usu).ID_Estadistica);
                    (*estadisActuales).Aciertos=(*estadisActuales).Aciertos+1;
                    actualizarEstadisticas((*estadisActuales).ID_Estadistica, *estadisActuales);
                        
                    free(estadisActuales);
                    estadisActuales=NULL;
                    free(nuevaPartida);
                    nuevaPartida = NULL;

                    for (int i=0; i<26; i++){
                        free(alfabeto[i]);
                        alfabeto[i]=NULL;
                    }

                    free(alfabeto);
                    alfabeto=NULL;
                    enviarResultadoLeds("1"); //////////////////////////////////////gestionar envio a leds



                    printf("Quieres jugar otra vez?\n");
                    printf("1. Si, quiero jugar otra partida!\n");
                    printf("2. No, quiero volver a la pantalla principal\n");
                    printf("Introduzca la opcion deseada:");
                    scanf("%s", opc);
                    if (*opc == '1')
                    {
                    system("cls");
                        pantallaCrearAlfabeto(nick, usu);
                    } 
                    else if(*opc == '2')
                    {
                    system("cls");
                        pantallaPrincipal(nick, usu);
                    }
                }
                
                else{
                system("cls");
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
                    


                    if (intentos_restantes==0){
                    system("cls");
                        
                        logo();
                        printf("                    V A Y A !                    \n");
                        printf("=================================================\n\n");
                        printf("Parece que te has quedado sin intentos, es una pena!\n");
                        puntuacion=-10;
                        escribirLog("El usuario se ha quedado sin intentos");
                        printf("Puntuacion: %i\n", puntuacion);

                        (*nuevaPartida).ID_Usuario= (*usu).ID_Usuario;
                        (*nuevaPartida).Intentos= intentos_restantes;
                        (*nuevaPartida).Puntuacion= puntuacion;
                        (*nuevaPartida).Resultado= "fallado";
                        actualizarPartida((*nuevaPartida).ID_Partida, (*nuevaPartida));

                        Estadisticas *estadisActuales= leerEstadisticas((*usu).ID_Estadistica);
                        (*estadisActuales).fallos=(*estadisActuales).fallos+1;
                        actualizarEstadisticas((*estadisActuales).ID_Estadistica, *estadisActuales);
                        
                        free(estadisActuales);
                        estadisActuales=NULL;
                        free(nuevaPartida);
                        nuevaPartida = NULL;


                        for (int i=0; i<26; i++){
                            free(alfabeto[i]);
                            alfabeto[i]=NULL;
                        }
                        free(alfabeto);
                        alfabeto=NULL;

                        enviarResultadoLeds("0"); //////////////////////////////////////gestionar envio a leds

                        printf("Quieres jugar otra vez?\n");
                        printf("1. Si, quiero jugar otra partida!\n");
                        printf("2. No, quiero volver a la pantalla principal\n");
                        printf("Introduzca la opcion deseada:");
                        scanf("%s", opc);
                        if (*opc == '1')
                        {
                        system("cls");
                            pantallaCrearAlfabeto(nick, usu);
                        } 
                        else if(*opc == '2')
                        {
                        system("cls");
                            pantallaPrincipal(nick, usu);
                        }
                    }
                    else{
                        pantallaJuego(nick, intentos_restantes, palabras_usadas, letras_conocidas, pista, puntuacion, fallado, mal_input, pista_mostrada,alfabeto, nuevaPartida, usu, adivinanza);
                    }
                }

            }
            else if (*opc == '2')
            {
                if( strlen(pista)<5){
                    int i=0;
                    int j;
                    int encontrada=0;

                    printf("\n Has solicitado una pista.\n");
                    escribirLog("Se ha solicitado una pista");

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
                actualizarPartida((*nuevaPartida).ID_Partida, (*nuevaPartida));
                pantallaRendir(nick, intentos_restantes, palabras_usadas, letras_conocidas, pista, puntuacion, alfabeto, nuevaPartida, usu, adivinanza);
            }
            else{
                mal_input=1;
                fallado=0;
            }
        }
    }
}


void pantallaRanking(char *nick, Usuario *usu)
{
  system("cls");
    logo();
    printf("                 R A N K I N G                   \n");
    printf("=================================================\n\n");

    hacerYImprimirRankings();

    escribirLog("El usuario quiere ver el ranking");

    printf("Opciones:\n");
    printf("1. Mostrar mis estadisticas\n");
    printf("2. Atras\n");
    char opc[2];
    printf("Introduzca la opcion deseada:");
    scanf("%s", opc);
    if (*opc == '1') {
        pantallaEstadisticas(nick, usu);
    } else if (*opc == '2') {
        pantallaAvisoPPrincipal(4, nick, usu, NULL);
    }
}

void pantallaEstadisticas(char *nick, Usuario *usu)
{
    Estadisticas *misEstadisticas= leerEstadisticas((*usu).ID_Estadistica);

    if ((*misEstadisticas).Aciertos == NULL && (*misEstadisticas).fallos == NULL)
    {
        free(misEstadisticas);
        misEstadisticas=NULL;
        printf("\nNo tienes estadisticas disponibles para exportar, juega antes de intentarlo de nuevo!\n");
        escribirLog("No hay estadisticas");
        printf("Pulsa cualquier tecla para continuar: ");
        char opc[2];
        scanf("%s", opc);
        pantallaRanking(nick, usu);
    }
    
   
    int aciertos = (*misEstadisticas).Aciertos;
    int fallos = (*misEstadisticas).fallos;
    int total = aciertos + fallos;
    float porcentaje = ((float)aciertos/total)*100;
    
  system("cls");
    logo();
    printf("         T U S  E S T A D I S T I C A S          \n");
    printf("=================================================\n\n");
    printf("Porcentaje de aciertos: %.2f%%\n", porcentaje);
    printf("Numero de partidas jugadas: %i\n\n", total);

    escribirLog("El usuario quiere ver sus estadisticas");
        
    printf("Opciones:\n");
    printf("1. Exportar mis estadisticas a fichero\n");
    printf("2. Atras\n");
    char opc[2];
    printf("Introduzca la opcion deseada:");
    scanf("%s", opc);
    if (*opc == '1')
    {
        exportarEstadisticas(porcentaje, total);
        free(misEstadisticas);
        misEstadisticas=NULL;
        
        printf("Ya se han exportado tus datos al fichero! Muchas gracias! \nIntroduce cualquier letra para continuar: ");
        escribirLog("Se han exportado los datos al fichero");
        scanf("%s", opc);
        
        pantallaAvisoPPrincipal(41, nick, usu, NULL);
    }
    else if (*opc == '2')
    {
        free(misEstadisticas);
        misEstadisticas=NULL;
        pantallaRanking(nick, usu);
    }
}

void pantallaTraducciones(char *nick, Usuario *usu)
{
  system("cls");
    logo();
    printf("            T R A D U C C I O N E S              \n");
    printf("=================================================\n\n");
    obtenerTraducciones(nick, usu);
    escribirLog("EL usuario quiere ver sus traducciones");
    char opc[2];
    printf("Para ir atras pulsa 1: ");
    scanf("%s", opc);
    fflush(stdin);
    if (*opc == '1')
    {
        pantallaPrincipal(nick, usu);
    }
}

void pantallaRendir(char *nick, int intentos_restantes, char** palabras_usadas, char* letras_conocidas, char* pista, int puntuacion, char** alfabeto, Partida *nuevaPartida, Usuario *usu, char* adivinanza)
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
    fflush(stdin);
    if (*opc == '1')
    {
        escribirLog("El usuario se ha rendido");
        puntuacion=-10;
        nuevaPartida->Resultado = "rendido";
        nuevaPartida->Intentos = intentos_restantes;
        nuevaPartida->Puntuacion = puntuacion;
        
        actualizarPartida((*nuevaPartida).ID_Partida, *nuevaPartida);
        free(nuevaPartida);
        nuevaPartida = NULL;
        Estadisticas *estadisActuales= leerEstadisticas((*usu).ID_Estadistica);

        int fallos = (*estadisActuales).fallos;
        (*estadisActuales).fallos= fallos + 1;
        
        actualizarEstadisticas((*estadisActuales).ID_Estadistica, *estadisActuales);
        free(estadisActuales);
        estadisActuales=NULL;

        for (int i=0; i<26; i++){
            free(alfabeto[i]);
            alfabeto[i]=NULL;
        }
        free(alfabeto);
        alfabeto=NULL;
        enviarResultadoLeds("0"); //////////////////////////////////////gestionar envio a leds

        printf("Es una pena, quiza logres adivinar la palabra en la siguiente. Quieres intentarlo otra vez?\n");
        printf("1.Si, quiero volver a jugar!\n");
        printf("2.No, lo intentare mas tarde.\n");
        printf("Que quieres hacer? ");
        scanf("%s", opc);
        if(*opc=='1'){
            pantallaCrearAlfabeto(nick, usu);
        }
        else{
            pantallaPrincipal(nick, usu);
        }
    }

    else if (*opc == '2')
    {   
      system("cls");
      escribirLog("El usuario ha querido rendirse, pero ha vuelto al juego");
        pantallaJuego(nick, intentos_restantes, palabras_usadas, letras_conocidas, pista, puntuacion, 0, 0, 0, alfabeto, nuevaPartida, usu, adivinanza); 
    }
}

void pantallaAvisoPPrincipal(int pantalla, char *nick, Usuario *usu, char** alfabeto)
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
    fflush(stdin);
    if (*opc == '1')
    {
            escribirLog("EL usuario quiere volver a la pantalla principal");
           if( pantalla == 4 | pantalla==41){
            pantallaPrincipal(nick, usu);
        }
    }
    else if (*opc == '2')
    {
        if(pantalla == 4){
            pantallaRanking(nick, usu);
        }
        else if(pantalla ==41){
            pantallaEstadisticas(nick, usu);
        }
    }
}

void pantallaAvisoInicio(int pantalla, char *nick, Usuario *usu)
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
    fflush(stdin);
    if (*opc == '1')
    {   escribirLog("EL usuario quiere volver a la pantalla de inicio");
        if (pantalla==2){
            free(usu);
            usu=NULL;
            pantallaInicio();
        }
    }
    else if (*opc == '2')
    {
        if(pantalla == 2){
            pantallaPrincipal(nick, usu);
        }
    }
}




void pantallaAvisoCierre()
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
        escribirLog("El programa se va a cerrar");
        cerrar();
    }
    else if (*opc == '2')
    {
        pantallaInicio();
    }
}


char* sortearPalabra(int ID_Usuario){ //recibir usuario para acceder a la base de datos y sortear entre palabras que el usu no haya hecho ya
    char* palabra = sortear_n_palabra(ID_Usuario);
    return palabra;
}


int mostrarPalabraLEDS(char* adivinanza, char** alfabeto){
    escribirLog("Se ha ordenado enviar la palabra a los leds");
    int indice=0;
    for (int i = 0; i < strlen(adivinanza); i++){
        char letra = toupper(adivinanza[i]);

        // recorremos el abecedario
        for (int j = 0; j < 26; j++){
            if (letra == alfabeto[j][0]){
                // imprimimos la traduccion sin la letra original abecedario[0]
                for (int k = 1; k < strlen(alfabeto[j]) + 1; k++){   
                    //printf("%c", alfabeto[j][k]);
                    indice++;
                }
                //printf(" ");
                break;
            }
        }
        indice++;
    }

    char *morse = (char*)malloc(indice*sizeof(char));
    //printf("%i\n", indice); //Comprobar que el length esta bien
    //printf("%i\n", strlen(adivinanza));
    int insertar_palabras = 0;

//Una vez calculada cual va a ser la longitud del morse, insertar cada caracter
//Recorremos de nuevo la palabra
    for (int i = 0; i < strlen(adivinanza); i++){
        char letra = toupper(adivinanza[i]);
        //Recorremos de nuevo el abecedario
        for (int j = 0; j < 26; j++){    
            //Cuando coincidan las letras, se insertan los simbolos        
            if (letra == alfabeto[j][0]){
                //Por cada letra, se insertan todos los puntos y rallas
                for (int k = 1; k < strlen(alfabeto[j]); k++){ 
                    //Insertar caracter  
                    morse[insertar_palabras] = alfabeto[j][k];
                    insertar_palabras++;
                }
            }
        }
        //Una vez se haya recorrido el caracter en morse, se inserta un espacio
        if (i < strlen(adivinanza) - 1) {
            morse[insertar_palabras] = ' ';
            insertar_palabras++;
        }
    }
    //Última inserción \0
    morse[insertar_palabras] = '\0';
    
    
    //COMUNICACION RASPBERRY
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;

    // Inicializar Winsock y crear el socket
    int socket = crearSocket(wsa, &sock, &server);
    escribirLog("Se va a crear el socket de comunicacion");
    int error = socket; //Valor para avisar al resto de funciones si se ha podido conectar o no al servidor
    //Si no ocurre ningun error al conectar con el servidor
    if(socket == 0){
        char *respuesta = mandarMensaje(morse, sock);
        if (respuesta == NULL) {
            //Si ha ocurrido algun error, el mismo error se puede poner en la variable de socket para que se
            //corte la conexion y el usuario vuelva a entrar
            printf("Error con el servidor");
            error = 1;          
        }
        // Cerrar el socket y limpiar Winsock
        cerrarSocket(sock);
    }

    //Error al conectar con el servidor, no se inicia la partida -> ERROR = 1
    //FREE
    free(morse);
    morse = NULL;
    return error;
}

int enviarResultadoLeds(char *resultado){
    
    //COMUNICACION RASPBERRY
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;

    // Inicializar Winsock y crear el socket

    int socket = crearSocket(wsa, &sock, &server);
    escribirLog("Se va a crear el socket de comunicacion");
    int error = socket; //Valor para avisar al resto de funciones si se ha podido conectar o no al servidor
    //Si no ocurre ningun error al conectar con el servidor
    if(socket == 0){
        char *respuesta = mandarMensaje(resultado, sock);
        if (respuesta == NULL) {
            //Si ha ocurrido algun error, el mismo error se puede poner en la variable de socket para que se
            //corte la conexion y el usuario vuelva a entrar
            printf("Error con el servidor");
            error = 1;            
        }
        // Cerrar el socket y limpiar Winsock
        cerrarSocket(sock);
    }

    //Error al conectar con el servidor, no se inicia la partida -> ERROR = 1

    return error;
}


char** crearAlfabeto(char *fichero, char** alfabeto){
    //Matriz alfabeto:
    /* [A][.][-]...
       [B][-][-]...
       [C][.][.]...
       [D][.][-]...
       [E][.][.]...
    */

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
        if(c == ' ' || c == ':'){
            continue;
        }else if(c != '\n'){
            size ++;
        }else if(c == '\n'){
            alfabeto[i] = (char*)malloc((size+1)*sizeof(char));
            i++;
            size = 0;
        }
    }
    alfabeto[i] = (char*)malloc((size+1)*sizeof(char));
    
    fila = 0;
    col = 0;
    fseek(archivo, 0, SEEK_SET); 
    while((c = fgetc(archivo))!= EOF){
        if(c == ':' || c == ' '){
            continue;
        }
        else if(c == '\n'){
            alfabeto[fila][col] = '\0';
            fila++;
            col = 0;
        }
        else if(c == '_'){
            alfabeto[fila][col] = ' ';
            col++;
        }
        else{
            alfabeto[fila][col] = c;
            col++;
        }
    }
    fseek(archivo, 0, SEEK_SET);


    fclose(archivo);

return alfabeto;
}

void iniciarLog(const char *fichero) {
    logFich = fopen(fichero, "a");
    if (logFich == NULL) {
        fprintf(stderr, "Error al abrir el fichero log %s\n", fichero);
        exit(1);
    }
}

void escribirLog(const char *mensaje) {
    if (logFich == NULL) {
        fprintf(stderr, "No se ha inicializado el logger\n");
        return;
    }

    time_t hora;
    time(&hora);
    struct tm *local = localtime(&hora);

    fprintf(logFich, "[%02d-%02d-%04d %02d:%02d:%02d] %s\n",
            local->tm_mday, local->tm_mon + 1, local->tm_year + 1900,
            local->tm_hour, local->tm_min, local->tm_sec, mensaje);
    fflush(logFich);
}

void cerrarLog() {
    if (logFich != NULL) {
        fclose(logFich);
        logFich = NULL;
    }
}