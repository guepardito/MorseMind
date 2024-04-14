#include "pruebaStatemt.h"
#include "sqlite3.h"
#include "stdlib.h"
#include <stdio.h>

sqlite3 *db;

void conectarBaseDeDatos() {
    int result = sqlite3_open("database.db", &db);
    if (result != SQLITE_OK) {
        fprintf(stderr, "Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        exit(1);
    }
    sqlite3_exec(db, "DROP DATABASE IF EXISTS database;", NULL, NULL, NULL);
    sqlite3_exec(db, "CREATE DATABASE database CHARACTER SET UTF8 COLLATE UTF8_GENERAL_CI;", NULL, NULL, NULL);
    sqlite3_exec(db, "DROP TABLE IF EXISTS Partida CASCADE;", NULL, NULL, NULL);
    
    sqlite3_exec(db, "CREATE TABLE Partida (ID_Partida INTEGER PRIMARY KEY AUTOINCREMENT, Puntuacion INTEGER, Resultado TEXT, Fecha TEXT, Intentos INTEGER, ID_Usuario INTEGER REFERENCES Usuario(ID_Usuario), ID_Morse INTEGER REFERENCES Tipo_Morse(ID_MORSE), ID_Palabra INTEGER REFERENCES Palabra(ID_Palabra));", NULL, NULL, NULL);

}

void desconectarBaseDeDatos() {
  sqlite3_close(db);
}

// Funciones CRUD para la estructura PARTIDA
void crearPartida(Partida nuevaPartida) {
    if (db == NULL) {
        printf("Error: No se pudo conectar a la base de datos.\n");
        return;
    }

    const char *checkTableQuery = "SELECT name FROM sqlite_master WHERE type='table' AND name='Partida'";
    sqlite3_stmt *checkStmt;
    int result = sqlite3_prepare_v2(db, checkTableQuery, -1, &checkStmt, NULL);
    
    if (result != SQLITE_OK) {
        printf("Error al comprobar la existencia de la tabla Partida\n");
        printf("%s\n", sqlite3_errmsg(db));
        return;
    }

    result = sqlite3_step(checkStmt);
    if (result != SQLITE_ROW) {
        printf("La tabla Partida no existe\n");
        sqlite3_finalize(checkStmt);
        return;
    }
    
    sqlite3_finalize(checkStmt);

    sqlite3_stmt *stmt;
    char sql[] = "insert into Partida (Puntuacion, Resultado, Fecha, Intentos, ID_Usuario, ID_Morse, ID_Palabra) values (?, ?, ?, ?, ?, ?, ?)";
    
    result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);

}


