#include <stdio.h>
#include <stdlib.h>
#include "pantallas.h"

// He cambiado el nombre del archivo para que sea mas descriptivo

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
    // código para cerrar
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

    char contrasena[20];
    printf("Contrasena: ");
    scanf("%s", contrasena);

    char contrasenaNue[20];
    printf("Repite la contrasena: ");
    scanf("%s", contrasenaNue);

    if (nombre != "" && apellido != "" && nick != "" && contrasena != "" && contrasenaNue != "" && contrasena == contrasenaNue) // No se por qué aquí peta
    {
        printf("Hola, %s. Has sido registrado correctamente!");
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
        pantalla63();
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
    if (*opc == '1')
    {
        pantalla3(); // habra que pasar como parametro el idioma (no pongo tildes por si luego peta, no soy imbecil (tambien con tilde). Si, ya se que duele ver las cosas asi, pero que querais que haga, joe!)
    }
    else if (*opc == '2')
    {
        pantalla3();
    }
    else
    {
        pantalla31();
    }
}

void pantalla3()
{
    system("cls");
    logo();
    printf("                 A D I V I N A !                 \n");
    printf("=================================================\n\n");
    printf("Intentos restantes: \n\n"); // rellenar
    printf("La palabra esta siendo imprimida en los LEDs\n\n");
    printf("Palabras usadas: \n\n");         // rellenar
    printf("Pistas: \n\n");                  // rellenar
    printf("Has acertado las letras: \n\n"); // rellenar
    printf("Opciones: \n");
    printf("1. Insertar palabra\n");
    printf("2. Mostrar pista (Recuerda que tu puntuacion disminuira)\n");
    printf("3. Rendirse\n");
    char opc[2];
    printf("Introduzca la opcion deseada:");
    scanf("%s", opc);
    if (*opc == '1')
    {
        char palabra[15];
        printf("Introduce palabra:");
        scanf("%s", palabra);
        // funcion
        //  si acierta: pantalla32()
    }
    else if (*opc == '2')
    {
        // pista
    }
    else if (*opc == '3')
    {
        pantalla62();
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
    char opc[2];
    printf("Introduzca la opcion deseada:");
    scanf("%s", opc);
    if (*opc == '1')
    {
        pantalla63();
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
        pantalla63();
    }
}

void pantalla41()
{
    system("cls");
    logo();
    printf("         T U S  E S T A D I S T I C A S          \n");
    printf("=================================================\n\n");
    printf("Porcentaje de aciertos: \n");
    printf("Numero de partida jugadas: \n");
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

void pantalla61()
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

void pantalla62()
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
         pantalla3();
    }
}

void pantalla63()
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
    {
        pantalla2();
    }
    else if (*opc == '2')
    {
         //no se que va aqui
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
        cerrar();
    }
    else if (*opc == '2')
    {
         //no se que va aqui
    }
}