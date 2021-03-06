#include "Tabla.h"

Tabla::Tabla()
{
    //ctor
}

Tabla::Tabla(char* n, int i, int p, int u, int pd, int ad, int nbp)
{
    strncpy(nombre, n, 20);
    id = i;
    primerBloqueCampos = p;
    ultimoBloqueCampos = u;
    primerDatos = pd;
    actualDatos = ad;
    numBloquePadre = nbp;
    campos = new list<Campo*>;
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
    memcpy(&datos[pos], &id, 4);
    pos += 4;
    memcpy(&datos[pos], &primerBloqueCampos, 4);
    pos += 4;
    memcpy(&datos[pos], &ultimoBloqueCampos, 4);
    pos += 4;
    memcpy(&datos[pos], &primerDatos, 4);
    pos += 4;
    memcpy(&datos[pos], &actualDatos, 4);
    pos += 4;
    memcpy(&datos[pos], &numBloquePadre, 4);
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

void Tabla::printCampos()
{
    int tmp = primerBloqueCampos;
    if (tmp == -1)
    {
        return;
    }
    do
    {
        BloqueCampo* bc = new BloqueCampo(tmp);
        bc->abrirArchivo("r");
        bc->cargarDesdeDisco();
        bc->cerrarArchivo();
        bc->printCampos();
        tmp = bc->siguiente;
    } while (tmp != -1);
}

void Tabla::cargarCampos()
{
    int tmp = primerBloqueCampos;
    if (tmp == -1)
    {
        return;
    }
    do
    {
        BloqueCampo* bc = new BloqueCampo(tmp);
        bc->abrirArchivo("r");
        bc->cargarDesdeDisco();
        bc->cerrarArchivo();
        Campo* campoTMP;
        for (int i=0; i < bc->cantidadDeCampos; i++)
        {
            campoTMP = bc->getCampo(i);
            campos->push_back(campoTMP);
        }
        tmp = bc->siguiente;
    } while (tmp != -1);
}

void Tabla::printRegistros()
{
    int tmp = primerDatos;
    if (tmp == -1)
    {
        return;
    }
    BloqueRegistro* br;
    do
    {
        br = new BloqueRegistro(tmp);
        br->abrirArchivo("r");
        br->cargarDesdeDisco();
        br->cerrarArchivo();
        br->printAllRegistros();
        tmp = br->siguiente;
    } while (tmp != -1);
}
