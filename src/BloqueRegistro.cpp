#include "BloqueRegistro.h"

BloqueRegistro::BloqueRegistro(int num) : Bloque(num)
{
    registros = new list<Registro*>;
    cantidadRegistros = 0;
}

BloqueRegistro::~BloqueRegistro()
{
    //dtor
}

void BloqueRegistro::cargarDesdeDisco()
{
    int pos = numBloque * tamBloque;
    char* data = archivo->leer(pos, tamBloque);
    charToBloque(data);
}

void BloqueRegistro::escribirEnDisco()
{
    char* data = new char[tamBloque];
    data = this->bloqueToChar();
    int pos = numBloque * tamBloque;
    archivo->escribir(data, pos, tamBloque);
}

char* BloqueRegistro::bloqueToChar()
{
    char* data = new char[tamBloque];
    int pos = 0;
    memcpy(&data[pos], &numBloque, 4);
    pos += 4;
    memcpy(&data[pos], &tamBloque, 4);
    pos += 4;
    memcpy(&data[pos], &siguiente, 4);
    pos += 4;
    memcpy(&data[pos], &cantidadRegistros, 4);
    pos += 4;
    list<Registro*>::iterator i;
    Registro* tmp;
    char* datoRegistro;
    int tamRegistro;
    for (i = registros->begin(); i != registros->end(); i++)
    {
        tmp = *i;
        tamRegistro = tmp->getRegSize();
        datoRegistro = new char[tamRegistro];
        datoRegistro = tmp->toChar();
        memcpy(&data[pos], &datoRegistro[0], tamRegistro);
        pos += tamRegistro;
    }
    return data;
}

void BloqueRegistro::charToBloque(char* datos)
{
    int pos = 0;
    memcpy(&numBloque, &datos[pos], 4);
    pos += 4;
    memcpy(&tamBloque, &datos[pos], 4);
    pos += 4;
    memcpy(&siguiente, &datos[pos], 4);
    pos += 4;
    memcpy(&cantidadRegistros, &datos[pos], 4);
    pos += 4;
    for (int i=0; i < cantidadRegistros; i++)
    {
        Registro* reg = new Registro();
        reg->fromChar(&datos[pos]);
        pos += reg->getRegSize();
        registros->push_back(reg);
    }
}

bool BloqueRegistro::agregarRegistro(Registro* reg, int longiRegistro)
{
    int tamanoDeEncabezado = sizeof(numBloque) + sizeof(siguiente) + sizeof(cantidadRegistros) + sizeof(tamBloque);
    if (cantidadRegistros < (tamBloque - tamanoDeEncabezado) / longiRegistro)
    {
        registros->push_back(reg);
        cantidadRegistros++;
        return true;
    }
    else
    {
        cout << "bloque de registros lleno...\n";
        return false;
    }
}


void BloqueRegistro::printAllRegistros()
{
    if (registros->empty())
    {
        return;
    }
    list<Registro*>::iterator i;
    Registro* tmp;
    for (i = registros->begin(); i != registros->end(); i++)
    {
        tmp = *i;
        tmp->printRegistro();
    }
}
