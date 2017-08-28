#include "BloqueMaestro.h"

BloqueMaestro::BloqueMaestro(int num) : Bloque (num)
{
    ultimoBloqueTablaDisponible = 1;
    ultimoBloqueCampo = 1;
    cantidadTablas = 1;
    archivo = new DataFile("C:\\Users\\ivand\\Desktop\\archivo.ivan");
}

BloqueMaestro::~BloqueMaestro()
{
    //dtor
}

void BloqueMaestro::escribirEnDisco()
{
    char* data = this->bloqueToChar();
    int pos = numBloque * tamBloque;
    archivo->escribir(data, pos, tamBloque);
}

void BloqueMaestro::cargarDesdeDisco()
{
    int pos = numBloque * tamBloque;
    char* data = archivo->leer(pos, tamBloque);
    charToBloque(data);
}

char* BloqueMaestro::bloqueToChar()
{
    char* data = new char[tamBloque];
    int pos = 0;
    memcpy(&data[pos], &numBloque, 4);
    pos += 4;
    memcpy(&data[pos], &tamBloque, 4);
    pos += 4;
    memcpy(&data[pos], &siguiente, 4);
    pos += 4;
    memcpy(&data[pos], &ultimoBloqueTablaDisponible, 4);
    pos += 4;
    memcpy(&data[pos], &ultimoBloqueCampo, 4);
    pos += 4;
    memcpy(&data[pos], &cantidadTablas, 4);
    pos += 4;
    return data;
}

void BloqueMaestro::charToBloque(char* datos)
{
    int pos = 0;
    memcpy(&numBloque, &datos[pos], 4);
    pos += 4;
    memcpy(&tamBloque, &datos[pos], 4);
    pos += 4;
    memcpy(&siguiente, &datos[pos], 4);
    pos += 4;
    memcpy(&ultimoBloqueTablaDisponible, &datos[pos], 4);
    pos += 4;
    memcpy(&ultimoBloqueCampo, &datos[pos], 4);
    pos += 4;
    memcpy(&cantidadTablas, &datos[pos], 4);
    pos += 4;
}
