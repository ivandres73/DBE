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
        std::list<Bloque*> listaBloques;
        DataFile* archivo;
        BloqueMaestro* bm;
        BloqueTabla* bt;
        BloqueCampo* bc;
        //funciones
        void listarBloqueTablas();
        void addBloqueTabla();
        void addBloqueCampo();
        void addBloqueMaestro();
        void addTabla(char*, int, int);
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
        BloqueCampo* getBloqueCampoFromDisco(int);
        int PosUltimoBloqueTabla();
        void addRegistroToTabla2(int);
        Registro* makeRegistro(Tabla*);
        void printRegistrosFromTabla(int);
        ///
        void formatearArchivo();
        void printCamposFrom(int);
        Tabla* getTabla(int);

    protected:

    private:

};

#endif // MANEJADORBLOQUES_H
