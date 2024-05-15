#include <string>
#include "tablas.h"

using namespace std;
using namespace tablas;

class SqlUtils {
    public:
        SqlUtils();
        ~SqlUtils();
        // Funciones de conexión
        void conectarBaseDeDatos();
        void desconectarBaseDeDatos();

        // Funciones CRUD para la estructura Usuario
        int crearUsuario(Usuario nuevoUsuario);
        Usuario* leerUsuario(const char* apodo);

        // Funciones CRUD para la estructura Partida
        int crearPartida(Partida nuevaPartida);
        Partida* leerPartida(int id);
        void actualizarPartida(int id, Partida datosActualizados);

        // Funciones CRUD para la estructura Palabra
        void crearPalabra(Palabra nuevaPalabra);
        int leerPalabra(char* palabra);
        // void actualizarPalabra(int id, const Palabra& datosActualizados);
        // void eliminarPalabra(int id);

        // Funciones CRUD para la estructura Tipo_Morse
        void crearTipoMorse(Tipo_Morse nuevoTipoMorse);
        Tipo_Morse* leerTipoMorse(int id);

        // Funciones CRUD para la estructura Estadisticas
        int crearEstadisticas(Estadisticas nuevasEstadisticas);
        Estadisticas* leerEstadisticas(int id);
        void actualizarEstadisticas(int id, Estadisticas datosActualizados);
        void eliminarEstadisticas(int id);

        // Otras funciones
        string sortear_n_palabra(int idUsuario);
        int cargar_datos();
        void hacerYImprimirRankings();
        void obtenerTraducciones(char* nick, Usuario usu);
};