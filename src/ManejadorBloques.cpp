#include "ManejadorBloques.h"

ManejarBloque::ManejarBloque()
{
    archivo = new DataFile("C:\\Users\\ivand\\Desktop\\archivo.ivan");
    archivo->abrir("a");
    archivo->cerrar();
    bt = 0;
    bc = 0;
    bm = 0;
}

ManejarBloque::~ManejarBloque()
{
    //dtor
}

void ManejarBloque::listarBloqueTablas()
{
    std::list<Bloque*>::iterator i;
    BloqueTabla* tmp;
    Bloque* block;
    int target = 1;
    printf("%cLos Bloques Tablas estan en las posiciones: %c", '\n', '\n');
    for (i = listaBloques.begin(); i != listaBloques.end(); i++)
    {
        block = *i;
        if (block->numBloque == target)
        {
            tmp = (BloqueTabla*)block;
            printf("%s", "Bloque Tabla: ");
            printf("%i", tmp->numBloque);
            printf("%c", '\n');
        }
        target = tmp->siguiente;
        if (target == -1)
        {
            return;
        }
    }
}

void ManejarBloque::addBloqueTabla()
{
    listaBloques.push_front(new BloqueTabla(bm->ultimoBloqueTablaDisponible++));
    bm->ultimoBloqueCampo++;
}

void ManejarBloque::addBloqueCampo()
{
    listaBloques.push_front(new BloqueCampo(bm->ultimoBloqueCampo++));
}

void ManejarBloque::addBloqueMaestro()
{
    bm = new BloqueMaestro(0);
    bm->abrirArchivo("r+");
    bm->escribirEnDisco();
    bm->cerrarArchivo();
}

BloqueTabla* ManejarBloque::getBloqueTablaFromDisco(int indice)
{
    BloqueTabla* bloque = new BloqueTabla(indice);
    bloque->abrirArchivo("r");
    bloque->cargarDesdeDisco();
    bloque->cerrarArchivo();
    return bloque;
}

Tabla* ManejarBloque::getTabla(int tablaID)
{
    list<Bloque*>::reverse_iterator i;
    Bloque* block;
    int target = 1;
    if (listaBloques.empty())
    {
        cout << "esta vacia\n";
        return 0;
    }
    Tabla* tmp = 0;
    for (i = listaBloques.rbegin(); i != listaBloques.rend(); i++)
    {
        block = *i;
        bt = (BloqueTabla*)block;
        if (bt->numBloque == target)
        {
            tmp = bt->buscarTabla(tablaID);
            target = bt->siguiente;
            return tmp;
        }
        if (target == -1)
        {
            return 0;
        }
    }
}

BloqueMaestro* ManejarBloque::getBloqueMasterFromDisco()
{
    BloqueMaestro* bloque = new BloqueMaestro(0);
    bloque->abrirArchivo("r");
    bloque->cargarDesdeDisco();
    bloque->cerrarArchivo();
    return bloque;
}

void ManejarBloque::formatearArchivo()
{
    archivo->abrir("w");
    archivo->cerrar();
    addBloqueMaestro();
    addBloqueTabla();
}

void ManejarBloque::addTabla(char* nombre, int primerDatos, int ultimoDatos)
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
        int indice = bm->ultimoBloqueTablaDisponible - 1;
        if (block->numBloque == indice)
        {
            bt = (BloqueTabla*)(block);
            cout << "soy bloque #" << bt->numBloque << endl;
            cout << "ultimo bloqueTablas disp segun master: " << bm->ultimoBloqueTablaDisponible << endl;
            cout << "mi num de tablas: " << bt->cantidadTablas << endl;
            break;
        }
    }

    if (bt->agregarTabla(nombre, bm->cantidadTablas, bm->ultimoBloqueCampo, bm->ultimoBloqueCampo, primerDatos, ultimoDatos))
    {
        cout << "agregue tabla..." << endl;
    }
    else
    {
        printf("---------------se creara un nuevo bloque %c", '\n');
        bm->ultimoBloqueTablaDisponible = bm->ultimoBloqueCampo;
        bt->siguiente = bm->ultimoBloqueTablaDisponible;
        cout << "sig sera bloque num: " << bt->siguiente;
        //listaBloques.front()->siguiente = -1;
        addBloqueTabla();
        bt = (BloqueTabla*)listaBloques.front();
        bt->agregarTabla(nombre, bm->cantidadTablas, bm->ultimoBloqueCampo, bm->ultimoBloqueCampo, primerDatos, ultimoDatos);
        //bt->tablas->front()->ultimoBloqueCampos = bm->ultimoBloqueCampo - 1;
    }
    addBloqueCampo();
    BloqueCampo* bc = (BloqueCampo*)listaBloques.front();
    cout << "Yo tengo " << bc->cantidadDeCampos << " campos\n";
    cout << "el sig del blo campo: " << bc->siguiente << endl;
    cout << "ultimo bloque campo disp es: " << bm->ultimoBloqueCampo << endl;
    bm->cantidadTablas++;
}

