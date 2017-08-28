#include <iostream>
#include <stdio.h>

#include <Bloque.h>
#include <BloqueTabla.h>
#include <BloqueCampo.h>
#include <Campo.h>
#include <BloqueMaestro.h>
#include <ManejadorBloques.h>
#include <DataFile.h>
#include <list>

using namespace std;

void pruebaEscribir(ManejarBloque& mt)
{
    //mt.subir_bloques_tablas();//hay que subir los bloques tablas para no perder el siguiente
    mt.formatearArchivo();

    for (int i=0; i < 100; i++)
    {
        mt.addTabla("Tabla_", 0, 0);
        cout << "ultimo Bloque Tabla disponible: " << mt.bm->ultimoBloqueTablaDisponible << endl;
    }

    mt.guardar_en_secudario_bloques();

    for (int i=0; i < 9; i++)
    {
        mt.agregarCampos(i+1, "Nombre", 1);
        mt.agregarCampos(i+1, "Apellido", 1);
        mt.agregarCampos(i+1, "Edad", 0);
        mt.agregarCampos(i+1, "Direccion", 1);
    }

}

void pruebaLectura(ManejarBloque& mt)
{
    mt.subir_bloques_tablas();
    mt.listarBloqueTablas();

    BloqueTabla* bt = mt.getBloqueTablaFromDisco(1);
    bt->imprimirTablas();

}

void ensenarBloques(int num)
{
    BloqueCampo* bc = new BloqueCampo(num);
    bc->abrirArchivo("r");
    bc->cargarDesdeDisco();
    bc->cerrarArchivo();
    bc->printCampos();
}

void mostrarDatos(char* datos)
{
    for (int i=0; i < 512; i++)
    {
        cout << "[" << i << "] :" << datos[i] << endl;
    }
}

int main()
{
    ManejarBloque mt = ManejarBloque();
    //pruebaEscribir(mt);
    pruebaLectura(mt);
    ensenarBloques(3);

    return 0;
}
