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
    mt.formatearArchivo();

    for (int i=0; i < 40; i++)
    {
        mt.addTabla("Tabla_", 0, 0, 0, 0);
        cout << "ultimo Bloque Tabla disponible: " << mt.bm->ultimoBloqueTablaDisponible << endl;
    }

    BloqueTabla* bt;
    Bloque* bloque;
    list<Bloque*>::reverse_iterator ri;
    ri = mt.listaBloques.rbegin();
    bloque = *ri;
    cout << "...num del bloque " << bloque->numBloque << endl;
    bt = (BloqueTabla*)bloque;
    cout << "...num del bloqueT " << bt->numBloque << endl;
    //mt.archivo->abrir("r+");
    //bt->escribirEnDisco();
    //bt->cerrarArchivo();

    mt.guardar_en_secudario_bloques();


//    BloqueMaestro* bm = new BloqueMaestro(0);
//    bm->abrirArchivo("r");
//    bm->cargarDesdeDisco();
//    bm->cerrarArchivo();
//
//    cout << bm->ultimoBloqueTablaDisponible << endl;

    return 0;
}