///INTENTO DE HACERLO MEJOR

int ManejarBloque::PosUltimoBloqueTabla()
{
    int target = 1;
    int anterior = target;
    BloqueTabla* tmp;
    while (target != -1)
    {
        tmp = getBloqueTablaFromDisco(target);
        tmp->abrirArchivo("r");
        tmp->cargarDesdeDisco();
        tmp->cerrarArchivo();

        anterior = target;
        target = tmp->siguiente;
    }
    return anterior;
}

void ManejarBloque::addTabla2(char* nombre)
{
    if (bt == 0)
    {
        bm = getBloqueMasterFromDisco();
        bt = new BloqueTabla(PosUltimoBloqueTabla());
        bt->abrirArchivo("r");
        bt->cargarDesdeDisco();
        bt->cerrarArchivo();
    }
    BloqueTabla* bttmp = 0;
    if (bt->agregarTabla(nombre, bm->cantidadTablas, -1, -1, -1, -1))
    {
        cout << "agregue tabla..." << endl;
    }
    else
    {
        cout << "creando nuevo bloque...\n";
        bm->ultimoBloqueTablaDisponible++;
        bm->ultimoBloqueCampo++;
        bttmp = new BloqueTabla(bm->ultimoBloqueTablaDisponible);
        bt->siguiente = bttmp->numBloque;
        cout << "siguiente es: " << bt->siguiente << endl;
        bttmp->agregarTabla(nombre, bm->cantidadTablas, -1, -1, -1, -1);
    }
    bm->cantidadTablas++;
    guardarBloquesAlArchivo2();
    if (bttmp != 0)
    {
        bt = bttmp;
        guardarBloquesAlArchivo2();
    }
}

Tabla* ManejarBloque::getTabla2(int tablaID)
{
    int target = 1;
    BloqueTabla* bttmp = new BloqueTabla(target);
    Tabla* tmp = 0;
    do
    {
        bttmp->abrirArchivo("r");
        bttmp->cargarDesdeDisco();
        bttmp->cerrarArchivo();
        tmp = bttmp->buscarTabla(tablaID);
        if (tmp != 0)
        {
            return tmp;
        }
        target = bttmp->siguiente;
        bttmp = new BloqueTabla(target);
    } while (target != -1);
    return 0;
}

