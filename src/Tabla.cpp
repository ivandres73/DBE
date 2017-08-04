#include "Tabla.h"

Tabla::Tabla()
{
    //ctor
}

Tabla::Tabla(char n[20], int i, int p, int u, int pd, int ad, int nbp)
{
    //nombre = n;
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
    char datos[44];
    int pos = 0;
    memcpy(&datos[pos], &nombre, sizeof(nombre));
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
    memcpy(&nombre, &datos[pos], sizeof(nombre));
    pos += 20;
    memcpy(&id, &datos[pos], sizeof(int));
    pos += 4;
    memcpy(&primerBloqueCampos, &datos[pos], sizeof(int));
    pos += 4;
    memcpy(&ultimoBloqueCampos, &datos[pos], sizeof(int));
    pos += 4;
    memcpy(&primerDatos, &datos[pos], sizeof(int));
    pos += 4;
    memcpy(&actualDatos, &datos[pos], sizeof(int));
    pos += 4;
    memcpy(&numBloquePadre, &datos[pos], sizeof(int));
    pos += 4;
}
