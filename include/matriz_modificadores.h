#ifndef MATRIZ_MODIFICADORES_H
#define MATRIZ_MODIFICADORES_H

#include "matriz_modo_l.h"
#include "matriz_modo_t.h"
#include "build_aventureiro.h"

class CelulaMetrica {
    private:
        int idItem;
        double valor;
        CelulaMetrica* proximo;
    friend class FilaPoder;
    friend class FilaEquilibrio;
};  

class CelulaSinergia {
    private:
        int idItem;
        int idAventureiro;
        double valor;
        CelulaSinergia* proximo;
    friend class FilaSinergia;
};  

class FilaPoder {
    private:
        CelulaMetrica* frente;
        int tamanho;
    
    public:
        FilaPoder();
        void setValor(int idItem, double valor);
        ~FilaPoder();
};

class FilaEquilibrio {
    private:
        CelulaMetrica* frente;
        int tamanho;
    
    public:
        FilaEquilibrio();
        void setValor(int idItem, double valor);
        ~FilaEquilibrio();
};

class FilaSinergia {
    private:
        CelulaSinergia* frente;
        int tamanho;
    
    public:
        FilaSinergia();
        void setValor(int idItem, int idAventureiro, double valor);
        ~FilaSinergia();
};

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
        double calculaSinergia(BuildAventureiro &build, int idItem);
        
        void consultaItem(FilaAtributos &atributos, FilaItens &itens, int idItem);
        void consultaAtributo(FilaAtributos &atributos, FilaItens &itens, int idAtributo);
        int somaAtributos(BuildAventureiro &build, int idAtributo);
        void imprime() const;
        void setModo(char modo);
        void setValor(int idItem, int idAtributo, int valor, FilaAtributos &atributos);
        int getValor(int idItem, int idAtributo);
        ~MatrizModificadores();
};

#endif