#ifndef _SQL_UTILS_H_
#define _SQL_UTILS_H_

typedef struct {
    int ID_Usuario;
    char* Correo;
    char* Nombre;
    char* Apellido;
    char* Apodo;
    char* Contrasenya;
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

// Funciones CRUD para la estructura Usuario
void crearUsuario(Usuario nuevoUsuario);
Usuario* leerUsuario(int ID);
void actualizarUsuario(int ID, Usuario datosActualizados);
void eliminarUsuario(int ID);

// Funciones CRUD para la estructura Partida
void crearPartida(Partida nuevaPartida);
Partida* leerPartida(int ID);
void actualizarPartida(int ID, Partida datosActualizados);
void eliminarPartida(int ID);

// Funciones CRUD para la estructura Palabra
void crearPalabra(Palabra nuevaPalabra);
Palabra* leerPalabra(int ID);
void actualizarPalabra(int ID, Palabra datosActualizados);
void eliminarPalabra(int ID);

// Funciones CRUD para la estructura Tpo_Morse
void crearTipoMorse(Tipo_Morse nuevoTipoMorse);
Tipo_Morse* leerTipoMorse(int ID);
void actualizarTipoMorse(int ID, Tipo_Morse datosActualizados);
void eliminarTipoMorse(int ID);

// Funciones CRUD para la estructura Estadisticas
void crearEstadisticas(Estadisticas nuevasEstadisticas);
Estadisticas* leerEstadisticas(int ID);
void actualizarEstadisticas(int ID, Estadisticas datosActualizados);
void eliminarEstadisticas(int ID);


#endif