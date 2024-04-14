#include "pruebaStatemt.h"
#include "sqlite3.h"
#include "stdlib.h"
#include <stdio.h>
#include "string.h"

sqlite3 *db;

void conectarBaseDeDatos() {
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

// Funciones CRUD para la estructura PARTIDA
int crearPartida(Partida nuevaPartida) {
    sqlite3_stmt *stmt;
    
    char sql[] = "insert into Partida (Puntuacion, Resultado, Fecha, Intentos, ID_Usuario, ID_Morse, ID_Palabra) values (?, ?, ?, ?, ?, ?, ?)";
	
    // Prepara la sentencia SQL
    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
    
    if (result != SQLITE_OK) {
        printf("Error en el statement (INSERTAR)\n");
        printf("%s\n", sqlite3_errmsg(db));
        return result;
    }

    // Prepara los parámetros de la sentencia SQL
    // ...

    // Inserta todos los valores preparados
    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error insertando los valores en la tabla Partida\n");
        sqlite3_finalize(stmt);
        return result;
    }
    
    // Obtiene el ID del último registro insertado
    int last_id = sqlite3_last_insert_rowid(db);
    
    result = sqlite3_finalize(stmt);
    if (result != SQLITE_OK) {
        printf("Error finalizando la declaración (INSERTAR)\n");
        printf("%s\n", sqlite3_errmsg(db));
        return result;
    }

    printf("Declaración finalizada correctamente (INSERTAR)\n");

    return last_id;
}

Partida* leerPartida(int ID) {
    sqlite3_stmt *stmt;
    char sql[] = "select ID_Partida, Puntuacion, Resultado, Fecha, Intentos, ID_Usuario, ID_Morse, ID_Palabra from Partida where ID_Partida = ?";
    
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    if (result != SQLITE_OK) {
        printf("Error en el statement (SELECT)\n");
        printf("%s\n", sqlite3_errmsg(db));
        return NULL;
    }

    printf("Peticion SQL preparada (SELECT) para ID: %d\n", ID);

    result = sqlite3_bind_int(stmt, 1, ID);
    if (result != SQLITE_OK) {
        printf("Error vinculando ID\n");
        printf("%s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return NULL;
    }

    result = sqlite3_step(stmt);
    if (result == SQLITE_ROW) {
        Partida *partida = malloc(sizeof(Partida));
        if (!partida) {
            printf("No se pudo asignar memoria para el usuario\n");
            sqlite3_finalize(stmt);
            return NULL;
        }

        partida->ID_Partida = sqlite3_column_int(stmt, 0);
        partida->Puntuacion = sqlite3_column_int(stmt, 1);
        partida->Resultado = strdup((char *)sqlite3_column_text(stmt, 2));
        partida->Fecha = strdup((char *)sqlite3_column_text(stmt, 3));
        partida->Intentos = sqlite3_column_int(stmt, 4);
        partida->ID_Usuario = sqlite3_column_int(stmt, 5);
        partida->ID_Palabra = sqlite3_column_int(stmt, 6);

        sqlite3_finalize(stmt);
        printf("Statement finalizado correctamente (SELECT)\n");
        return partida;
        
    } else if (result == SQLITE_DONE) {
        printf("No hay ID %d\n", ID);
        sqlite3_finalize(stmt);
        return NULL;
    } else {
        printf("Error en el statement (SELECT)\n");
        printf("%s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return NULL;
    }
}

