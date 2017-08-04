#ifndef MANEJADORBLOQUES_H
#define MANEJADORBLOQUES_H


#include <BloqueTabla.h>
#include <BloqueMaestro.h>
#include <DataFile.h>
#include <list>

#include <iostream>
using namespace std;

class ManejarTabla
{
    public:
        ManejarTabla();
        virtual ~ManejarTabla();
        //atributos
        std::list<Bloque*> listaBloques;
        DataFile* archivo;
        BloqueMaestro* bm;
        //funciones
        void listarTablas();
        void addBloqueTabla();
        void addBloqueCampo();
        void addBloqueMaestro();
        void addTabla(char nombre[20], int pbr, int ubr, int pr, int ud);
        void guardar_en_secudario_bloques();
        void subir_bloques_a_primario();
        void formatearArchivo();
        void guardar_un_bloque_tabla();///
        BloqueTabla* getBloqueTablaFromDisco(int);
        BloqueMaestro* getBloqueMasterFromDisco();

    protected:

    private:

};

#endif // MANEJADORBLOQUES_H
