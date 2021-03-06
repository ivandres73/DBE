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
    this->abrirArchivo("r+");

    char* data = this->bloqueToChar();
    int pos = numBloque * tamBloque;
    archivo->escribir(data, pos, tamBloque);

    this->cerrarArchivo();
}

void BloqueMaestro::cargarDesdeDisco()
{
    this->abrirArchivo("r");

    int pos = numBloque * tamBloque;
    char* data = archivo->leer(pos, tamBloque);
    charToBloque(data);

    this->cerrarArchivo();
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

void BloqueMaestro::printEncabezado()
{
    printf("Ultimo Bloque Tablas Disponible: %i %c", ultimoBloqueTablaDisponible, '\n');
    printf("Cantidad de Tablas: %i %c", cantidadTablas, '\n');
    printf("Ultimo Bloque de Campos: %i %c", ultimoBloqueCampo, '\n');
}
