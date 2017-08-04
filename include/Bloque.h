#ifndef BLOQUE_H
#define BLOQUE_H


#include <DataFile.h>
#include <stdio.h>
#include <string.h>

class Bloque
{
    public:
        Bloque();
        Bloque(int);
        virtual ~Bloque();
        //atributos
        int numBloque;
        int tamBloque;
        DataFile* archivo;
        int siguiente;
        //funciones
        virtual void escribirEnDisco() = 0;
        virtual void cargarDesdeDisco() = 0;
        virtual char* bloqueToChar() = 0;
        virtual void charToBloque(char*) = 0;
        void abrirArchivo(char*);
        void cerrarArchivo();

    protected:

    private:

};

#endif // BLOQUE_H
