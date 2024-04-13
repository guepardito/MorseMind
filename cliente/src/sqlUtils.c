#include "sqlUtils.h"
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
    sqlite3_exec(db, "DROP TABLE IF EXISTS Usuario CASCADE;", NULL, NULL, NULL);
    sqlite3_exec(db, "DROP TABLE IF EXISTS Partida CASCADE;", NULL, NULL, NULL);
    sqlite3_exec(db, "DROP TABLE IF EXISTS Palabra CASCADE;", NULL, NULL, NULL);
    sqlite3_exec(db, "DROP TABLE IF EXISTS Estadisticas CASCADE;", NULL, NULL, NULL);
    sqlite3_exec(db, "DROP TABLE IF EXISTS Tipo_Morse CASCADE;", NULL, NULL, NULL);

    sqlite3_exec(db, "CREATE TABLE Usuario (ID_Usuario INTEGER PRIMARY KEY AUTOINCREMENT, Correo TEXT, NOMBRE TEXT, APELLIDO TEXT, APODO TEXT, CONTRASENYA TEXT, ID_Estadistica INTEGER REFERENCES Estadisticas(ID_Estadistica));", NULL, NULL, NULL);
    
    sqlite3_exec(db, "CREATE TABLE Partida (ID_Partida INTEGER AUTOINCREMENT, Puntuacion INTEGER, Resultado TEXT, Fecha TEXT, Intentos INTEGER, ID_Usuario INTEGER REFERENCES Usuario(ID_Usuario), ID_Morse INTEGER REFERENCES Tipo_Morse(ID_MORSE), ID_Palabra INTEGER REFERENCES Palabra(ID_Palabra), PRIMARY KEY(ID_Partida, ID_Usuario, ID_Morse, ID_Palabra, Fecha));", NULL, NULL, NULL);
        
    sqlite3_exec(db, "CREATE TABLE Palabra (ID_Palabra INTEGER PRIMARY KEY AUTOINCREMENT, PAL_ESP TEXT, PAL_MOR_INT TEXT, PAL_MOR_AM TEXT);", NULL, NULL, NULL);

    sqlite3_exec(db, "CREATE TABLE Estadisticas (ID_Estadistica INTEGER PRIMARY KEY AUTOINCREMENT, Aciertos INTEGER, Fallos INTEGER);", NULL, NULL, NULL);

    sqlite3_exec(db, "CREATE TABLE Tipo_Morse (ID_Morse INTEGER PRIMARY KEY AUTOINCREMENT, NOMBRE_TIPO TEXT);", NULL, NULL, NULL);

}

