#include "ManejadorBloques.h"

ManejarBloque::ManejarBloque()
{
    archivo = new DataFile("C:\\Users\\ivand\\Desktop\\archivo.ivan");
    archivo->abrir("a");
    archivo->cerrar();
    bt = 0;
    bc = 0;
}

ManejarBloque::~ManejarBloque()
{
    //dtor
}

void ManejarBloque::listarBloqueTablas()
{
    std::list<Bloque*>::iterator i;
    BloqueTabla* tmp;
    printf("%cLos Bloques Tablas estan en las posiciones: %c", '\n', '\n');
    for (i = listaBloques.begin(); i != listaBloques.end(); i++)
    {
        tmp = (BloqueTabla*)*i;
        printf("%s", "Bloque Tabla: ");
        printf("%i", tmp->numBloque);
        printf("%c", '\n');
    }
}

void ManejarBloque::addBloqueTabla()
{
    listaBloques.push_front(new BloqueTabla(bm->ultimoBloqueTablaDisponible++));
    bm->ultimoBloqueCampo++;
//    bm->abrirArchivo("r+");
//    bm->escribirEnDisco();
//    bm->cerrarArchivo();
    //bloqueTablas.front()->siguiente = bm->ultimoBloqueTablaDisponible - 1;
}

void ManejarBloque::addBloqueCampo()
{
    listaBloques.push_front(new BloqueCampo(bm->ultimoBloqueCampo++));
//    bm->abrirArchivo("r+");
//    bm->escribirEnDisco();
//    bm->cerrarArchivo();
}

void ManejarBloque::addBloqueMaestro()
{
    bm = new BloqueMaestro(0);
    bm->abrirArchivo("r+");
    bm->escribirEnDisco();
    bm->cerrarArchivo();
}

void ManejarBloque::guardar_en_secudario_bloques()
{
    BloqueTabla* tmp;
    BloqueCampo* bc;
    Bloque* block;
    list<Bloque*>::reverse_iterator ri;
    int target = 1;///SETEARLO A 1, ASI VUELVE A FUNCIONAR PARA BLOQUES TABLAS
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
            cout << "Cantidad de Campos: " << bc->cantidadDeCampos << endl;
            bc->abrirArchivo("r+");
            bc->escribirEnDisco();
            bc->cerrarArchivo();
            cout << "bc escribio...\n";
        }
    }
    cout << "ultimo segun master: " << bm->ultimoBloqueTablaDisponible;
    bm->abrirArchivo("r+");
    bm->escribirEnDisco();
    bm->cerrarArchivo();
}

void ManejarBloque::subir_bloques_a_primario()
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

BloqueTabla* ManejarBloque::getBloqueTablaFromDisco(int indice)
{
    archivo->abrir("r");
    BloqueTabla* bloque = new BloqueTabla(indice);
    char* datos = archivo->leer(indice*512, 512);//quitarla luego pero mejor no, porque funciona
    bloque->charToBloque(datos);//quitarla luego pero mejor no, porque funciona
    //bloque->cargarDesdeDisco();
    archivo->cerrar();
    return bloque;
}

BloqueMaestro* ManejarBloque::getBloqueMasterFromDisco()
{
    archivo->abrir("r");
    BloqueMaestro* bloque = new BloqueMaestro(0);
    char* datos = archivo->leer(0, 512);//quitarla luego pero mejor no, porque funciona
    bloque->charToBloque(datos);//quitarla luego pero mejor no, porque funciona
    //bloque->cargarDesdeDisco();
    archivo->cerrar();
    return bloque;
}

void ManejarBloque::formatearArchivo()
{
    archivo->abrir("w");
    archivo->cerrar();
    addBloqueMaestro();
    addBloqueTabla();
}

