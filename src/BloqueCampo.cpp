#include "BloqueCampo.h"

BloqueCampo::BloqueCampo()
{
    //ctor
}

BloqueCampo::BloqueCampo(int num) : Bloque(num)
{
    campos = new list<Campo*>;
    cantidadDeCampos = 0;
}

BloqueCampo::~BloqueCampo()
{
    //dtor
}

void BloqueCampo::cargarDesdeDisco()
{
    this->abrirArchivo("r");

    int pos = numBloque * tamBloque;
    char* data = archivo->leer(pos, tamBloque);
    charToBloque(data);

    this->cerrarArchivo();
}

void BloqueCampo::escribirEnDisco()
{
    this->abrirArchivo("r+");

    char* data = new char[tamBloque];
    data = this->bloqueToChar();
    int pos = numBloque * tamBloque;
    archivo->escribir(data, pos, tamBloque);

    this->cerrarArchivo();
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
    memcpy(&data[pos], &cantidadDeCampos, 4);
    pos += 4;
    list<Campo*>::iterator i;
    Campo* tmp = new Campo();
    for (i = campos->begin(); i != campos->end(); i++)
    {
        tmp = *i;
        char* datoCampos = new char[27];
        datoCampos = tmp->toChar();
        memcpy(&data[pos], &datoCampos[0], 27);
        pos += 27;
    }
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
    memcpy(&cantidadDeCampos, &datos[pos], 4);
    pos += 4;
    for (int i=0; i < cantidadDeCampos; i++)
    {
        char* datoCampos = new char[27];
        memcpy(&datoCampos[0], &datos[pos], 27);
        Campo* nuevo = new Campo();
        nuevo->charToCampo(datoCampos);
        campos->push_back(nuevo);
        pos += 27;
    }
}

bool BloqueCampo::agregarCampo(char* nombre, bool tipo)
{
    Campo* nuevo = new Campo(nombre, tipo, numBloque);
    int camposDisponible = (tamBloque-4-4-4-4)/27;
    if (cantidadDeCampos < 9) // deberia de ser (cantidadDeCampos < camposDisponible)
    {
        campos->push_back(nuevo);
        cantidadDeCampos++;
        return true;
    }
    else
    {
        printf("No hay espacio para mas campos %c", '\n');
        return false;
    }
}

void BloqueCampo::printCampos()
{
    list<Campo*>::iterator i;
    for (i = campos->begin(); i != campos->end(); i++)
    {
        Campo* tmp = *i;
        printf("Nombre del Campo: %s", tmp->nombre);
        printf("%c", '\n');
        cout << "tipo del campo: " << tmp->tipo;
        printf("%c", '\n');
        cout << "tamano de un registro del campo: " << tmp->tamano;
        printf("%c", '\n');
        printf("num de mi Bloque papa: %i", tmp->numBloquePadre);
        printf("%c", '\n');
    }
}

Campo* BloqueCampo::getCampo(int index)
{
    if (index > campos->size())
    {
        return 0;
    }
    list<Campo*>::iterator i = campos->begin();
    advance(i, index);
    Campo* tmp = *i;
    return tmp;
}
