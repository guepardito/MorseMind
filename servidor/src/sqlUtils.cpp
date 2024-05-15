#include "sqlite3.h"
#include "sqlUtils.h"
#include <cstring>
#include <cstdio>
#include <stdexcept>

using namespace std;
using namespace tablas;

sqlite3 *db;

SqlUtils::SqlUtils() {
    conectarBaseDeDatos();
}

SqlUtils::~SqlUtils() {
    desconectarBaseDeDatos();
}

void SqlUtils::conectarBaseDeDatos() {
    int result = sqlite3_open("database.sqlite", &db);
    if (result != SQLITE_OK) {
        fprintf(stderr, "Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    sqlite3_exec(db, "DROP DATABASE IF EXISTS database;", NULL, NULL, NULL);
    sqlite3_exec(db, "CREATE DATABASE database CHARACTER SET UTF8 COLLATE UTF8_GENERAL_CI;", NULL, NULL, NULL);
    sqlite3_exec(db, "DROP TABLE IF EXISTS Usuario CASCADE;", NULL, NULL, NULL);
    sqlite3_exec(db, "DROP TABLE IF EXISTS Partida CASCADE;", NULL, NULL, NULL);
    sqlite3_exec(db, "DROP TABLE IF EXISTS Palabra CASCADE;", NULL, NULL, NULL);
    sqlite3_exec(db, "DROP TABLE IF EXISTS Estadisticas CASCADE;", NULL, NULL, NULL);
    sqlite3_exec(db, "DROP TABLE IF EXISTS Tipo_Morse CASCADE;", NULL, NULL, NULL);

    sqlite3_exec(db, "CREATE TABLE Tipo_Morse (ID_Morse INTEGER PRIMARY KEY, NOMBRE_TIPO TEXT);", NULL, NULL, NULL);

    sqlite3_exec(db, "CREATE TABLE Palabra (ID_Palabra INTEGER PRIMARY KEY, PAL_ESP TEXT, PAL_MOR_INT TEXT, PAL_MOR_AM TEXT);", NULL, NULL, NULL);

    sqlite3_exec(db, "CREATE TABLE Estadisticas (ID_Estadistica INTEGER PRIMARY KEY AUTOINCREMENT, Aciertos INTEGER, Fallos INTEGER);", NULL, NULL, NULL);

    sqlite3_exec(db, "CREATE TABLE Usuario (ID_Usuario INTEGER PRIMARY KEY AUTOINCREMENT, Correo TEXT, NOMBRE TEXT, APELLIDO TEXT, APODO TEXT, CONTRASENYA TEXT, ID_Estadistica INTEGER REFERENCES Estadisticas(ID_Estadistica));", NULL, NULL, NULL);
    
    sqlite3_exec(db, "CREATE TABLE Partida (ID_Partida INTEGER PRIMARY KEY AUTOINCREMENT, Puntuacion INTEGER, Resultado TEXT, Fecha TEXT, Intentos INTEGER, ID_Usuario INTEGER REFERENCES Usuario(ID_Usuario), ID_Morse INTEGER REFERENCES Tipo_Morse(ID_MORSE), ID_Palabra INTEGER REFERENCES Palabra(ID_Palabra));", NULL, NULL, NULL);
}
void desconectarBaseDeDatos() {
    sqlite3_close(db);
}

// Funciones CRUD para la estructura Usuario
int SqlUtils::crearUsuario(Usuario nuevoUsuario) {
    string sql = "insert into Usuario (Correo, Nombre, Apellido, Apodo, Contrasenya, ID_Estadistica) VALUES (?, ?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return -1;
    }

    sqlite3_bind_text(stmt, 1, nuevoUsuario.getCorreo().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, nuevoUsuario.getNombre().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, nuevoUsuario.getApellido().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, nuevoUsuario.getApodo().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, nuevoUsuario.getContrasenya().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 6, nuevoUsuario.getID_Estadistica());

    int result = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return result == SQLITE_DONE ? 0 : -1;
}

Usuario* SqlUtils::leerUsuario(const char* apodo) {
    string sql = "select ID_USUARIO, CORREO, NOMBRE, APELLIDO, APODO, CONTRASENYA, ID_ESTADISTICA from USUARIO where APODO = ?";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return nullptr;
    }

    sqlite3_bind_text(stmt, 1, apodo, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        Usuario* usuario = new Usuario(
            sqlite3_column_int(stmt, 0),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)),
            sqlite3_column_int(stmt, 6)
        );
        sqlite3_finalize(stmt);
        return usuario;
    }
    
    sqlite3_finalize(stmt);
    return nullptr;
}

