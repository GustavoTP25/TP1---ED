#ifndef FILA_ENCOMENDAS_H
#define FILA_ENCOMENDAS_H

#include <string>
#include "encomenda.h"
#include "../include/fila_aventureiros.h"
#include "../include/fila_itens.h"

class CelulaEncomenda {
    private:
        Encomenda item;
        CelulaEncomenda* proximo;

    public:
        CelulaEncomenda();
    friend class FilaEncomendas;
};

// Uma fila que representa as encomendas da forja
class FilaEncomendas {
    private:
        CelulaEncomenda* frente;
        CelulaEncomenda* tras;
        int tamanho;
        void Limpa();

    public:
        FilaEncomendas();
        void adicionarEncomenda(int idAventureiro, int idItem);
        // é preciso passar o endereço de aventureiros e itens, pois se passar por cópia, quando a função terminar ela irá apagar a lista original devido ao destrutor
        void forjarItens(FilaAventureiros &aventureiros, FilaItens &itens, int k, MatrizModificadores &matrizModificadores);
        ~FilaEncomendas();

};

#endif