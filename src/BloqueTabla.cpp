#include "BloqueTabla.h"

BloqueTabla::BloqueTabla() : Bloque()
{
    cantidadTablas = 0;
}

BloqueTabla::BloqueTabla(int num) : Bloque(num)
{
    cantidadTablas = 0;
    tablas = new list<Tabla*>;
}

BloqueTabla::~BloqueTabla()
{
    //dtor
}

void BloqueTabla::cargarDesdeDisco()
{
    int pos = numBloque * tamBloque;
    char* data = archivo->leer(pos, tamBloque);
    charToBloque(data);
}

void BloqueTabla::escribirEnDisco()
{
    char* data = this->bloqueToChar();
    int pos = numBloque * tamBloque;
    cout << "el toChar pijudo\n";
    archivo->escribir(data, pos, tamBloque);
}

char* BloqueTabla::bloqueToChar()
{
    char* data = new char[tamBloque];
    int pos = 0;
    memcpy(&data[pos], &numBloque, 4);
    pos += 4;
    memcpy(&data[pos], &tamBloque, 4);
    pos += 4;
    memcpy(&data[pos], &siguiente, 4);
    pos += 4;
    memcpy(&data[pos], &cantidadTablas, 4);
    pos += 4;
//    list<Tabla*>::iterator i;
//    for (i = tablas->begin(); i != tablas->end(); i++)
//    {
//        Tabla* tmp = *i;
//        char* datoTabla = tmp->toChar();
//        memcpy(&data[pos], &datoTabla, 44);
//        pos += 44;
//    }
    return data;
}

void BloqueTabla::charToBloque(char* datos)
{
    int pos = 0;
    memcpy(&numBloque, &datos[pos], 4);
    pos += 4;
    memcpy(&tamBloque, &datos[pos], 4);
    pos += 4;
    memcpy(&siguiente, &datos[pos], 4);
    pos += 4;
    memcpy(&cantidadTablas, &datos[pos], 4);
    pos += 4;
    for (int i = 0; i < cantidadTablas; i++)
    {
        Tabla *tabla = new Tabla("vacio", 0, 0, 0, 0, 0, 0);
        tabla->charToTabla(&datos[pos]);
        tablas->push_back(tabla);
        pos += 44;
    }
}


bool BloqueTabla::agregarTabla(char nombre[20], int id, int pbr, int ubr, int pr, int ud)
{
    Tabla* nuevo = new Tabla(nombre, id, pbr, ubr, pr, ud, numBloque);
    cout << "espacio libre: " << (int)((tamBloque - 4 - 4) / 44)-cantidadTablas << endl;
    if (cantidadTablas < (tamBloque - sizeof(numBloque) - sizeof(siguiente)) / 44)
    {
        tablas->push_front(nuevo);
        cantidadTablas++;
        return true;
    }
    else
    {
        cout << "ya no hay espacio para mas tablas..." << endl;
        return false;
    }
}

void BloqueTabla::asignarBloqueCampo(int id, BloqueCampo* bloque)
{
    list<Tabla*>::iterator i;
    for (i = tablas->begin(); i != tablas->end(); i++)
    {
        Tabla* tmp = *i;
        if (id == tmp->id)
        {
            tmp->primerBloqueCampos = bloque->numBloque;
            return;
        }
    }
    printf("no se encontro la tabla con ese id %c", '\n');
}
