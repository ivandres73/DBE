#ifndef MANEJADORBLOQUES_H
#define MANEJADORBLOQUES_H


#include <BloqueTabla.h>
#include <BloqueMaestro.h>
#include <DataFile.h>
#include <list>

#include <iostream>
using namespace std;

class ManejarBloque
{
    public:
        ManejarBloque();
        virtual ~ManejarBloque();
        //atributos
        std::list<Bloque*> listaBloques;
        DataFile* archivo;
        BloqueMaestro* bm;
        //funciones
        void listarBloqueTablas();
        void addBloqueTabla();
        void addBloqueCampo();
        void addBloqueMaestro();
        void addTabla(char nombre[20], int pbr, int ubr, int pr, int ud);
        void guardar_en_secudario_bloques();
        void subir_bloques_a_primario();
        void subir_bloques_tablas();
        void formatearArchivo();
        BloqueTabla* getBloqueTablaFromDisco(int);
        BloqueMaestro* getBloqueMasterFromDisco();

    protected:

    private:

};

#endif // MANEJADORBLOQUES_H
