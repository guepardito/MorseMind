#ifndef _PANTALLAS_H_
#define _PANTALLAS_H_
#include "sqlUtils.h"

void logo();
void pantallaInicio();
void pantallaRegistro();
void pantallaLogin();
void cerrar();
void pantallaPrincipal(char *nick, Usuario  *usuario);
void pantallaCrearAlfabeto(char *nick, Usuario *usu);
int displayPantallaJuego(int intentos_restantes, char** palabras_usadas, char* letras_conocidas, char* pista, int puntuacion, int fallado, int mal_input, int pista_mostrada, char** alfabeto, char* adivinanza);
void pantallaJuego(char* nick, int intentos_restantes,char** palabras_usadas, char* letras_conocidas, char*pista, int puntuacion, int fallado, int mal_input, int pista_mostrada, char** alfabeto, Partida *nuevapartida, Usuario *usu, char* adivinanza);
void pantallaRanking(char *nick, Usuario *usu);
void pantallaEstadisticas(char *nick, Usuario *usu);
void pantallaTraducciones(char *nick, Usuario *usu);  
void pantallaRendir(char* nick, int intentos_restantes, char** palabras_usadas, char* letras_conocidas, char* pista, int puntuacion, char** alfabeto, Partida *nuevaPartida, Usuario *usu, char* adivinanza);
void pantallaAvisoPPrincipal(int pantalla, char *nick, Usuario *usu, char** alfabeto);
void pantallaAvisoCierre();
void pantallaAvisoInicio(int pantalla, char* nick, Usuario *usu);

char* sortearPalabra(int ID_usuario);
int mostrarPalabraLEDS(char* adivinanza, char** alfabeto);
char** crearAlfabeto(char *fichero, char** alfabeto);
void guardarPuntuacion(int puntuacion);

void iniciarLog(const char *fichero);
void escribirLog(const char *mensaje);
void cerrarLog();

int enviarResultadoLeds(char *resultado);

void obtener_ip(char *ip_buffer, size_t buffer_size);

#endif