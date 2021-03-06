#ifndef BLOQUETABLA_H
#define BLOQUETABLA_H

#include <Bloque.h>
#include <BloqueCampo.h>
#include <BloqueRegistro.h>
#include <Tabla.h>
#include <list>

#include <iostream>
using namespace std;

class BloqueTabla : public Bloque
{
    public:
        BloqueTabla();
        BloqueTabla(int);
        virtual ~BloqueTabla();
        //atributos
        list<Tabla*>* tablas;
        int cantidadTablas;
        //funciones heredadas
        void escribirEnDisco();
        void cargarDesdeDisco();
        char* bloqueToChar();
        void charToBloque(char*);
        void imprimirTablas();
        Tabla* buscarTabla(int);
        //funciones propias
        bool agregarTabla(char*, int, int, int, int, int);
        void asignarBloqueCampo(int, BloqueCampo*);
        void asignarBloqueRegistro(int, BloqueRegistro*);

    protected:

    private:
};

#endif // BLOQUETABLA_H
