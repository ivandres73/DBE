#include "DataFile.h"

DataFile::DataFile()
{
    //ctor
}

DataFile::DataFile(char* path)
{
    DataFile::path = path;
}

DataFile::~DataFile()
{
    //dtor
}

void DataFile::abrir(char* proposito)
{
    archivo = fopen(path, proposito);
}

void DataFile::cerrar()
{
    fclose(archivo);
}

void DataFile::escribir(char* datos, int pos, int longitud)
{
    if(fseek(archivo, pos, SEEK_SET) == 0)
    {
        fwrite(datos, sizeof(char), longitud, archivo);
    }
}

char* DataFile::leer(int pos, int longitud)
{
    char* datos = new char[longitud];
    fseek(archivo, pos, SEEK_SET);
    fread(datos , sizeof(char), longitud, archivo);
    return datos;
}

int DataFile::longitudArchivo()
{
    //fseek(archivo, 0, SEEK_END);
    //return sizeof(0);
}
