#ifndef BLOQUEREGISTRO_H
#define BLOQUEREGISTRO_H

#include <Bloque.h>
#include <Registro.h>
#include <Campo.h>
#include <iostream>
#include <list>
#include <string>

using namespace std;

class BloqueRegistro : public Bloque
{
    public:
        BloqueRegistro(int);
        virtual ~BloqueRegistro();

        //atributos
        list<Registro*>* registros;
        int cantidadRegistros;
        //funciones heredadas
        void escribirEnDisco();
        void cargarDesdeDisco();
        char* bloqueToChar();
        void charToBloque(char*);
        //funciones propias
        bool agregarRegistro(Registro*,  int);
        void printAllRegistros();

    protected:

    private:
};

#endif // BLOQUEREGISTRO_H
