#ifndef MATRIZ_MODO_L_H
#define MATRIZ_MODO_L_H

#include "../include/fila_itens.h"
#include "../include/fila_atributos.h"

class CelulaMatriz {
    private:
        int lin, col, valor;
        CelulaMatriz* proxLinha;
        CelulaMatriz* proxColuna;

    public:
        CelulaMatriz(int lin, int col, int valor, CelulaMatriz* proxLinha, CelulaMatriz* proxColuna);
    friend class MatrizModoL;
    friend class MatrizModificadores;
};

class MatrizModoL {
    private:
        int numeroLinhas, numeroColunas, tamanho;
        // dois ponteiros que apontam para os vetores cabeças
        CelulaMatriz** CabecasLinha;
        CelulaMatriz** CabecasColuna;
        void Limpa();
        CelulaMatriz* LinhaAnterior(int i, int j) const;
        CelulaMatriz* ColunaAnterior(int i, int j) const;
        void ampliaLinhas(int novoNumero);
        void ampliaColunas(int novoNumero);

    public:
        MatrizModoL();
        void consultaItem(FilaAtributos &atributos, FilaItens &itens, int idItem);
        void consultaAtributo(FilaAtributos &atributos, FilaItens &itens, int idAtributo);
        void imprime() const;
        int getValor(int i, int j);
        void setValor(int i, int j, int valor);
        ~MatrizModoL();
    friend class MatrizModificadores;
};

#endif