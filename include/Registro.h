#ifndef REGISTRO_H
#define REGISTRO_H

#include <list>
#include <DatoCampo.h>
#include <Campo.h>
#include <string>

using namespace std;

class Registro
{
    public:
        Registro(int);
        Registro();
        virtual ~Registro();
        //atributos
        int numTablaPadre;
        int regSize;
        list<DatoCampo*>* datosCampos;
        //funciones
        void addDatoCampo(Campo*);
        void addRegistro();
        int getRegSize();
        char* toChar();
        void fromChar(char*);
        void printRegistro();

    protected:

    private:
};

#endif // REGISTRO_H
