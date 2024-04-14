#ifndef _PRUEBASTATENT_H_
#define _PRUEBASTATENT_H_

#include "sqlite3.h"
#include "stdlib.h"
#include <stdio.h>

typedef struct {
    int ID_Usuario;
    char* Correo;
    char* Nombre;
    char* Apellido;
    char* Apodo;
    char* Contrasenya;
    int ID_Estadistica;
} Usuario;

typedef struct {
    int ID_Partida;
    int Puntuacion;
    char* Resultado;
    char* Fecha;
    int Intentos;
    int ID_Usuario;
    int ID_Morse;
    int ID_Palabra;
} Partida;

typedef struct
{
  int ID_Palabra;
  char* Pal_Esp;
  char* Pal_Mor_Int;
  char* Pal_Mor_Am;
} Palabra;

typedef struct
{
  int ID_Morse;
  char* Nombre_Tipo;
} Tipo_Morse;

typedef struct
{
  int ID_Estadistica;
  int Aciertos;
  int fallos;
} Estadisticas;

void conectarBaseDeDatos();
void desconectarBaseDeDatos();
void crearPartida(Partida nuevaPartida);
int leerPalabra(char* palabra);
void actualizarPalabra(int ID, Palabra datosActualizados);
void eliminarPalabra(int ID);
int crearUsuario(Usuario nuevoUsuario);
Usuario* leerUsuario(char* Apodo);


#endif