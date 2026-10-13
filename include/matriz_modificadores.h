#ifndef MATRIZ_MODIFICADORES_H
#define MATRIZ_MODIFICADORES_H

#include "matriz_modo_l.h"
#include "matriz_modo_t.h"

class MatrizModificadores {
    private:
        char modo;
        MatrizModoL* matrizModoL; // so utiliza esse ponteiro se o modo for igual a 'L'
        MatrizModoT* matrizModoT; // so utiliza esse ponteiro se o modo for igual a 'T'
        void transicionaLparaT();
        void transicionaTparaL();

    public:
        MatrizModificadores();
        void imprime() const;
        void setModo(char modo);
        void setValor(int idItem, int idAtributo, int valor);
        int getValor(int idItem, int idAtributo);
        ~MatrizModificadores();
};

#endif