#ifndef MANEJADORBLOQUES_H
#define MANEJADORBLOQUES_H


#include <BloqueTabla.h>
#include <Tabla.h>
#include <BloqueRegistro.h>
#include <Registro.h>
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
        DataFile* archivo;
        BloqueMaestro* bm;
        BloqueTabla* bt;
        BloqueCampo* bc;
        ///Intento de hacerlo mejor
        void addTabla2(char*);
        void formatearArchivo2();
        void guardarBloquesAlArchivo2();
        void addCampo2(int, char*, bool);
        Tabla* getTabla2(int);
        void listarBloqueTablas2();
        void printBloqueMaster();
        BloqueTabla* getBloqueTablaFromDisco(int);
        BloqueMaestro* getBloqueMasterFromDisco();
        int PosUltimoBloqueTabla();
        void addRegistroToTabla2(int);
        Registro* makeRegistro(Tabla*);
        void printRegistrosFromTabla(int);
        void printCamposFrom(int);

    protected:

    private:

};

#endif // MANEJADORBLOQUES_H
