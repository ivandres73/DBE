#include "Tabla.h"

Tabla::Tabla()
{
    //ctor
}

Tabla::Tabla(char* n, int i, int p, int u, int pd, int ad, int nbp)
{
    strcpy(nombre, n);
    id = i;
    primerBloqueCampos = p;
    ultimoBloqueCampos = u;
    primerDatos = pd;
    actualDatos = ad;
    numBloquePadre = nbp;
}

Tabla::~Tabla()
{
    //dtor
}

char* Tabla::toChar()//pesa 44 bytes sumando todos los atributos
{
    char* datos = new char[44];
    int pos = 0;
    memcpy(&datos[pos], nombre, 20);
    pos += 20;
    memcpy(&datos[pos], &id, sizeof(int));
    pos += 4;
    memcpy(&datos[pos], &primerBloqueCampos, sizeof(int));
    pos += 4;
    memcpy(&datos[pos], &ultimoBloqueCampos, sizeof(int));
    pos += 4;
    memcpy(&datos[pos], &primerDatos, sizeof(int));
    pos += 4;
    memcpy(&datos[pos], &actualDatos, sizeof(int));
    pos += 4;
    memcpy(&datos[pos], &numBloquePadre, sizeof(int));
    pos += 4;
    return datos;
}

void Tabla::charToTabla(char* datos)
{
    int pos = 0;
    memcpy(nombre, &datos[pos], 20);
    pos += 20;
    memcpy(&id, &datos[pos], 4);
    pos += 4;
    memcpy(&primerBloqueCampos, &datos[pos], 4);
    pos += 4;
    memcpy(&ultimoBloqueCampos, &datos[pos], 4);
    pos += 4;
    memcpy(&primerDatos, &datos[pos], 4);
    pos += 4;
    memcpy(&actualDatos, &datos[pos], 4);
    pos += 4;
    memcpy(&numBloquePadre, &datos[pos], 4);
    pos += 4;
}
