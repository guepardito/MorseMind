#ifndef _SQL_UTILS_H_
#define _SQL_UTILS_H_

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


// Funciones CRUD para la estructura Partida
int crearPartida(Partida nuevaPartida);
Partida* leerPartida(int ID);
void actualizarPartida(int ID, Partida datosActualizados);


// Funciones CRUD para la estructura Estadisticas
int crearEstadisticas(Estadisticas nuevasEstadisticas);
Estadisticas* leerEstadisticas(int ID);
void actualizarEstadisticas(int ID, Estadisticas datosActualizados);
void eliminarEstadisticas(int ID);

char* sortear_n_palabra(int ID); //se pasa el ID de usuario
int cargar_datos();

int leerPalabra(char* palabra);
void crearPalabra(Palabra nuevaPalabra);

#endif