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



// Funciones CRUD para la estructura PALABRA
void crearPalabra(Palabra nuevaPalabra){
    
    sqlite3_stmt *stmt;
    
    char sql[] = "insert into Palabra (ID_Palabra PAL_ESP, PAL_MOR_INT, PAL_MOR_AM) values (?, ?, ?, ?)";
	
    //Prepara la sentencia SQL
    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
    
	if (result != SQLITE_OK) {
		printf("Error en el statement (INSERTAR)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    //Si no hay error se ha preparado correctamente la solicitud
    printf("Peticion SQL preparada (INSERTAR)\n");

    //Preparamos cada valor de nuevaPalabra en la BD
    // ID
    result = sqlite3_bind_int(stmt, 1, nuevaPalabra.ID_Palabra);

    //Pal_Esp
	result = sqlite3_bind_text(stmt, 2, nuevaPalabra.Pal_Esp, sizeof(nuevaPalabra.Pal_Esp), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error insertando parametros\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    //Pal_mor_int
    result = sqlite3_bind_text(stmt, 3, nuevaPalabra.Pal_Mor_Int, sizeof(nuevaPalabra.Pal_Mor_Int), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error insertando parametros\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    //Pal_Mor_Am
    result = sqlite3_bind_text(stmt, 4, nuevaPalabra.Pal_Mor_Am, strlen(nuevaPalabra.Pal_Mor_Am), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error insertando parametros\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    //Insertamos todos los valores preparados
    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error insertando los valores en la tabla Palabra\n");
        sqlite3_finalize(stmt);
        return;
    }
    
    result = sqlite3_finalize(stmt);
    if (result != SQLITE_OK) {
        printf("Error finalizando la declaracion (INSERT)\n");
        printf("%s\n", sqlite3_errmsg(db));
        return;
    }

	printf("Declarcion finalizada correctamente (INSERT)\n");

	return SQLITE_OK;
    
}

int leerPalabra(char* palabra) {
    sqlite3_stmt *stmt;
    char sql[] = "select ID_Palabra from Palabra where Pal_Esp = ?";
    
    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
    
    if (result != SQLITE_OK) {
        printf("Error en el statement (SELECT)\n");
        printf("%s\n", sqlite3_errmsg(db));
        return result;
    }

    printf("Peticion SQL preparada (SELECT)\n");

    // Vincular el parámetro de la palabra
    result = sqlite3_bind_text(stmt, 1, palabra, strlen(palabra), SQLITE_STATIC);
    if (result != SQLITE_OK) {
        printf("Error vinculando palabra\n");
        printf("%s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return result;
    }

    int id_pal = -1;  // Inicializar con un valor predeterminado

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        id_pal = sqlite3_column_int(stmt, 0);
    } else {
        printf("No se encontró la palabra: %s\n", palabra);
    }

    // Finalizar el statement
    result = sqlite3_finalize(stmt);
    if (result != SQLITE_OK) {
        printf("Error finalizando el statement (SELECT)\n");
        printf("%s\n", sqlite3_errmsg(db));
        return result;
    }

    printf("Statement finalizado (SELECT)\n");

    return id_pal;
}
