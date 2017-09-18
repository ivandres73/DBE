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

BloqueTabla* ManejarBloque::getBloqueTablaFromDisco(int indice)
{
    BloqueTabla* bloque = new BloqueTabla(indice);
    bloque->cargarDesdeDisco();
    return bloque;
}

BloqueMaestro* ManejarBloque::getBloqueMasterFromDisco()
{
    BloqueMaestro* bloque = new BloqueMaestro(0);
    bloque->cargarDesdeDisco();
    return bloque;
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
        tmp->cargarDesdeDisco();

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
        bt->cargarDesdeDisco();
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
        bttmp->cargarDesdeDisco();
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
        bc->cargarDesdeDisco();
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
        bc->escribirEnDisco();
        bandera = false;
    }
    if (bandera)
    {
        bc->escribirEnDisco();
    }
    else
    {
        bctmp->escribirEnDisco();

        BloqueTabla* bttmp = new BloqueTabla(table->numBloquePadre);
        bttmp->cargarDesdeDisco();
        Tabla* teibol = bttmp->buscarTabla(table->id);
        teibol->ultimoBloqueCampos = bctmp->numBloque;
        bttmp->escribirEnDisco();
    }

    if (flag)
    {
        BloqueTabla* bttmp = new BloqueTabla(table->numBloquePadre);
        bttmp->cargarDesdeDisco();
        bttmp->asignarBloqueCampo(table->id, bc);
        Tabla* teibol = bttmp->buscarTabla(table->id);
        teibol->ultimoBloqueCampos = bctmp->numBloque;
        bttmp->escribirEnDisco();
    }
    bm->escribirEnDisco();
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
        bt->escribirEnDisco();
        cout << "soy bloque#" << bt->numBloque << ", al guardar, mi sig es: " << bt->siguiente << endl;
    }

    if (bc != 0)
    {
        bc->escribirEnDisco();
    }

    if (bm != 0)
    {
        bm->escribirEnDisco();
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
        tmp->cargarDesdeDisco();

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
        br->cargarDesdeDisco();
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
        br->escribirEnDisco();
        bandera = false;
    }
    if (bandera)///si estaba lleno un bloque registro o no
    {
        br->escribirEnDisco();
    }
    else
    {
        brtmp->escribirEnDisco();

        BloqueTabla* bttmp = new BloqueTabla(table->numBloquePadre);
        bttmp->cargarDesdeDisco();
        Tabla* teibol = bttmp->buscarTabla(table->id);
        teibol->actualDatos = brtmp->numBloque;
        bttmp->escribirEnDisco();
    }
    if (flag)///si tuvo qe crear su primer bloqueRegistro
    {
        BloqueTabla* bttmp = new BloqueTabla(table->numBloquePadre);
        bttmp->cargarDesdeDisco();
        bttmp->asignarBloqueRegistro(table->id, br);
        Tabla* teibol = bttmp->buscarTabla(table->id);
        teibol->actualDatos = brtmp->numBloque;
        bttmp->escribirEnDisco();
    }
    bm->escribirEnDisco();
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

void ManejarBloque::printCamposFrom(int tablaId)
{
    Tabla* TheBooksOnTheTable = getTabla2(tablaId);
    if (TheBooksOnTheTable == 0)
    {
        cout << "no se encontro tabla\n";
        return;
    }
    else
    {
        TheBooksOnTheTable->printCampos();
    }
}
