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
#include <DatoCampo.h>
#include <Registro.h>
#include <BloqueRegistro.h>

using namespace std;

void pruebaEscribirTablas(ManejarBloque& mt)
{
    for (int i=0; i < 19; i++)
    {
        mt.addTabla2("Tabla_");
    }
}

void pruebaEscribirCampos(ManejarBloque& mt)
{
    int num = 19;

    mt.addCampo2(num, "Nombre", 1);
    mt.addCampo2(num, "Apellido", 1);
    mt.addCampo2(num, "Edad", 0);
    mt.addCampo2(num, "Direccion", 1);
}

int main()
{
    ManejarBloque mt = ManejarBloque();

    //mt.formatearArchivo2();
    //pruebaEscribirTablas(mt);
    //pruebaEscribirCampos(mt);

    mt.listarBloqueTablas2();

    BloqueTabla* blota = new BloqueTabla(3);
    blota->abrirArchivo("r");
    blota->cargarDesdeDisco();
    blota->cerrarArchivo();
    blota->imprimirTablas();

    Tabla* ivan = mt.getTabla2(19);
    ivan->printCampos();

    mt.addRegistroToTabla2(19);
    mt.printRegistrosFromTabla(19);

    return 0;
}