void ManejarBloque::addCampo2(int tablaID, char* nombre, bool tipoDato)
{
    if (bm == 0)
    {
        bm = getBloqueMasterFromDisco();
    }
    Tabla* table = getTabla2(tablaID);
    bool flag = true;
    if (table->primerBloqueCampos == -1)
    {
        bm->ultimoBloqueCampo++;
        bm->ultimoBloqueTablaDisponible++;
        bc = new BloqueCampo(bm->ultimoBloqueCampo);
    }
    else
    {
        bc = new BloqueCampo(table->ultimoBloqueCampos);
        bc->abrirArchivo("r");
        bc->cargarDesdeDisco();
        bc->cerrarArchivo();
        flag = false;
    }
    BloqueCampo* bctmp = bc;
    bool bandera = true;
    if (bc->agregarCampo(nombre, tipoDato))
    {
        cout << "agregue campo..." << endl;
        cout << "Yo tengo " << bc->cantidadDeCampos << " campos\n";
        cout << "ultimo bloque campo disp es: " << bm->ultimoBloqueCampo << endl;
    }
    else
    {
        printf("---------------se creara un nuevo bloque de campos %c", '\n');
        bm->ultimoBloqueCampo++;
        bm->ultimoBloqueTablaDisponible++;
        bctmp = new BloqueCampo(bm->ultimoBloqueCampo);
        bctmp->agregarCampo(nombre, tipoDato);
        bc->siguiente = bm->ultimoBloqueCampo;
        bc->abrirArchivo("r+");
        bc->escribirEnDisco();
        bc->cerrarArchivo();
        bandera = false;
    }
    if (bandera)
    {
        bc->abrirArchivo("r+");
        bc->escribirEnDisco();
        bc->cerrarArchivo();
    }
    else
    {
        bctmp->abrirArchivo("r+");
        bctmp->escribirEnDisco();
        bctmp->cerrarArchivo();

        BloqueTabla* bttmp = new BloqueTabla(table->numBloquePadre);
        bttmp->abrirArchivo("r");
        bttmp->cargarDesdeDisco();
        bttmp->cerrarArchivo();
        Tabla* teibol = bttmp->buscarTabla(table->id);
        teibol->ultimoBloqueCampos = bctmp->numBloque;
        bttmp->abrirArchivo("r+");
        bttmp->escribirEnDisco();
        bttmp->cerrarArchivo();
    }

    if (flag)
    {
        BloqueTabla* bttmp = new BloqueTabla(table->numBloquePadre);
        bttmp->abrirArchivo("r");
        bttmp->cargarDesdeDisco();
        bttmp->cerrarArchivo();
        bttmp->asignarBloqueCampo(table->id, bc);
        Tabla* teibol = bttmp->buscarTabla(table->id);
        teibol->ultimoBloqueCampos = bctmp->numBloque;
        bttmp->abrirArchivo("r+");
        bttmp->escribirEnDisco();
        bttmp->cerrarArchivo();
    }
    bm->abrirArchivo("r+");
    bm->escribirEnDisco();
    bm->cerrarArchivo();
    bc = 0;
}

void ManejarBloque::formatearArchivo2()
{
    archivo->abrir("w");
    archivo->cerrar();
    bm = new BloqueMaestro(0);
    bt = new BloqueTabla(bm->ultimoBloqueTablaDisponible);
    guardarBloquesAlArchivo2();
}

void ManejarBloque::guardarBloquesAlArchivo2()
{
    if (bt != 0)
    {
        bt->abrirArchivo("r+");
        bt->escribirEnDisco();
        bt->cerrarArchivo();
        cout << "soy bloque#" << bt->numBloque << ", al guardar, mi sig es: " << bt->siguiente << endl;
    }

    if (bc != 0)
    {
        bc->abrirArchivo("r+");
        bc->escribirEnDisco();
        bc->cerrarArchivo();
    }

    if (bm != 0)
    {
        bm->abrirArchivo("r+");
        bm->escribirEnDisco();
        bm->cerrarArchivo();
    }
}

void ManejarBloque::listarBloqueTablas2()
{
    int target = 1;
    BloqueTabla* tmp;
    printf("%cLos Bloques Tablas estan en las posiciones: %c", '\n', '\n');
    do
    {
        tmp = new BloqueTabla(target);
        tmp->abrirArchivo("r");
        tmp->cargarDesdeDisco();
        tmp->cerrarArchivo();

        printf("%s", "Bloque Tabla: ");
        printf("%i", tmp->numBloque);
        printf("%c", '\n');
        target = tmp->siguiente;
    } while (target != -1);
}

void ManejarBloque::printBloqueMaster()
{
    if (bm == 0)
    {
        bm = getBloqueMasterFromDisco();
    }
    bm->printEncabezado();
}

