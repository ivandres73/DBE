#include "Campo.h"

Campo::Campo()
{
    //ctor
}

Campo::Campo(const char* nombre, bool tipo, int padre)
{
    memcpy(this->nombre, nombre, 20);
    this->tipo = tipo;
    tamano = (tipo) ? 20 : 4;
    numBloquePadre = padre;
}

Campo::~Campo()
{
    //dtor
}

char* Campo::toChar()
{
    char* datos = new char[27];
    int pos = 0;
    memcpy(&datos[pos], nombre, 20);
    pos += 20;
    memcpy(&datos[pos], &tipo, 1);
    pos += 1;
    memcpy(&datos[pos], &tamano, 2);
    pos += 2;
    memcpy(&datos[pos], &numBloquePadre, 4);
    pos += 4;
    return datos;
}

void Campo::charToCampo(char* datos)
{
    int pos = 0;
    memcpy(nombre, &datos[pos], 20);
    pos += 20;
    memcpy(&tipo, &datos[pos], 1);
    pos += 1;
    memcpy(&tamano, &datos[pos], 2);
    pos += 2;
    memcpy(&numBloquePadre, &datos[pos], 4);
    pos += 4;
}
