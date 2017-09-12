#include "Registro.h"

Registro::Registro(int padre)
{
    numTablaPadre = padre;
    datosCampos = new list<DatoCampo*>;
    regSize = 0;
}

Registro::Registro()
{
    numTablaPadre = 0;
    datosCampos = new list<DatoCampo*>;
    regSize = 0;
}

Registro::~Registro()
{
    numTablaPadre = 0;
    datosCampos = new list<DatoCampo*>;
    regSize = 0;
}

void Registro::addDatoCampo(Campo* campo)
{
    DatoCampo* nuevo = new DatoCampo(campo);
    datosCampos->push_back(nuevo);
}

int Registro::getRegSize()
{
    int longi = 8;
    list<DatoCampo*>::iterator i;
    DatoCampo* aux;
    for (i = datosCampos->begin(); i != datosCampos->end(); i++)
    {
        aux = *i;
        longi += aux->getSize();
        longi += 27; ///bytes de la definicion del campo
    }
    return longi;
}

char* Registro::toChar()
{
    char* datos = new char[getRegSize()];
    int pos = 0;
    memcpy(&datos[pos], &numTablaPadre, 4);
    pos += 4;
    regSize = getRegSize();
    memcpy(&datos[pos], &regSize, 4);
    pos += 4;
    list<DatoCampo*>::iterator i;
    DatoCampo* tmp;
    int tamano;
    char* datosAux;
    for (i = datosCampos->begin(); i != datosCampos->end(); i++)
    {
        tmp = *i;
        tamano = tmp->getSize() + 27;
        datosAux = new char[tamano];
        datosAux = tmp->toChar();
        memcpy(&datos[pos], &datosAux[0], tamano);
        pos += tamano;
    }
    return datos;
}

void Registro::fromChar(char* datos)
{
    int pos = 0;
    memcpy(&numTablaPadre, &datos[pos], 4);
    pos += 4;
    memcpy(&regSize, &datos[pos], 4);
    pos += 4;
    while (pos < regSize)
    {
        DatoCampo* nuevo = new DatoCampo();
        nuevo->fromChar(&datos[pos]);
        datosCampos->push_back(nuevo);
        pos += nuevo->getSize() + 27;
    }
}

void Registro::printRegistro()
{
    if (datosCampos->empty())
    {
        return;
    }
    list<DatoCampo*>::iterator i;
    DatoCampo* tmp;
    for (i = datosCampos->begin(); i != datosCampos->end(); i++)
    {
        tmp = *i;
        tmp->printValue();
    }
    cout << endl;
}

void Registro::addRegistro()
{
    list<DatoCampo*>::iterator i;
    DatoCampo* tmp;
    for (i = datosCampos->begin(); i != datosCampos->end(); i++)
    {
        tmp = *i;
        if (tmp->defCampo->tipo)
        {
            cout << tmp->defCampo->nombre << ": ";
            char* texto = new char[20];
            cin >> texto;
            tmp->setCharValue(texto);
        }
        else
        {
            cout << tmp->defCampo->nombre << ": ";
            int numero;
            cin >> numero;
            tmp->setIntValue(numero);
        }
    }
}
