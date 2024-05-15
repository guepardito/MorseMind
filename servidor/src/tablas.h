#include <string>

using namespace std;

namespace tablas {
    class Usuario {
        private:
            int ID_Usuario;
            string Correo;
            string Nombre;
            string Apellido;
            string Apodo;
            string Contrasenya;
            int ID_Estadistica;

        public:
            Usuario(int idUsuario, string correo, string nombre, string apellido, string apodo, string contrasenya, int idEstadistica)
                : ID_Usuario(idUsuario), Correo(correo), Nombre(nombre), Apellido(apellido), Apodo(apodo), Contrasenya(contrasenya), ID_Estadistica(idEstadistica) {}

            int getID_Usuario() const { return ID_Usuario; }
            void setID_Usuario(int idUsuario) { ID_Usuario = idUsuario; }

            string getCorreo() const { return Correo; }
            void setCorreo(string correo) { Correo = correo; }

            string getNombre() const { return Nombre; }
            void setNombre(string nombre) { Nombre = nombre; }

            string getApellido() const { return Apellido; }
            void setApellido(string apellido) { Apellido = apellido; }

            string getApodo() const { return Apodo; }
            void setApodo(string apodo) { Apodo = apodo; }

            string getContrasenya() const { return Contrasenya; }
            void setContrasenya(string contrasenya) { Contrasenya = contrasenya; }

            int getID_Estadistica() const { return ID_Estadistica; }
            void setID_Estadistica(int idEstadistica) { ID_Estadistica = idEstadistica; }
        };

    class Partida {
        private:
            int ID_Partida;
            int Puntuacion;
            string Resultado;
            string Fecha;
            int Intentos;
            int ID_Usuario;
            int ID_Morse;
            int ID_Palabra;

        public:
            Partida(int idPartida, int puntuacion, string resultado, string fecha, int intentos, int idUsuario, int idMorse, int idPalabra)
                : ID_Partida(idPartida), Puntuacion(puntuacion), Resultado(resultado), Fecha(fecha), Intentos(intentos), ID_Usuario(idUsuario), ID_Morse(idMorse), ID_Palabra(idPalabra) {}

            int getID_Partida() const { return ID_Partida; }
            void setID_Partida(int idPartida) { ID_Partida = idPartida; }

            int getPuntuacion() const { return Puntuacion; }
            void setPuntuacion(int puntuacion) { Puntuacion = puntuacion; }

            string getResultado() const { return Resultado; }
            void setResultado(string resultado) { Resultado = resultado; }

            string getFecha() const { return Fecha; }
            void setFecha(string fecha) { Fecha = fecha; }

            int getIntentos() const { return Intentos; }
            void setIntentos(int intentos) { Intentos = intentos; }

            int getID_Usuario() const { return ID_Usuario; }
            void setID_Usuario(int idUsuario) { ID_Usuario = idUsuario; }

            int getID_Morse() const { return ID_Morse; }
            void setID_Morse(int idMorse) { ID_Morse = idMorse; }

            int getID_Palabra() const { return ID_Palabra; }
            void setID_Palabra(int idPalabra) { ID_Palabra = idPalabra; }
    };

    class Palabra {
        private:
            int ID_Palabra;
            string Pal_Esp;
            string Pal_Mor_Int;
            string Pal_Mor_Am;

        public:
            Palabra(int idPalabra, string palEsp, string palMorInt, string palMorAm)
                : ID_Palabra(idPalabra), Pal_Esp(palEsp), Pal_Mor_Int(palMorInt), Pal_Mor_Am(palMorAm) {}

            int getID_Palabra() const { return ID_Palabra; }
            void setID_Palabra(int idPalabra) { ID_Palabra = idPalabra; }

            string getPal_Esp() const { return Pal_Esp; }
            void setPal_Esp(string palEsp) { Pal_Esp = palEsp; }

            string getPal_Mor_Int() const { return Pal_Mor_Int; }
            void setPal_Mor_Int(string palMorInt) { Pal_Mor_Int = palMorInt; }

            string getPal_Mor_Am() const { return Pal_Mor_Am; }
            void setPal_Mor_Am(string palMorAm) { Pal_Mor_Am = palMorAm; }
    };

    class Tipo_Morse {
        private:
            int ID_Morse;
            string Nombre_Tipo;

        public:
            Tipo_Morse(int idMorse, string nombreTipo)
                : ID_Morse(idMorse), Nombre_Tipo(nombreTipo) {}

            int getID_Morse() const { return ID_Morse; }
            void setID_Morse(int idMorse) { ID_Morse = idMorse; }

            string getNombre_Tipo() const { return Nombre_Tipo; }
            void setNombre_Tipo(string nombreTipo) { Nombre_Tipo = nombreTipo; }
    };

    class Estadisticas {
        private:
            int ID_Estadistica;
            int Aciertos;
            int Fallos;

        public:
            Estadisticas(int idEstadistica, int aciertos, int fallos)
                : ID_Estadistica(idEstadistica), Aciertos(aciertos), Fallos(fallos) {}

            int getID_Estadistica() const { return ID_Estadistica; }
            void setID_Estadistica(int idEstadistica) { ID_Estadistica = idEstadistica; }

            int getAciertos() const { return Aciertos; }
            void setAciertos(int aciertos) { Aciertos = aciertos; }

            int getFallos() const { return Fallos; }
            void setFallos(int fallos) { Fallos = fallos; }
    };

    class Ranking {
        private:
            string Apodo;
            int Puntuacion;

        public:
            Ranking(string apodo, int puntuacion)
                : Apodo(apodo), Puntuacion(puntuacion) {}

            string getApodo() const { return Apodo; }
            void setApodo(string apodo) { Apodo = apodo; }

            int getPuntuacion() const { return Puntuacion; }
            void setPuntuacion(int puntuacion) { Puntuacion = puntuacion; }
    };

}