void ManejarBloque::addRegistroToTabla2(int tablaID)
{
    Tabla* table = getTabla2(tablaID);
    if (table == 0)///si la tabla no existe
    {
        cout << "tabla no existe\n";
        return;
    }
    if (table->primerBloqueCampos == -1)///si la tabla no tiene campos
    {
        cout << "tabla no tiene campos\n";
        return;
    }
    if (bm == 0)
    {
        bm = getBloqueMasterFromDisco();
    }
    BloqueRegistro* br;
    bool flag = true;
    if (table->primerDatos == -1)///si la tabla no tenia registros
    {
        bm->ultimoBloqueCampo++;
        bm->ultimoBloqueTablaDisponible++;
        br = new BloqueRegistro(bm->ultimoBloqueCampo);///ultimoCampo es referencia porque no existe ultimoDatos
    }
    else
    {
        br = new BloqueRegistro(table->actualDatos);
        br->abrirArchivo("r");
        br->cargarDesdeDisco();
        br->cerrarArchivo();
        flag = false;
    }
    BloqueRegistro* brtmp = br;
    bool bandera = true;
    Registro* registry = makeRegistro(table);
    if (br->agregarRegistro(registry, registry->getRegSize()))
    {
        cout << "agregado registro exitosamente...\n";
    }
    else
    {
        cout << "se creara un nuevo bloque registro...\n";
        bm->ultimoBloqueCampo++;
        bm->ultimoBloqueTablaDisponible++;
        brtmp = new BloqueRegistro(bm->ultimoBloqueCampo);
        brtmp->agregarRegistro(registry, registry->getRegSize());
        br->siguiente = bm->ultimoBloqueCampo;
        br->abrirArchivo("r+");
        br->escribirEnDisco();
        br->cerrarArchivo();
        bandera = false;
    }
    if (bandera)///si estaba lleno un bloque registro o no
    {
        br->abrirArchivo("r+");
        br->escribirEnDisco();
        br->cerrarArchivo();
    }
    else
    {
        brtmp->abrirArchivo("r+");
        brtmp->escribirEnDisco();
        brtmp->cerrarArchivo();

        BloqueTabla* bttmp = new BloqueTabla(table->numBloquePadre);
        bttmp->abrirArchivo("r");
        bttmp->cargarDesdeDisco();
        bttmp->cerrarArchivo();
        Tabla* teibol = bttmp->buscarTabla(table->id);
        teibol->actualDatos = brtmp->numBloque;
        bttmp->abrirArchivo("r+");
        bttmp->escribirEnDisco();
        bttmp->cerrarArchivo();
    }
    if (flag)///si tuvo qe crear su primer bloqueRegistro
    {
        BloqueTabla* bttmp = new BloqueTabla(table->numBloquePadre);
        bttmp->abrirArchivo("r");
        bttmp->cargarDesdeDisco();
        bttmp->cerrarArchivo();
        bttmp->asignarBloqueRegistro(table->id, br);
        Tabla* teibol = bttmp->buscarTabla(table->id);
        teibol->actualDatos = brtmp->numBloque;
        bttmp->abrirArchivo("r+");
        bttmp->escribirEnDisco();
        bttmp->cerrarArchivo();
    }
    bm->abrirArchivo("r+");
    bm->escribirEnDisco();
    bm->cerrarArchivo();
}

void ManejarBloque::printRegistrosFromTabla(int id)
{
    Tabla* table = getTabla2(id);
    table->printRegistros();
}

Registro* ManejarBloque::makeRegistro(Tabla* t)
{
    Registro* reg = new Registro(t->id);
    Campo* tmp;
    BloqueCampo* bc;
    t->cargarCampos();
    list<Campo*>::iterator i;
    for (i = t->campos->begin(); i != t->campos->end(); i++)
    {
        tmp = *i;
        reg->addDatoCampo(tmp);
    }
    reg->addRegistro();
    return reg;
}

///FIN DEL INTENTO DE HACERLO MEJOR

BloqueCampo* ManejarBloque::getBloqueCampoFromDisco(int id)
{
    BloqueCampo* bloque = new BloqueCampo(id);
    bloque->abrirArchivo("r");
    bloque->cargarDesdeDisco();
    bloque->cerrarArchivo();
    return bloque;
}
