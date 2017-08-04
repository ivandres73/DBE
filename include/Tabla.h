#ifndef TABLA_H
#define TABLA_H

#include <string.h>

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
        int primerDatos;//
        int actualDatos;//nose para qe es esto
        int numBloquePadre;
        //funciones
        char* toChar();//crea un char de 44bytes
        void charToTabla(char*);

    protected:

    private:
};

#endif // TABLA_H
