#ifndef FILA_AVENTUREIROS_H
#define FILA_AVENTUREIROS_H

#include <string>
#include "aventureiro.h"

class CelulaAventureiro {
    private:
        Aventureiro item;
        CelulaAventureiro* proximo;

    public:
        CelulaAventureiro();
    friend class FilaAventureiros; // permite que FilaAventureiros acesse os atributos privados
};

// Uma fila encadeada para armzenar os aventureiros
class FilaAventureiros {
    private:
        CelulaAventureiro* frente;
        CelulaAventureiro* tras;
        int tamanho;
        void Limpa();

    public:
        FilaAventureiros();
        void adicionarAventureiro(std::string nome);
        void listarAventureiros();
        Aventureiro* pesquisa(int id);

        bool equiparItem(FilaItens &itens, int idAventureiro, int idItem, MatrizModificadores &matrizModificadores);
        void desequiparItem(FilaItens &itens, int idAventureiro);

        ~FilaAventureiros();

};

#endif