// Funciones CRUD para la estructura Partida
int SqlUtils::crearPartida(Partida nuevaPartida) {
    // TODO
}
Partida* SqlUtils::leerPartida(int id) {
    string sql = "SELECT * FROM Partida WHERE ID_Partida = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return nullptr;
    }

    sqlite3_bind_int(stmt, 1, id);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        Partida* partida = new Partida(
            sqlite3_column_int(stmt, 0),
            sqlite3_column_int(stmt, 1),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)),
            sqlite3_column_int(stmt, 4),
            sqlite3_column_int(stmt, 5),
            sqlite3_column_int(stmt, 6),
            sqlite3_column_int(stmt, 7)
        );
        sqlite3_finalize(stmt);
        return partida;
    }

    sqlite3_finalize(stmt);
    return nullptr;
}
void SqlUtils::actualizarPartida(int id, Partida datosActualizados) {
    string sql = "UPDATE Partida SET Puntuacion = ?, Resultado = ?, Fecha = ?, Intentos = ?, ID_Usuario = ?, ID_Morse = ?, ID_Palabra = ? WHERE ID_Partida = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        throw runtime_error("Error al preparar la sentencia SQL");
    }

    sqlite3_bind_int(stmt, 1, datosActualizados.getPuntuacion());
    sqlite3_bind_text(stmt, 2, datosActualizados.getResultado().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, datosActualizados.getFecha().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, datosActualizados.getIntentos());
    sqlite3_bind_int(stmt, 5, datosActualizados.getID_Usuario());
    sqlite3_bind_int(stmt, 6, datosActualizados.getID_Morse());
    sqlite3_bind_int(stmt, 7, datosActualizados.getID_Palabra());
    sqlite3_bind_int(stmt, 8, id);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw runtime_error("Error al ejecutar la sentencia SQL");
    }

    sqlite3_finalize(stmt);
}

// Funciones CRUD para la estructura Palabra
void SqlUtils::crearPalabra(Palabra nuevaPalabra) {
    string sql = "INSERT INTO Palabra (ID_Palabra, Pal_Esp, Pal_Mor_Int, Pal_Mor_Am) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        throw runtime_error("Error al preparar la sentencia SQL");
    }

    sqlite3_bind_int(stmt, 1, nuevaPalabra.getID_Palabra());
    sqlite3_bind_text(stmt, 2, nuevaPalabra.getPal_Esp().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, nuevaPalabra.getPal_Mor_Int().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, nuevaPalabra.getPal_Mor_Am().c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw runtime_error("Error al ejecutar la sentencia SQL");
    }

    sqlite3_finalize(stmt);
}
int SqlUtils::leerPalabra(char* palabra) {
    string sql = "SELECT ID_Palabra FROM Palabra WHERE Pal_Esp = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
    return -1;
    }

    sqlite3_bind_text(stmt, 1, palabra, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, palabra, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, palabra, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
    int id = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return id;
    }

    sqlite3_finalize(stmt);
    return -1;
}
// void actualizarPalabra(int id, const Palabra& datosActualizados);
// void eliminarPalabra(int id);

// Funciones CRUD para la estructura Tipo_Morse
void SqlUtils::crearTipoMorse(Tipo_Morse nuevoTipoMorse) {

}
Tipo_Morse* SqlUtils::leerTipoMorse(int id) {

}

// Funciones CRUD para la estructura Estadisticas
int SqlUtils::crearEstadisticas(Estadisticas nuevasEstadisticas) {

}
Estadisticas* SqlUtils::leerEstadisticas(int id) {

}
void SqlUtils::actualizarEstadisticas(int id, Estadisticas datosActualizados) {

}
void SqlUtils::eliminarEstadisticas(int id) {

}

// Otras funciones
string SqlUtils::sortear_n_palabra(int idUsuario) {

}
int SqlUtils::cargar_datos() {

}
void SqlUtils::hacerYImprimirRankings() {

}
void SqlUtils::obtenerTraducciones(char* nick, Usuario usu) {

}