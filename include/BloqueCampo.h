#ifndef BLOQUECAMPO_H
#define BLOQUECAMPO_H

#include <Bloque.h>
#include <Campo.h>
#include <list>
#include <iostream>

using namespace std;

class BloqueCampo : public Bloque
{
    public:
        BloqueCampo();
        BloqueCampo(int);
        //atributos
        list<Campo*>* campos;
        int cantidadDeCampos;
        //funciones
        virtual ~BloqueCampo();
        void escribirEnDisco();
        void cargarDesdeDisco();
        char* bloqueToChar();
        void charToBloque(char*);
        //funciones propias
        bool agregarCampo(char*, bool);
        void asignarBloqueRegistros(int/*, BloqueRegistro*/);
        void printCampos();

    protected:

    private:
};

#endif // BLOQUECAMPO_H
