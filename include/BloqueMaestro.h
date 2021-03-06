#ifndef BLOQUEMAESTRO_H
#define BLOQUEMAESTRO_H

#include <Bloque.h>

class BloqueMaestro : public Bloque
{
    public:
        BloqueMaestro(int);
        virtual ~BloqueMaestro();
        //atributos
        int ultimoBloqueTablaDisponible;
        int cantidadTablas;
        int ultimoBloqueCampo;
        //funciones
        void escribirEnDisco();
        void cargarDesdeDisco();
        char* bloqueToChar();
        void charToBloque(char*);
        void printEncabezado();

    protected:

    private:
};

#endif // BLOQUEMAESTRO_H
