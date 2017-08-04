#ifndef BLOQUECAMPO_H
#define BLOQUECAMPO_H

#include <Bloque.h>

class BloqueCampo : public Bloque
{
    public:
        BloqueCampo();
        BloqueCampo(int);
        virtual ~BloqueCampo();
        void escribirEnDisco();
        void cargarDesdeDisco();
        char* bloqueToChar();
        void charToBloque(char*);

    protected:

    private:
};

#endif // BLOQUECAMPO_H
