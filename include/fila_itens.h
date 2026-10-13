#ifndef FILA_ITENS_H
#define FILA_ITENS_H

#include <string>
#include "item.h"

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
        void adicionarItem(std::string nome);
        void listarItens();
        Item pesquisa(int id);
        ~FilaItens();
    friend class MatrizModoL; 
};

#endif