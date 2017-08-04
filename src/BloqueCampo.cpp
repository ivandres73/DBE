#include "BloqueCampo.h"

BloqueCampo::BloqueCampo()
{
    //ctor
}

BloqueCampo::BloqueCampo(int num) : Bloque(num)
{

}

BloqueCampo::~BloqueCampo()
{
    //dtor
}

void BloqueCampo::cargarDesdeDisco()
{
    int pos = numBloque * tamBloque;
    char* data = archivo->leer(pos, tamBloque);
    charToBloque(data);
}

void BloqueCampo::escribirEnDisco()
{
    char* data = this->bloqueToChar();
    int pos = numBloque * tamBloque;
    archivo->escribir(data, pos, tamBloque);
}

char* BloqueCampo::bloqueToChar()
{
    char* data = new char[tamBloque];
    int pos = 0;
    memcpy(&data[pos], &numBloque, 4);
    pos += 4;
    memcpy(&data[pos], &tamBloque, 4);
    pos += 4;
    memcpy(&data[pos], &siguiente, 4);
    pos += 4;
    return data;
}

void BloqueCampo::charToBloque(char* datos)
{
    int pos = 0;
    memcpy(&numBloque, &datos[pos], 4);
    pos += 4;
    memcpy(&tamBloque, &datos[pos], 4);
    pos += 4;
    memcpy(&siguiente, &datos[pos], 4);
    pos += 4;
}
