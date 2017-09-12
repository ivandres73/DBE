#ifndef TABLA_H
#define TABLA_H

#include <string.h>
#include <BloqueCampo.h>
#include <BloqueRegistro.h>
#include <Registro.h>
#include <Campo.h>
#include <list>

using namespace std;

class Tabla
{
    public:
        Tabla();
        Tabla(char [20], int, int, int, int, int, int);
        virtual ~Tabla();
        //atributos
        char nombre[20];
        int id;
        int primerBloqueCampos;
        int ultimoBloqueCampos;
        int primerDatos;
        int actualDatos;
        int numBloquePadre;
        list<Campo*>* campos;
        //funciones
        char* toChar();//crea un char de 44bytes
        void charToTabla(char*);
        void printCampos();
        void cargarCampos();
        void printRegistros();

    protected:

    private:
};

#endif // TABLA_H
