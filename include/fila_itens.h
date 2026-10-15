#ifndef FILA_ITENS_H
#define FILA_ITENS_H

#include <string>
#include "item.h"

class MatrizModificadores; // em matrizmodificadores eu tbm incluo a build, virando um ciclo. P evitar isso, declarei uma classe com msm nome

class CelulaItem {
    private:
        Item item;
        CelulaItem* proximo;

    public:
        CelulaItem();
    friend class FilaItens; // permite que FilaAventureiros acesse os atributos privados
};

// Uma fila encadeada para armzenar os itens
class FilaItens {
    private:
        CelulaItem* frente;
        CelulaItem* tras;
        int tamanho;
        void Limpa();

    public:
        FilaItens();
        void adicionarItem(std::string nome, MatrizModificadores &matrizModificadores);
        void listarItens();
        Item pesquisa(int id);
        ~FilaItens();
    friend class MatrizModoL;
};

#endif