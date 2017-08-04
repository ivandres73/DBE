#include "Bloque.h"

Bloque::Bloque()
{
    //ctor
}

Bloque::Bloque(int num)
{
    numBloque = num;
    tamBloque = 512;
    siguiente = -1;
    archivo = new DataFile("C:\\Users\\ivand\\Desktop\\archivo.ivan");
}

Bloque::~Bloque()
{
    //dtor
}

void Bloque::abrirArchivo(char* proposito)
{
    archivo->abrir(proposito);
}

void Bloque::cerrarArchivo()
{
    archivo->cerrar();
}
