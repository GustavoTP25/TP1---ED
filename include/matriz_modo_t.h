#ifndef MATRIZ_MODO_T_H
#define MATRIZ_MODO_T_H

#include "../include/fila_itens.h"
#include "../include/fila_atributos.h"

class Tripla {
    private:
        int idItem;
        int idAtributo;
        int valor;

    public:
        Tripla();
    friend class MatrizModoT;
    friend class MatrizModificadores;
};

class MatrizModoT {
    private:
        int tamanho;
        Tripla* vetor; // um ponteiro que aponta para o vetor de triplas

    public:
        MatrizModoT();
        int getValor(int idItem, int idAtributo);
        Tripla* getTripla(int idItem, int idAtributo);
        void setValor(int idItem, int idAtributo, int valor);
        void ordernar();
        ~MatrizModoT();
    friend class MatrizModificadores;

};

#endif