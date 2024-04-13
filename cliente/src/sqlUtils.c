#include "sqlUtils.h"
#include "sqlite3.h"

#include <stdio.h>

sqlite3 *db;

void conectarBaseDeDatos() {
    int result = sqlite3_open("database.db", &db);
    if (result != SQLITE_OK) {
        fprintf(stderr, "Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        exit(1);
    }
    
    sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS Usuario (ID_Usuario INTEGER PRIMARY KEY AUTOINCREMENT, Correo TEXT, NOMBRE TEXT, APELLIDO TEXT, APODO TEXT, CONTRASENYA TEXT, ID_Estadistica INTEGER REFERENCES Estadisticas(ID_Estadistica));", NULL, NULL, NULL);
    
    sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS Partida (ID_Partida INTEGER AUTOINCREMENT, Puntuacion INTEGER, Resultado TEXT, Fecha TEXT, Intentos INTEGER, ID_Usuario INTEGER REFERENCES Usuario(ID_Usuario), ID_Morse INTEGER REFERENCES Tipo_Morse(ID_MORSE), ID_Palabra INTEGER REFERENCES Palabra(ID_Palabra), PRIMARY KEY(ID_Partida, ID_Usuario, ID_Morse, ID_Palabra, Fecha));", NULL, NULL, NULL);
        
    sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS Palabra (ID_Palabra INTEGER PRIMARY KEY AUTOINCREMENT, PAL_ESP TEXT, PAL_MOR_INT TEXT, PAL_MOR_AM TEXT);", NULL, NULL, NULL);
-
    sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS Estadisticas (ID_Estadistica INTEGER PRIMARY KEY AUTOINCREMENT, Aciertos INTEGER, Fallos INTEGER);", NULL, NULL, NULL);

    sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS Tipo_Morse (ID_Palabra INTEGER PRIMARY KEY AUTOINCREMENT, NOMBRE_TIPO TEXT);", NULL, NULL, NULL);

}
void desconectarBaseDeDatos() {
  sqlite3_close(db);
}

// Funciones CRUD para la estructura Usuario
void crearUsuario(Usuario nuevoUsuario);
Usuario* leerUsuario(int ID){
    //char sql[] = "select ";
}
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