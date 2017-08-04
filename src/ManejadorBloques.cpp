#include "ManejadorBloques.h"

ManejarTabla::ManejarTabla()
{
    archivo = new DataFile("C:\\Users\\ivand\\Desktop\\archivo.ivan");
    archivo->abrir("a");
    archivo->cerrar();
}

ManejarTabla::~ManejarTabla()
{
    //dtor
}

void ManejarTabla::listarTablas()
{
    std::list<Bloque*>::iterator i;
    for (i = listaBloques.begin(); i != listaBloques.end(); i++)
    {
        BloqueTabla* tmp;
        tmp = (BloqueTabla*)*i;
        printf("%s", "Boque: ");
        printf("%i", tmp->numBloque);
        printf("%c", '\n');
    }
}

void ManejarTabla::addBloqueTabla()
{
    listaBloques.push_front(new BloqueTabla(bm->ultimoBloqueTablaDisponible++));
    bm->ultimoBloqueCampo++;
    bm->abrirArchivo("r+");
    bm->escribirEnDisco();
    bm->cerrarArchivo();
    //bloqueTablas.front()->siguiente = bm->ultimoBloqueTablaDisponible - 1;
}

void ManejarTabla::addBloqueCampo()
{
    listaBloques.push_front(new BloqueCampo(bm->ultimoBloqueCampo++));
    //bm->abrirArchivo("r+");
    //bm->escribirEnDisco();
    //bm->cerrarArchivo();
}

void ManejarTabla::addBloqueMaestro()
{
    bm = new BloqueMaestro(0);
    bm->abrirArchivo("r+");
    bm->escribirEnDisco();
    bm->cerrarArchivo();
}

void ManejarTabla::guardar_en_secudario_bloques()
{
    BloqueTabla* tmp;
    BloqueCampo* bc;
    Bloque* block;
    list<Bloque*>::reverse_iterator ri;
    int target = 1;
    for (ri = listaBloques.rbegin(); ri != listaBloques.rend(); ri++)
    {
        cout << "entro al for\n";
        block = *ri;
        if (block->numBloque == target)
        {
            cout << "reconocio que es Btabla\n";
            tmp = (BloqueTabla*)block;
            cout << "num del bTabla: " << tmp->numBloque << endl;
            tmp->abrirArchivo("r+");
            tmp->escribirEnDisco();
            tmp->cerrarArchivo();
            target = tmp->siguiente;
            cout << "tmp escribio..." << endl;

        }
        else
        {
            cout << "reconocio que es Bcampo\n";
            bc = (BloqueCampo*)block;
            cout << "el num de bloque es: " << bc->numBloque << endl;
            bc->abrirArchivo("r+");
            bc->escribirEnDisco();
            bc->cerrarArchivo();
            cout << "bc escribio...\n";
        }
    }
    archivo->cerrar();
}

void ManejarTabla::subir_bloques_a_primario()
{
    archivo->abrir("r");
    ///POR AQUI ME QUEDE
    BloqueTabla* tmp = new BloqueTabla();
    for (int i=0; i < bm->ultimoBloqueTablaDisponible; i++)
    {
        tmp = getBloqueTablaFromDisco(i);
        listaBloques.push_back(tmp);
    }
    archivo->cerrar();
}

BloqueTabla* ManejarTabla::getBloqueTablaFromDisco(int indice)
{
    archivo->abrir("r");
    BloqueTabla* bloque = new BloqueTabla(indice);
    bloque->numBloque = 73;
    char* datos = archivo->leer(indice*512, 512);//quitarla luego pero mejor no, porque funciona
    bloque->charToBloque(datos);//quitarla luego pero mejor no, porque funciona
    //bloque->cargarDesdeDisco();
    archivo->cerrar();
    return bloque;
}

BloqueMaestro* ManejarTabla::getBloqueMasterFromDisco()
{
    archivo->abrir("r");
    BloqueMaestro* bloque = new BloqueMaestro(0);
    bloque->numBloque = 73;
    char* datos = archivo->leer(0, 512);//quitarla luego pero mejor no, porque funciona
    bloque->charToBloque(datos);//quitarla luego pero mejor no, porque funciona
    //bloque->cargarDesdeDisco();
    archivo->cerrar();
    return bloque;
}

void ManejarTabla::formatearArchivo()
{
    archivo->abrir("w");
    archivo->cerrar();
    addBloqueMaestro();
    addBloqueTabla();
}

void ManejarTabla::addTabla(char nombre[20], int pbr, int ubr, int pr, int ud)
{
    if (listaBloques.empty())
    {
        addBloqueTabla();
    }
    list<Bloque*>::iterator i;
    BloqueTabla* bt;
    Bloque* block;
    for (i = listaBloques.begin(); i != listaBloques.end(); i++)
    {
        block = *i;
        int indice = bm->ultimoBloqueTablaDisponible;
        indice--;
        if (block->numBloque == indice)
        {
            bt = (BloqueTabla*)(block);
            cout << "soy bloque #" << bt->numBloque << endl;
            cout << "ultimo bloqueTablas disp segun master: " << bm->ultimoBloqueTablaDisponible << endl;
            cout << "mi num de tablas: " << bt->cantidadTablas << endl;
            break;
        }
    }

    if (bt->agregarTabla(nombre, bt->cantidadTablas, bm->ultimoBloqueCampo, ubr, pr, ud))
    {
        cout << "agregue tabla..." << endl;
        addBloqueCampo();
        BloqueCampo* bc = (BloqueCampo*)listaBloques.front();
        bc->siguiente = bm->ultimoBloqueCampo;
        cout << "el sig del blo campo: " << bc->siguiente << endl;
        cout << "ultimo bloque campo disp es: " << bm->ultimoBloqueCampo << endl;
    }
    else
    {
        printf("---------------se creara un nuevo bloque %c", '\n');
        //bt->siguiente = bm->ultimoBloqueTablaDisponible;
        bm->ultimoBloqueTablaDisponible = bm->ultimoBloqueCampo;
        bt->siguiente = bm->ultimoBloqueTablaDisponible;
        cout << "sig sera bloque num: " << bt->siguiente;
        listaBloques.front()->siguiente = -1;
        addBloqueTabla();
        bt = (BloqueTabla*)listaBloques.front();
        bt->agregarTabla(nombre, bt->cantidadTablas, bm->ultimoBloqueCampo, ubr, pr, ud);
        addBloqueCampo();
        //bt->tablas->front()->ultimoBloqueCampos = bm->ultimoBloqueCampo - 1;
    }
}

void ManejarTabla::guardar_un_bloque_tabla()
{

}
