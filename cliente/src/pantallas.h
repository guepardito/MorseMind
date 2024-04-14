 #ifndef _PANTALLAS_H_
#define _PANTALLAS_H_
#include "sqlUtils.h"

void logo();
void pantalla1();
void pantalla11();
void pantalla12();
void cerrar();
void pantalla2(char *nick, Usuario  *usuario);
void pantalla31(char *nick, Usuario *usu);
void pantalla32(char *nick, int puntuacion, Partida *nuevaPartida, Usuario *usu);
void display_pantalla3(int intentos_restantes, char** palabras_usadas, char* letras_conocidas, char* pista, int puntuacion, int fallado, int mal_input, int pista_mostrada, char** alfabeto, char* adivinanza);
void pantalla3(char* nick, int intentos_restantes,char** palabras_usadas, char* letras_conocidas, char*pista, int puntuacion, int fallado, int mal_input, int pista_mostrada, char** alfabeto, Partida *nuevapartida, Usuario *usu, char* adivinanza);
void pantalla4(char *nick, Usuario *usu);
void pantalla41(char *nick, Usuario *usu);
void pantalla5(char *nick, Usuario *usu);  
void pantalla61();
void pantalla62(char* nick, int intentos_restantes, char** palabras_usadas, char* letras_conocidas, char* pista, int puntuacion, char** alfabeto, Partida *nuevaPartida, Usuario *usu, char* adivinanza);
void pantalla63(int pantalla, char *nick, Usuario *usu);
void pantalla64();
void pantalla65(int pantalla, char* nick, Usuario *usu);

char* sortear_palabra(int ID_usuario);
void mostrar_palabra_LEDS(char* adivinanza, char** alfabeto);
char** crearAlfabeto(char *fichero, char** alfabeto);
void guardarPuntuacion(int puntuacion);


#endif