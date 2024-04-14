#include <stdio.h>
#include "pruebaStatemt.h"


int main(void)
{
  conectarBaseDeDatos();
  cargar_datos();
  Tipo_Morse t;
  t.ID_Morse = 1;
  t.Nombre_Tipo = "Americano";

  Tipo_Morse t2;
  t.ID_Morse = 2;
  t.Nombre_Tipo = "Internacional";

  crearTipoMorse(t);
  /*
  Partida p;
  Usuario usu;
  usu.Nombre = "hai";
  usu.Apellido = "gon";
  usu.Apodo = "a";
  usu.Contrasenya= "12";
  usu.Correo = "Jj";
  usu.ID_Estadistica = 1;
  usu.ID_Usuario = 10;
  Usuario *usu2;
  crearUsuario(usu);
  usu2 = leerUsuario("dsf");
  printf("ZORRA: %s", usu2->ID_Usuario);

  p.Fecha = "JD";
  p.ID_Morse= 1;
  p.ID_Palabra=2;
  p.ID_Partida=5;
  p.ID_Usuario=567;
  p.Intentos=2;
  p.Puntuacion=456;
  p.Resultado="acertado";
  
  /*
  crearPartida(p);
  //printf("AAAAAAAAAAA\n");
  Partida *p2;
  //printf("Punt %i\n", (p).Puntuacion);
  p2 = leerPartida(p.ID_Partida);
  printf("JNJB");
  if(p2 = NULL){
    printf("%s", "funca");
  }
  //printf("Punt2 %i\n", (*p2).Puntuacion);
  */
  desconectarBaseDeDatos();
  
}