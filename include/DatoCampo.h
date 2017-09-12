#ifndef DATOCAMPO_H
#define DATOCAMPO_H

#include <Campo.h>
#include <iostream>
#include <string>

using namespace std;

class DatoCampo
{
    public:
        DatoCampo(Campo*);
        DatoCampo();
        virtual ~DatoCampo();
        //atributos
        char* valor;
        Campo* defCampo;
        //funciones
        int getIntValue();
        char* getCharValue();
        void setIntValue(int);
        void setCharValue(char*);
        void printValue();
        short getSize();
        char* toChar();
        void fromChar(char*);

    protected:

    private:
};

#endif // DATOCAMPO_H
