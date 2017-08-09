#include <iostream>
#include <stdio.h>

#include <Bloque.h>
#include <BloqueTabla.h>
#include <BloqueCampo.h>
#include <BloqueMaestro.h>
#include <ManejadorBloques.h>
#include <DataFile.h>
#include <list>

using namespace std;

int main()
{
    ManejarBloque mt = ManejarBloque();
    //mt.formatearArchivo();

//    for (int i=0; i < 1000; i++)
//    {
//        mt.addTabla("Tabla_", 0, 0, 0, 0);
//        cout << "ultimo Bloque Tabla disponible: " << mt.bm->ultimoBloqueTablaDisponible << endl;
//    }



    //mt.guardar_en_secudario_bloques();

    mt.subir_bloques_tablas();
    mt.listarBloqueTablas();

    BloqueTabla* bt = mt.getBloqueTablaFromDisco(1081);
    bt->imprimirTablas();


    return 0;
}