void ManejarBloque::addTabla(char* nombre, int pr, int ud)
{
    if (listaBloques.empty())
    {
        bm = getBloqueMasterFromDisco();
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

    if (bt->agregarTabla(nombre, bm->cantidadTablas, bm->ultimoBloqueCampo, bm->ultimoBloqueCampo, pr, ud))
    {
        cout << "agregue tabla..." << endl;
        addBloqueCampo();
        BloqueCampo* bc = (BloqueCampo*)listaBloques.front();
        bc->siguiente = bm->ultimoBloqueCampo;
        cout << "Yo tengo " << bc->cantidadDeCampos << " campos\n";
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
        bt->agregarTabla(nombre, bm->cantidadTablas, bm->ultimoBloqueCampo, bm->ultimoBloqueCampo, pr, ud);
        addBloqueCampo();
        //bt->tablas->front()->ultimoBloqueCampos = bm->ultimoBloqueCampo - 1;
    }
    bm->cantidadTablas++;
}

void ManejarBloque::subir_bloques_tablas()
{
    bm = getBloqueMasterFromDisco();
    cout << bm->ultimoBloqueTablaDisponible << endl;
    BloqueTabla* bt = new BloqueTabla(1);
    bt->abrirArchivo("r");
    bt->cargarDesdeDisco();
    bt->cerrarArchivo();
    listaBloques.push_back(bt);
    int next;
    cout << "num de este bt: " << bt->numBloque << endl;
    cout << "bt->siguiente: " << bt->siguiente << endl;
    do
    {
        next = bt->siguiente;
        bt = new BloqueTabla(next);
        bt->abrirArchivo("r");
        bt->cargarDesdeDisco();
        bt->cerrarArchivo();
        listaBloques.push_back(bt);
    } while (bt->siguiente != -1);
}

BloqueCampo* ManejarBloque::getBloqueCampoFromDisco(int id)
{
    archivo->abrir("r");
    BloqueCampo* bloque = new BloqueCampo(id);
    //bloque->archivo = new DataFile("C:\\Users\\ivand\\Desktop\\archivo.ivan");
    //bloque->abrirArchivo("r");
    //bloque->cargarDesdeDisco();
    //bloque->cerrarArchivo();
    char* datos = archivo->leer(id*512, 512);
    bloque->charToBloque(datos);
    archivo->cerrar();
    return bloque;
}

void ManejarBloque::agregarCampos(int tablaID, char* nombre, bool tipoDato)
{
    list<Bloque*>::reverse_iterator i;
    Bloque* block;
    int target = 1;
    if (listaBloques.empty())
    {
        cout << "esta vacia\n";
    }
    for (i = listaBloques.rbegin(); i != listaBloques.rend(); i++)
    {
        block = *i;
        bt = (BloqueTabla*)block;
        if (bt->numBloque == target)
        {
            list<Tabla*>::iterator ti;
            for (ti = bt->tablas->begin(); ti != bt->tablas->end(); ti++)
            {
                Tabla* table = *ti;
                if (table->id == tablaID)
                {
                    cout << "encontre la tabla...\n";
                    bc = new BloqueCampo(table->ultimoBloqueCampos);
                    bc->abrirArchivo("r");
                    bc->cargarDesdeDisco();
                    bc->cerrarArchivo();
                    cout << "num del bloque campo: " << bc->numBloque << endl;
                    break;
                }
            }
            target = bt->siguiente;
        }
        if (target == -1)
        {
            break;
        }
    }

    if (bc->agregarCampo(nombre, tipoDato))
    {
        cout << "agregue campo..." << endl;
        cout << "Yo tengo " << bc->cantidadDeCampos << " campos\n";
        cout << "ultimo bloque campo disp es: " << bm->ultimoBloqueCampo << endl;
    }
    else
    {
        printf("---------------se creara un nuevo bloque de campos %c", '\n');
        addBloqueCampo();
        bc = (BloqueCampo*)listaBloques.front();
        bc->agregarCampo(nombre, tipoDato);
    }
    bc->abrirArchivo("r+");
    bc->escribirEnDisco();
    bc->cerrarArchivo();
}
