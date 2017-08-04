#ifndef DATAFILE_H
#define DATAFILE_H

#include <stdio.h>

class DataFile
{
    public:
        DataFile();
        DataFile(char*);
        virtual ~DataFile();
        //atributos
        FILE *archivo;
        //funciones
        void abrir(char*);
        void cerrar();
        void escribir(char*, int, int);
        char* leer(int, int);
        int longitudArchivo();


    protected:

    private:
        char* path;
};

#endif // DATAFILE_H
