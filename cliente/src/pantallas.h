 #ifndef _PANTALLAS_H_
#define _PANTALLAS_H_
#include "sqlUtils.h"

void logo();
void pantalla1();
void pantalla11();
void pantalla12();
void cerrar();
void pantalla2();
void pantalla31();
void pantalla32(char *nick, int puntuacion, Partida nuevaPartida);
void display_pantalla3(int intentos_restantes, char** palabras_usadas, char* letras_conocidas, char* pista, int puntuacion, int fallado, int mal_input, int pista_mostrada, char** alfabeto, char* adivinanza);
void pantalla3(char* nick, int intentos_restantes,char** palabras_usadas, char* letras_conocidas, char*pista, int puntuacion, int fallado, int mal_input, int pista_mostrada, char** alfabeto, Partida nuevapartida);
void pantalla4();
void pantalla41();
void pantalla5();
void pantalla61();
void pantalla62(char* nick, int intentos_restantes, char** palabras_usadas, char* letras_conocidas, char* pista, int puntuacion, char** alfabeto, Partida nuevaPartida);
void pantalla63(int pantalla, char *nick);
void pantalla64();
void pantalla65(int pantalla, char* nick);

char* sortear_palabra(int ID_usuario);
void mostrar_palabra_LEDS(char* adivinanza, char** alfabeto); //por ahora solo imprime por pantalla
char** crearAlfabeto(char *fichero, char** alfabeto);
void guardarPuntuacion(int puntuacion); //deberia guardarla en un fichero, ahora imprime por pantalla


#endif