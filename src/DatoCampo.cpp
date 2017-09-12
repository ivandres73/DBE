#include "DatoCampo.h"

DatoCampo::DatoCampo(Campo* campo)
{
    defCampo = campo;
    valor = (defCampo->tipo) ? new char[20] : new char[4];
}

DatoCampo::DatoCampo()
{
    defCampo = 0;
}

DatoCampo::~DatoCampo()
{
    //dtor
}

int DatoCampo::getIntValue()
{
    int tmp;
    memcpy(&tmp, &valor[0], 4);
    return tmp;
}

char* DatoCampo::getCharValue()
{
    return valor;
}

void DatoCampo::setIntValue(int value)
{
    memcpy(valor, &value, 20);
}

void DatoCampo::setCharValue(char* value)
{
    memcpy(valor, value, 20);
}

void DatoCampo::printValue()
{
    if (defCampo->tipo)
    {
        cout << valor << ", ";
    }
    else
    {
        int tmp;
        memcpy(&tmp, valor, 4);
        cout << tmp << ", ";
    }
}

short DatoCampo::getSize()
{
    return defCampo->tamano;
}

char* DatoCampo::toChar()
{
    int longi = getSize();
    int pos = 0;
    char* datos = new char[longi + 27];
    char* campoChar = new char[27];
    campoChar = defCampo->toChar();
    memcpy(&datos[pos], &campoChar[0], 27);
    pos += 27;
    if (longi == 4)
        memcpy(&datos[pos], &valor[0], longi);
    else
        memcpy(&datos[pos], valor, longi);
    return datos;
}

void DatoCampo::fromChar(char* datos)
{
    int pos = 0;
    defCampo = new Campo();
    defCampo->charToCampo(&datos[pos]);
    pos += 27;
    int longiDato = defCampo->tamano;
    valor = new char[longiDato];
    if (longiDato == 4)
        memcpy(&valor[0], &datos[pos], 4);
    else
        memcpy(valor, &datos[pos], 20);
}
