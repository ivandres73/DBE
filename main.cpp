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
    ManejarTabla mt = ManejarTabla();
    //mt.formatearArchivo();

//    for (int i=0; i < 40; i++)
//    {
//        mt.addTabla("Tabla_", 0, 0, 0, 0);
//        cout << "ultimo Bloque Tabla disponible: " << mt.bm->ultimoBloqueTablaDisponible << endl;
//    }

    //mt.guardar_en_secudario_bloques();

    mt.subir_bloques_tablas();
    mt.listarBloqueTablas();

    return 0;
}
