#include <stdio.h>
#include "pantallas.h"
#include "sqlUtils.h"
#include "servidorCliente.h"


int main(void)
{
  conectarBaseDeDatos();
  //int serv = mainServidor();    //Esta comentado pues en esta primera entrega no lo necesitamos.
  Tipo_Morse i;
  i.ID_Morse = 1;
  i.Nombre_Tipo = "Internacional";
  Tipo_Morse a;
  a.ID_Morse = 2;
  a.Nombre_Tipo = "Americano";
  crearTipoMorse(i);
  crearTipoMorse(a);
  cargar_datos();
  pantallaInicio();
  desconectarBaseDeDatos();
  
}