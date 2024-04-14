#include "sqlUtils.h"
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
        printf("No se encontro ningun usuario con el Apodo especificado.\n");
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


// Funciones CRUD para la estructura PARTIDA
int crearPartida(Partida nuevaPartida) {
    printf("EL ID DE LA PARTIDA ES: %i\n", nuevaPartida.ID_Partida);
    sqlite3_stmt *stmt;
    
    char sql[] = "insert into Partida (Puntuacion, Resultado, Fecha, Intentos, ID_Usuario, ID_Morse, ID_Palabra) values (?, ?, ?, ?, ?, ?, ?)";
	
    //Prepara la sentencia SQL
    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
    
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
    result = sqlite3_bind_text(stmt, 2, nuevaPartida.Resultado, strlen(nuevaPartida.Resultado) + 1, SQLITE_STATIC);
    printf("B\n");
    if (result != SQLITE_OK) {
        printf("Error insertando Resultado\n");
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
    
    int last_id = sqlite3_last_insert_rowid(db);

    result = sqlite3_finalize(stmt);
    if (result != SQLITE_OK) {
        printf("Error finalizando la declaracion (INSERTAR)\n");
        printf("%s\n", sqlite3_errmsg(db));
        return;
    }

	printf("Declaracion finalizada correctamente (INSERTAR)\n");

    printf("ID: %i\n", last_id);
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


void actualizarPartida(int ID, Partida datosActualizados)
{
    sqlite3_stmt *stmt;
    char sql[] = "UPDATE Partida SET Puntuacion = ?, Resultado = ?, Fecha = ?, Intentos = ?, ID_Usuario = ?, ID_Morse = ?, ID_Palabra = ? WHERE ID_Partida = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error preparando el statement (UPDATE): %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_int(stmt, 1, datosActualizados.Puntuacion);
    sqlite3_bind_text(stmt, 2, datosActualizados.Resultado, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, datosActualizados.Fecha, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 4, datosActualizados.Intentos);
    sqlite3_bind_int(stmt, 5, datosActualizados.ID_Usuario);
    sqlite3_bind_int(stmt, 6, datosActualizados.ID_Morse);
    sqlite3_bind_int(stmt, 7, datosActualizados.ID_Palabra);
    sqlite3_bind_int(stmt, 8, ID);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        printf("Error actualizando partida: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Partida actualizada correctamente (UPDATE)\n");
        printf("FECHA: %s\n", datosActualizados.Fecha);
        printf("ID_MORSE: %i\n", datosActualizados.ID_Morse);
        printf("ID_PALABRA: %i\n", datosActualizados.ID_Palabra);
        printf("ID_PARTIDA: %i\n", datosActualizados.ID_Partida);
        printf("ID_USUARIO: %i\n", datosActualizados.ID_Usuario);
        printf("INTENTOS: %i\n", datosActualizados.Intentos);
        printf("PUNTUACION: %i\n", datosActualizados.Puntuacion);
        printf("RESULTADO: %s\n", datosActualizados.Resultado);
        
    }

    sqlite3_finalize(stmt);
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

    if (result != SQLITE_OK) {
		printf("Error finalizando el statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("Statement finalizado (SELECT)\n");

    return id_pal;
    }
}

void actualizarPalabra(int ID, Palabra datosActualizados){
    sqlite3_stmt *stmt;

    char sql[] = "UPDATE Tipo_Morse SET PAL_ESP = ?, PAL_MOR_INT = ?, PAL_MOR_AM = ? where ID_Palabra = ?";
    
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

    char sql[] = "insert into Tipo_Morse (ID_MORSE, NOMBRE_TIPO) values (?, ?)";

    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
   
	if (result != SQLITE_OK) {
		printf("Error en el statement (INSERTAR)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    printf("Peticion SQL preparada (INSERTAR)\n");

    //Preparamos cada valor de nuevoTipoMorse en la BD
    result = sqlite3_bind_int(stmt, 1, nuevoTipoMorse.ID_Morse);
	result = sqlite3_bind_text(stmt, 2, nuevoTipoMorse.Nombre_Tipo, strlen(nuevoTipoMorse.Nombre_Tipo), SQLITE_STATIC);
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
int crearEstadisticas(Estadisticas nuevasEstadisticas){
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

    //Obtenemos el ID que se genera automaticamente
    int id = (int)sqlite3_last_insert_rowid(db);
    
    result = sqlite3_finalize(stmt);
    if (result != SQLITE_OK) {
        printf("Error finalizando la declaracion (INSERTAR)\n");
        printf("%s\n", sqlite3_errmsg(db));
        return;
    }
    printf("EL ID DE ESTADISTICA ES: %i\n", id);

	printf("Declaracion finalizada correctamente (INSERTAR)\n");

	return id;

}
Estadisticas* leerEstadisticas(int ID) {
	sqlite3_stmt *stmt;
    //ID_Estadistica INTEGER PRIMARY KEY AUTOINCREMENT, Aciertos INTEGER, Fallos INTEGER
    char sql[] = "select ID_Estadistica, Aciertos, Fallos from Estadisticas where ID_Estadistica = ?";

    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
    
    if (result != SQLITE_OK) {
		printf("Error en el statement leerEstadisticas (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return NULL;
		}

    printf("Peticion SQL preparada (SELECT)\n");
    int intID = (int)ID;
	sqlite3_bind_int(stmt, 1, intID);
    printf("Imprime esto\n");
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        Estadisticas *estadistica = malloc(sizeof(Estadisticas));
        if (estadistica == NULL) {
            printf("No se pudo asignar memoria para estadistica\n");
            sqlite3_finalize(stmt);
            return NULL;
        }

        estadistica->ID_Estadistica = sqlite3_column_int(stmt, 0);
        estadistica->Aciertos = sqlite3_column_int(stmt, 1);
        estadistica->fallos = sqlite3_column_int(stmt, 2);

        sqlite3_finalize(stmt);
        printf("Peticion SQL finalizada correctamente (SELECT)\n");
        return estadistica;
    } else {
        printf("No hay ID %d\n", ID);
        sqlite3_finalize(stmt);
        return NULL;
    }

}

void actualizarEstadisticas(int ID, Estadisticas datosActualizados){
    sqlite3_stmt *stmt;

    char sql[] = "UPDATE Estadisticas SET Aciertos = ?, Fallos = ? WHERE ID_Estadistica = ?";
    
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

char* sortear_n_palabra(int ID) {
    sqlite3_stmt *stmt;
    char sql[] = "SELECT ID_Palabra FROM Palabra WHERE ID_Palabra NOT IN (SELECT ID_Palabra FROM Partida WHERE ID_Usuario = ?)";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error preparando el stmt: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    sqlite3_bind_int(stmt, 1, ID);

    int available_words[100];
    int num_available_words = 0;

    while (sqlite3_step(stmt) == SQLITE_ROW && num_available_words < 100) {
        available_words[num_available_words++] = sqlite3_column_int(stmt, 0);
    }

    if (num_available_words == 0) {
        printf("No available words found.\n");
        sqlite3_finalize(stmt);
        return NULL;
    }

    int index = rand() % num_available_words;
    int chosen_word_id = available_words[index];

    sqlite3_finalize(stmt); 
    const char *sql2 = "SELECT Pal_Esp FROM Palabra WHERE ID_Palabra = ?";
    if (sqlite3_prepare_v2(db, sql2, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error en el stmt: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    sqlite3_bind_int(stmt, 1, chosen_word_id);
    char* palabraSeleccionada = NULL;

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        palabraSeleccionada = strdup((char *)sqlite3_column_text(stmt, 0));
    } else {
        printf("Error.\n");
    }

    sqlite3_finalize(stmt);
    return palabraSeleccionada;
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
    const char *sql = "INSERT INTO Palabra (ID_Palabra, Pal_Esp, Pal_Mor_Int, Pal_Mor_Am) VALUES (?, ?, ?, ?)";

    //sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, NULL);

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("No se ha podido escribir el codigo SQL: %s\n", sqlite3_errmsg(db));
        fclose(file);
        return 1;
    }

    fgets(linea, 1024, file);

    int contadorPalabras = 1;
    while (fgets(linea, 1024, file)) {
        char *pal_esp = strtok(linea, ",");
        char *pal_mor_int = strtok(NULL, ",");
        char *pal_mor_am = strtok(NULL, "\n");

        if (!pal_esp || !pal_mor_int || !pal_mor_am) {
            fprintf(stderr, "No se ha podido escribir esta linea\n");
            continue;
        }        

        sqlite3_bind_int(stmt, 1, contadorPalabras);
        sqlite3_bind_text(stmt, 2, pal_esp, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, pal_mor_int, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 4, pal_mor_am, -1, SQLITE_TRANSIENT);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            // fprintf(stderr, "No se pudo insertar la data: %s\n", sqlite3_errmsg(db));
        }

        sqlite3_reset(stmt);

        contadorPalabras++;
    }

    sqlite3_finalize(stmt);
    //sqlite3_exec(db, "COMMIT;", NULL, NULL, NULL);
    fclose(file);
    return 0;   
}