#ifndef MATRIZ_MODIFICADORES_H
#define MATRIZ_MODIFICADORES_H

#include "matriz_modo_l.h"
#include "matriz_modo_t.h"
#include "build_aventureiro.h"
#include "fila_equilibrio.h"
#include "fila_poder.h"
#include "fila_sinergia.h"
#include "fila_itens.h"
#include "fila_atributos.h"
#include "fila_aventureiros.h"

class MatrizModificadores {
    private:
        char modo;
        MatrizModoL* matrizModoL; // so utiliza esse ponteiro se o modo for igual a 'L'
        MatrizModoT* matrizModoT; // so utiliza esse ponteiro se o modo for igual a 'T'

        void transicionaLparaT();
        void transicionaTparaL();

    public:
        FilaPoder filaPoder;
        FilaEquilibrio filaEquilibrio;
        FilaSinergia filaSinergia;

        MatrizModificadores();

        double calculaPoderItem(int idItem);
        double calculaEquilibrioItem(FilaAtributos &atributos, int idItem);
        void calculaBuild(BuildAventureiro &build, int T, long long* b, long long &normB2);
        double calculaSinergia(const long long* b, int T, long long normB2, int idItem);
        void consultaRecomendacao(int idAventureiro, FilaAventureiros &aventureiros, FilaAtributos &atributos, FilaItens &itens, std::string metricas[], double pesos[], int m, int n);
        
        void consultaItem(FilaAtributos &atributos, FilaItens &itens, int idItem);
        void consultaAtributo(FilaAtributos &atributos, FilaItens &itens, int idAtributo);
        int somaAtributos(BuildAventureiro &build, int idAtributo);
        void imprime() const;
        void setModo(char modo);
        void setValor(int idItem, int idAtributo, int valor);
        int getValor(int idItem, int idAtributo);
        ~MatrizModificadores();
};

#endif