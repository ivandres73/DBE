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
    this->abrirArchivo("r");

    int pos = numBloque * tamBloque;
    char* data = archivo->leer(pos, tamBloque);
    charToBloque(data);

    this->cerrarArchivo();
}

void BloqueTabla::escribirEnDisco()
{
    this->abrirArchivo("r+");

    char* data = new char[512];
    data = this->bloqueToChar();
    int pos = numBloque * tamBloque;
    archivo->escribir(data, pos, tamBloque);

    this->cerrarArchivo();
}

char* BloqueTabla::bloqueToChar()
{
    char* data = new char[512];
    int pos = 0;
    memcpy(&data[pos], &numBloque, 4);
    pos += 4;
    memcpy(&data[pos], &tamBloque, 4);
    pos += 4;
    memcpy(&data[pos], &siguiente, 4);
    pos += 4;
    memcpy(&data[pos], &cantidadTablas, 4);
    pos += 4;
    list<Tabla*>::iterator i;
    char* datoTabla = new char[44];
    for (i = tablas->begin(); i != tablas->end(); i++)
    {
        Tabla* tmp = *i;
        datoTabla = tmp->toChar();
        memcpy(&data[pos], &datoTabla[0], 44);
        pos += 44;
    }
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
        Tabla* tabla = new Tabla("vacio", 0, 0, 0, 0, 0, 0);
        tabla->charToTabla(&datos[pos]);
        tablas->push_back(tabla);
        pos += 44;
    }
}


bool BloqueTabla::agregarTabla(char* nombre, int id, int pbr, int ubr, int pr, int ud)
{
    Tabla* nuevo = new Tabla(nombre, id, pbr, ubr, pr, ud, numBloque);
    int tamanoDeEncabezado = sizeof(numBloque) + sizeof(siguiente) + sizeof(cantidadTablas) + sizeof(tamBloque);
    if (cantidadTablas < 9) //deberia de ser:cantidadTablas < (tamBloque - tamanoDeEncabezado) / 44
    {
        tablas->push_back(nuevo);
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

void BloqueTabla::asignarBloqueRegistro(int id, BloqueRegistro* bloque)
{
    list<Tabla*>::iterator i;
    for (i = tablas->begin(); i != tablas->end(); i++)
    {
        Tabla* tmp = *i;
        if (id == tmp->id)
        {
            tmp->primerDatos = bloque->numBloque;
            return;
        }
    }
    printf("no se encontro la tabla con ese id %c", '\n');
}

void BloqueTabla::imprimirTablas()
{
    list<Tabla*>::iterator i;
    Tabla* tmp;
    printf("%cSoy el bloque tabla # %i", '\t', numBloque);
    printf(" Mi cantidad de Tablas: %i", cantidadTablas);
    printf("%c", '\n');
    for (i = tablas->begin(); i != tablas->end(); i++)
    {
        tmp = *i;
        printf("Nombre: %s,", tmp->nombre);
        printf(" ID: %i,", tmp->id);
        printf(" primerBloqueCampo: %i,", tmp->primerBloqueCampos);
        printf(" ultimoBloqueCampo: %i,", tmp->ultimoBloqueCampos);
        printf(" BloquePadre: %i", tmp->numBloquePadre);
        printf(" primerDatos: %i,", tmp->primerDatos);
        printf(" actualDatos: %i", tmp->actualDatos);
        printf("%c", '\n');
    }
}

Tabla* BloqueTabla::buscarTabla(int tablaID)
{
    if (tablas->empty())
    {
        return 0;
    }
    else
    {
        list<Tabla*>::iterator i;
        Tabla* tmp;
        for (i = tablas->begin(); i != tablas->end(); i++)
        {
            tmp = *i;
            if (tmp->id == tablaID)
            {
                cout << "\n****************ENTONTRE LA TABLA****************\n";
                return tmp;
            }
        }
    }
    return 0;
}
