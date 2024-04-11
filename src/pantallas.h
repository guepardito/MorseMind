#ifndef _PANTALLAS_H_
#define _PANTALLAS_H_


void logo();
void pantalla1();
void pantalla11();
void pantalla12();
void cerrar();
void pantalla2();
void pantalla31();
void pantalla32(char *nick, int puntuacion);
void display_pantalla3(int intentos_restantes, char** palabras_usadas, char* letras_conocidas, char* pista, int puntuacion, int fallado, int mal_input, int pista_mostrada);
void pantalla3(char* nick, int intentos_restantes,char** palabras_usadas, char* letras_conocidas, char*pista, int puntuacion, int fallado, int mal_input, int pista_mostrada);
void pantalla4();
void pantalla41();
void pantalla5();
void pantalla61();
void pantalla62(char* nick, int intentos_restantes, char** palabras_usadas, char* letras_conocidas, char* pista, int puntuacion);
void pantalla63(int pantalla, char *nick);
void pantalla64();
void pantalla65(int pantalla, char* nick);

char* sortear_palabra();// falta meterle el usuario para que no le toque la misma varias veces
void mostrar_palabra_LEDS(char* adivinanza); //por ahora solo imprime por pantalla
void crearAlfabeto(char *fichero);
void guardarPuntuacion(int puntuacion); //deberia guardarla en un fichero, ahora imprime por pantalla

#endif