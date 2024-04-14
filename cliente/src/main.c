#include <stdio.h>
#include "pantallas.h"
#include "sqlUtils.h"


int main(void)
{
  conectarBaseDeDatos();
  Tipo_Morse i;
  i.ID_Morse = 1;
  i.Nombre_Tipo = "Internacional";
  Tipo_Morse a;
  a.ID_Morse = 2;
  a.Nombre_Tipo = "Americano";
  crearTipoMorse(i);
  crearTipoMorse(a);
  cargar_datos();
  pantalla1();
  desconectarBaseDeDatos();
  
}