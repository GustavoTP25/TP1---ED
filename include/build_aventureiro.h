#ifndef BUILD_AVENTUREIRO_H
#define BUILD_AVENTUREIRO_H

#include <string>
#include "item.h"

class CelulaBuild {
    private:
        Item item;
        CelulaBuild* proximo;

    public:
        CelulaBuild();
    friend class BuildAventureiro;

};

class BuildAventureiro {
    private:
        CelulaBuild* topo;
        int tamanho;

    public:
        BuildAventureiro();
        void equiparItem(Item item);
        Item desequiparItem();
        void Limpa();
        ~BuildAventureiro();
};

#endif