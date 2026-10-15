#ifndef FILA_ATRIBUTOS_H
#define FILA_ATRIBUTOS_H

#include <string>
#include "atributo.h"

class CelulaAtributo {
    private:
        Atributo item;
        CelulaAtributo* proximo;

    public:
        CelulaAtributo();
    friend class FilaAtributos;
    friend class BuildAventureiro;
};

// Uma fila encadeada para armzenar os aventureiros
class FilaAtributos {
    private:
        CelulaAtributo* frente;
        CelulaAtributo* tras;
        int tamanho;
        void Limpa();

    public:
        FilaAtributos();
        void adicionarAtributo(std::string nome);
        void listarAtributos();
        Atributo pesquisa(int id);
        ~FilaAtributos();
    friend class MatrizModoL;
    friend class BuildAventureiro;

};

#endif