Partida* leerPartida(int ID) {
	sqlite3_stmt *stmt;
    char sql[] = "select ID_Partida, Puntuacion, Resultado, Fecha, Intentos, ID_Usuario, ID_Morse, ID_Palabra from Partida where ID_Partida = ?";
    
    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;

    if (result != SQLITE_OK) {
		printf("Error en el statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
		}

    printf("Peticion SQL preparada (SELECT)\n");
	sqlite3_bind_text(stmt, 1, ID, -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        Partida *partida = malloc(sizeof(Partida));
        if (!partida) {
            printf("No se pudo asignar memoria para el usuario\n");
            sqlite3_finalize(stmt);
            return NULL;
        }
    printf("HIJO PUTA");
    /*
        partida->ID_Partida = sqlite3_column_int(stmt, 0);
        partida->Puntuacion = sqlite3_column_int(stmt, 1);
        partida->Resultado = strdup((char *)sqlite3_column_text(stmt, 2));
        partida->Fecha = strdup((char *)sqlite3_column_text(stmt, 3));
        partida->Intentos = sqlite3_column_int(stmt, 4);
        partida->ID_Usuario = sqlite3_column_int(stmt, 5);
        partida->ID_Morse = sqlite3_column_int(stmt, 6);
        partida->ID_Palabra = sqlite3_column_int(stmt, 7);

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizando el statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
        //Liberar memoria si no se ha hecho correctamente
        free(partida->Resultado);
        free(partida->Fecha);
        free(partida);
		return result;
	}
	printf("Statement preparado finalizado (SELECT)\n");
    return partida;
    */
    }
}

// Funciones CRUD para la estructura USUARIO
int crearUsuario(Usuario nuevoUsuario){
    sqlite3_stmt *stmt;
    
    //Al ser ID autoincremental, no es necesario insetarlo
    char sql[] = "insert into Usuario (Correo, Nombre, Apellido, Apodo, Contrasenya, ID_Estadistica) values (?, ?, ?, ?, ?, ?)";
	//Prepara la sentencia SQL
    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
    //tstrlen(sql) -> Mas 1 byte para incluir el carácter nulo (\0) 
    //&stmt -> Este puntero apuntara a la estructura sqlite3_stmt que contiene la sentencia SQL compilada.
    //NULL -> Puntero a un puntero a un caracter, donde se almacena el resto de la sentencia SQL no procesada. No lo vamos a usar en este caso, por eso es NULL.
	if (result != SQLITE_OK) {
		printf("Error en el statement (INSERTAR)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    //Si no hay error se ha preparado correctamente la solicitud
    printf("Peticion SQL preparada (INSERTAR)\n");

    //Preparamos cada valor de nuevoUsuario en la BD
    //Correo
	result = sqlite3_bind_text(stmt, 1, nuevoUsuario.Correo, strlen(nuevoUsuario.Correo), SQLITE_STATIC);
    //SQLITE_STATIC -> Vincula un valor a un paramtro de una sentencia preparada
	if (result != SQLITE_OK) {
		printf("Error insertando parametros\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    //Nombre
    result = sqlite3_bind_text(stmt, 2, nuevoUsuario.Nombre, strlen(nuevoUsuario.Nombre), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error insertando parametros\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    //Apellido
    result = sqlite3_bind_text(stmt, 3, nuevoUsuario.Apellido, strlen(nuevoUsuario.Apellido), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error insertando parametros\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    //Apodo
    result = sqlite3_bind_text(stmt, 4, nuevoUsuario.Apodo, strlen(nuevoUsuario.Apodo), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error insertando parametros\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    //Contrasenya
    result = sqlite3_bind_text(stmt, 5, nuevoUsuario.Contrasenya, strlen(nuevoUsuario.Contrasenya), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error insertando parametros\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    //ID_Estadistica
    result = sqlite3_bind_int(stmt, 6, nuevoUsuario.ID_Estadistica);
	if (result != SQLITE_OK) {                                          
		printf("Error insertando parametros\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    //Insertamos todos los valores preparados
    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error insertando los valores en la tabla Usuario\n");
        sqlite3_finalize(stmt);
        return;
    }
    
    result = sqlite3_finalize(stmt);
    if (result != SQLITE_OK) {
        printf("Error finalizando la declaracion (INSERTAR)\n");
        printf("%s\n", sqlite3_errmsg(db));
        return;
    }


	printf("Declarcion finalizada correctamente (INSERTAR)\n");

	return SQLITE_OK;

}

Usuario* leerUsuario(char* Apodo) {
    sqlite3_stmt *stmt;
    char sql[] = "select ID_USUARIO, CORREO, NOMBRE, APELLIDO, APODO, CONTRASENYA, ID_ESTADISTICA from USUARIO where APODO = ?";
    
    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
    
    if (result != SQLITE_OK) {
        printf("Error en el statement (SELECT)\n");
        printf("%s\n", sqlite3_errmsg(db));
        return NULL;
    }

    printf("Peticion SQL preparada (SELECT)\n");

    sqlite3_bind_text(stmt, 1, Apodo, -1, SQLITE_TRANSIENT);

    result = sqlite3_step(stmt);
    if (result == SQLITE_ROW) {
        Usuario *usuario = malloc(sizeof(Usuario));
        if (!usuario) {
            printf("No se pudo asignar memoria para el usuario\n");
            sqlite3_finalize(stmt);
            return NULL;
        }

        usuario->ID_Usuario = sqlite3_column_int(stmt, 0);
        usuario->Correo = strdup((char *)sqlite3_column_text(stmt, 1));
        usuario->Nombre = strdup((char *)sqlite3_column_text(stmt, 2));
        usuario->Apellido = strdup((char *)sqlite3_column_text(stmt, 3));
        usuario->Apodo = strdup((char *)sqlite3_column_text(stmt, 4));
        usuario->Contrasenya = strdup((char *)sqlite3_column_text(stmt, 5));
        usuario->ID_Estadistica = sqlite3_column_int(stmt, 6);

        sqlite3_finalize(stmt);
        printf("Statement preparado finalizado (SELECT)\n");
        return usuario;
        
    } else if (result == SQLITE_DONE) {
        printf("No se encontró ningún usuario con el Apodo especificado.\n");
        sqlite3_finalize(stmt);
        return NULL;

    } else {
        printf("Error en la ejecución de la consulta (SELECT)\n");
        printf("%s\n", sqlite3_errmsg(db));

        // Liberar memoria si es necesario
        sqlite3_finalize(stmt);
        return NULL;
    }
}
