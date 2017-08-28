#ifndef CAMPO_H
#define CAMPO_H

#include <string.h>

class Campo
{
    public:
        Campo();
        Campo(const char*, bool, int);
        virtual ~Campo();
        //atributos
        char nombre[20];
        bool tipo;
        short tamano;
        int numBloquePadre;
        //funciones
        char* toChar();
        void charToCampo(char*);

    protected:

    private:
};

#endif // CAMPO_H