void desconectarBaseDeDatos() {
  sqlite3_close(db);
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

Usuario* leerUsuario(char* Apodo){
    sqlite3_stmt *stmt;
    char sql[] = "select ID_USUARIO, CORREO, NOMBRE, APELLIDO, APODO, CONTRASENYA, ID_ESTADISTICA from USUARIO where APODO = ?";
    
    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
    
    if (result != SQLITE_OK) {
		printf("Error en el statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
		}

    printf("Peticion SQL preparada (SELECT)\n");
	//sqlite3_bind_text(stmt, 1, Apodo, -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
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
        return usuario;
    } else {
			sqlite3_finalize(stmt);
        return NULL;
    }
}

// Funciones CRUD para la estructura PARTIDA
void crearPartida(Partida nuevaPartida) {

    sqlite3_stmt *stmt;
    
    char sql[] = "insert into Partida (Puntuacion, Resultado, Fecha, Intentos, ID_Usuario, ID_Morse, ID_Palabra) values (?, ?, ?, ?, ?, ?, ?)";
	
    //Prepara la sentencia SQL
    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
    
	if (result != SQLITE_OK) {
		printf("Error en el statement (INSERTAR)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    //Si no hay error se ha preparado correctamente la solicitud
    printf("Peticion SQL preparada (INSERTAR)\n");

    //Preparamos cada valor de nuevaPartida en la BD
    //Puntuacion
	result = sqlite3_bind_int(stmt, 1, nuevaPartida.Puntuacion);
	if (result != SQLITE_OK) {
		printf("Error insertando parametros\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    //Resultado
    result = sqlite3_bind_text(stmt, 2, nuevaPartida.Resultado, strlen(nuevaPartida.Resultado), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error insertando parametros\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    //Fecha
    result = sqlite3_bind_text(stmt, 3, nuevaPartida.Fecha, strlen(nuevaPartida.Fecha), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error insertando parametros\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    //Intentos
    result = sqlite3_bind_int(stmt, 4, nuevaPartida.Intentos);
	if (result != SQLITE_OK) {
		printf("Error insertando parametros\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    //ID_Usuario
    result = sqlite3_bind_int(stmt, 5, nuevaPartida.ID_Usuario);
	if (result != SQLITE_OK) {
		printf("Error insertando parametros\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    //ID_Morse
    result = sqlite3_bind_int(stmt, 6, nuevaPartida.ID_Morse);
	if (result != SQLITE_OK) {                                          
		printf("Error insertando parametros\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    //ID_Palabra
    result = sqlite3_bind_int(stmt, 7, nuevaPartida.ID_Palabra);
	if (result != SQLITE_OK) {
		printf("Error insertando parametros\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    //Insertamos todos los valores preparados
    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error insertando los valores en la tabla Partida\n");
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
	//sqlite3_bind_text(stmt, 1, ID, -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
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
        return partida;
    } else {
				sqlite3_finalize(stmt);
        return NULL;
    }
}

// Funciones CRUD para la estructura PALABRA
void crearPalabra(Palabra nuevaPalabra){
    
    sqlite3_stmt *stmt;
    
    char sql[] = "insert into Palabra (PAL_ESP, PAL_MOR_INT, PAL_MOR_AM) values (?, ?, ?)";
	
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
    //Pal_Esp
	result = sqlite3_bind_text(stmt, 1, nuevaPalabra.Pal_Esp, sizeof(nuevaPalabra.Pal_Esp), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error insertando parametros\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    //Pal_mor_int
    result = sqlite3_bind_text(stmt, 2, nuevaPalabra.Pal_Mor_Int, sizeof(nuevaPalabra.Pal_Mor_Int), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error insertando parametros\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    //Pal_Mor_Am
    result = sqlite3_bind_text(stmt, 3, nuevaPalabra.Pal_Mor_Am, strlen(nuevaPalabra.Pal_Mor_Am), SQLITE_STATIC);
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
int leerPalabra(char* palabra){
	sqlite3_stmt *stmt;
    char sql[] = "select ID_Palabra from Palabra where Pal_Esp = ?";
    
    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
    
    if (result != SQLITE_OK) {
		printf("Error en el statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
		}

    printf("Peticion SQL preparada (SELECT)\n");

		int id_pal;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        id_pal = sqlite3_column_int(stmt, 0);

        sqlite3_finalize(stmt);
        return id_pal;
    } else {
				sqlite3_finalize(stmt);
        return NULL;
    }
}

void actualizarPalabra(int ID, Palabra datosActualizados){
    sqlite3_stmt *stmt;

    char sql[] = "UPDATE Tipo_Morse SET PAL_ESP = ?, PAL_MOR_INT = ?, PAL_MOR_AM = ?, where ID_Palabra = ?";
    
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (result != SQLITE_OK) {
        printf("Error preparando el statement (UPDATE)\n");
        printf("%s\n", sqlite3_errmsg(db));
        return;
    }

    result = sqlite3_bind_text(stmt, 1, datosActualizados.Pal_Esp, strlen(datosActualizados.Pal_Esp), SQLITE_STATIC);
    if (result != SQLITE_OK) {
        printf("Error vinculando Pal_Esp\n");
        printf("%s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return;
    }

    result = sqlite3_bind_text(stmt, 2, datosActualizados.Pal_Mor_Int, strlen(datosActualizados.Pal_Mor_Int), SQLITE_STATIC);
    if (result != SQLITE_OK) {
        printf("Error vinculando Pal_Mor_Int\n");
        printf("%s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return;
    }

    result = sqlite3_bind_text(stmt, 3, datosActualizados.Pal_Mor_Am, strlen(datosActualizados.Pal_Mor_Am), SQLITE_STATIC);
    if (result != SQLITE_OK) {
        printf("Error vinculando Pal_Mor_Am\n");
        printf("%s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return;
    }

    result = sqlite3_bind_int(stmt, 4, ID);
    if (result != SQLITE_OK) {
        printf("Error vinculando ID_Palabra\n");
        printf("%s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return;
    }

    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error actualizando las Palabra\n");
        printf("%s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return;
    }

    result = sqlite3_finalize(stmt);
    if (result != SQLITE_OK) {
        printf("Error al finalizar el statement (UPDATE)\n");
        printf("%s\n", sqlite3_errmsg(db));
        return;
    }
    printf("Palabra actualizado correctamente (UPDATE)\n");
}

void eliminarPalabra(int ID){
    sqlite3_stmt *stmt;

	char sql[] = "delete from Palabra where ID_Palabra = ?";

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparando el statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("Peticion SQL preparada (DELETE)\n");

    result = sqlite3_bind_int(stmt, 1, ID);
    if (result != SQLITE_OK) {
        printf("Error vinculando parametro (ID)\n");
        printf("%s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return result;
    }

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error eliminando datos\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error al finalizar el statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("Statement preparado finalizado (DELETE)\n");

	return SQLITE_OK;
}

// Funciones CRUD para la estructura TIPO_MORSE
void crearTipoMorse(Tipo_Morse nuevoTipoMorse){
    sqlite3_stmt *stmt;

    char sql[] = "insert into Tipo_Morse (NOMBRE_TIPO) values (?)";

    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
   
	if (result != SQLITE_OK) {
		printf("Error en el statement (INSERTAR)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    printf("Peticion SQL preparada (INSERTAR)\n");

    //Preparamos cada valor de nuevoTipoMorse en la BD
    //NOMBRE_TIPO
	result = sqlite3_bind_text(stmt, 1, nuevoTipoMorse.Nombre_Tipo, strlen(nuevoTipoMorse.Nombre_Tipo), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error insertando parametros\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    //Insertamos todos los valores preparados
    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error insertando los valores en la tabla Tipo_Morse\n");
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

Tipo_Morse* leerTipoMorse(int ID){
    sqlite3_stmt *stmt;
    Tipo_Morse *tipo;
    tipo = (Tipo_Morse*)(sizeof(Tipo_Morse));
    char *nombre;
    int id;
    
    char sql[] = "select ID_Morse, Nombre_Tipo from Tipo_Morse where ID_Morse = ?";
    
    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
    
    if (result != SQLITE_OK) {
		printf("Error en el statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
		}

    printf("Peticion SQL preparada (SELECT)\n");

    
	result = sqlite3_step(stmt) ;
	if (result == SQLITE_ROW) {
		id = sqlite3_column_int(stmt, 0);
		strcpy(nombre, (char *) sqlite3_column_text(stmt, 1));
	}
    tipo->ID_Morse = id;
    tipo->Nombre_Tipo = nombre;
    result = sqlite3_finalize(stmt);

	if (result != SQLITE_OK) {
		printf("Error finalizando el statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("Statement finalizado (SELECT)\n");

    return tipo;
}

// Funciones CRUD para la estructura ESTADISTICAS
void crearEstadisticas(Estadisticas nuevasEstadisticas){
    sqlite3_stmt *stmt;
    
    char sql[] = "insert into Estadisticas (Aciertos, Fallos) values (?, ?)";
	
    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error en el statement (INSERTAR)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    //Si no hay error se ha preparado correctamente la solicitud
    printf("Peticion SQL preparada (INSERTAR)\n");

    //Preparamos cada valor de nuevasEstadisticas en la BD
    //Aciertos
	result = sqlite3_bind_int(stmt, 1, nuevasEstadisticas.Aciertos);
	if (result != SQLITE_OK) {
		printf("Error insertando parametros\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    //Fallos
    result = sqlite3_bind_int(stmt, 2, nuevasEstadisticas.fallos);
	if (result != SQLITE_OK) {
		printf("Error insertando parametros\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    //Insertamos todos los valores preparados
    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error insertando los valores en la tabla Estadisticas\n");
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
Estadisticas* leerEstadisticas(int ID) {
	sqlite3_stmt *stmt;
    //ID_Estadistica INTEGER PRIMARY KEY AUTOINCREMENT, Aciertos INTEGER, Fallos INTEGER
    char sql[] = "select ID_Estadistica, Aciertos, Fallos where ID_Partida = ?";
    Estadisticas *estadistica = malloc(sizeof(Estadisticas));

    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
    
    if (result != SQLITE_OK) {
		printf("Error en el statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
		}

    printf("Peticion SQL preparada (SELECT)\n"); 
	//sqlite3_bind_text(stmt, 1, ID, -1, SQLITE_TRANSIENT);  
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        if (!estadistica) {
            printf("No se pudo asignar memoria para el usuario\n");
            sqlite3_finalize(stmt);
            return NULL;
        }
        estadistica->ID_Estadistica = sqlite3_column_int(stmt, 0);
        estadistica->Aciertos = sqlite3_column_int(stmt, 1);
        estadistica->fallos = sqlite3_column_int(stmt, 2);
	}

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizando el statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	printf("Statement preparado finalizado (SELECT)\n");
    return estadistica;
}

void actualizarEstadisticas(int ID, Estadisticas datosActualizados){
    sqlite3_stmt *stmt;

    char sql[] = "UPDATE Estadisticas SET Aciertos = ?, Fallos = ?, where ID_Estadistica = ?";
    
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (result != SQLITE_OK) {
        printf("Error preparando el statement (UPDATE)\n");
        printf("%s\n", sqlite3_errmsg(db));
        return;
    }

    result = sqlite3_bind_int(stmt, 1, datosActualizados.Aciertos);
    if (result != SQLITE_OK) {
        printf("Error vinculando Aciertos\n");
        printf("%s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return;
    }

    result = sqlite3_bind_int(stmt, 2, datosActualizados.fallos);
    if (result != SQLITE_OK) {
        printf("Error vinculando Fallos\n");
        printf("%s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return;
    }

    result = sqlite3_bind_int(stmt, 3, ID);
    if (result != SQLITE_OK) {
        printf("Error vinculando ID_Estadistica\n");
        printf("%s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return;
    }

    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error actualizando las estadisticas\n");
        printf("%s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return;
    }

    result = sqlite3_finalize(stmt);
    if (result != SQLITE_OK) {
        printf("Error al finalizar el statement (UPDATE)\n");
        printf("%s\n", sqlite3_errmsg(db));
        return;
    }
    printf("Estadisticas actualizado correctamente (UPDATE)\n");
    
}
void eliminarEstadisticas(int ID){
    sqlite3_stmt *stmt;

	char sql[] = "delete from Estadisticas where ID_Estadistica = ?";

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparando el statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("Peticion SQL preparada (DELETE)\n");

    result = sqlite3_bind_int(stmt, 1, ID);
    if (result != SQLITE_OK) {
        printf("Error vinculando parametro (ID)\n");
        printf("%s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return result;
    }

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error eliminando datos\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error al finalizar el statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("Statement preparado finalizado (DELETE)\n");

	return SQLITE_OK;
}

char* sortear_n_palabra(int ID)
{
	sqlite3_stmt *stmt;

	char sql[] = "SELECT ID_Palabra FROM Partida WHERE ID_Usuario = ?";

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	sqlite3_bind_int(stmt, 1, ID);
	int palabras_usadas[100];
    int num_palabras = 0;

	while (sqlite3_step(stmt) == SQLITE_ROW && num_palabras < 100) {
        palabras_usadas[num_palabras] = sqlite3_column_int(stmt, 0);
		num_palabras++;
    }
    sqlite3_finalize(stmt);

    const char *sql2 = "SELECT ID_Palabra, Pal_Esp, Pal_Mor_Int, Pal_Mor_Am FROM Palabra WHERE ID_Palabra NOT IN (SELECT ID_Palabra FROM Partida WHERE ID_Usuario = ?)"; //no :)
    result = sqlite3_prepare_v2(db, sql2, -1, &stmt, NULL);
    if (result != SQLITE_OK) { 
        printf("Error en preparación SQL: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    sqlite3_bind_int(stmt, 1, ID);

    Palabra *nueva_palabra = NULL;

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        nueva_palabra = malloc(sizeof(Palabra));
        if (!nueva_palabra) {
            printf("Error de asignación de memoria\n");
            sqlite3_finalize(stmt);
            return NULL;
        }

        nueva_palabra->ID_Palabra = sqlite3_column_int(stmt, 0);
        nueva_palabra->Pal_Esp = strdup((char *)sqlite3_column_text(stmt, 1));
        nueva_palabra->Pal_Mor_Int = strdup((char *)sqlite3_column_text(stmt, 2));
        nueva_palabra->Pal_Mor_Am = strdup((char *)sqlite3_column_text(stmt, 3));
    }

    sqlite3_finalize(stmt);
    return nueva_palabra->Pal_Esp;
}

int cargar_datos()
{
    FILE *file = fopen("Traducciones/palabras_traducidas_sep.txt", "r");
    if (!file) {
        printf("No se ha podido abrir el archivo.\n");
        return 1;
    }

    char linea[1024];
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO Palabras (Pal_Esp, Pal_Mor_Int, Pal_Mor_Am) VALUES (?, ?, ?)";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("No se ha podido escribir el codigo SQL: %s\n", sqlite3_errmsg(db));
        fclose(file);
        return 1;
    }

    // Leer el archivo y omitir la primera línea (encabezados)
    fgets(linea, 1024, file);

    while (fgets(linea, 1024, file)) {
        char *pal_esp = strtok(linea, ",");
        char *pal_mor_int = strtok(NULL, ",");
        char *pal_mor_am = strtok(NULL, "\n");

        //sqlite3_bind_text(stmt, 1, pal_esp, -1, SQLITE_TRANSIENT);
        //sqlite3_bind_text(stmt, 2, pal_mor_int, -1, SQLITE_TRANSIENT);
        //sqlite3_bind_text(stmt, 3, pal_mor_am, -1, SQLITE_TRANSIENT);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            fprintf(stderr, "No se pudo insertar la data: %s\n", sqlite3_errmsg(db));
        }

        sqlite3_reset(stmt);
    }

    sqlite3_finalize(stmt);
    fclose(file);
    return 0;   
}