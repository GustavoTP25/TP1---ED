#ifndef BUILD_AVENTUREIRO_H
#define BUILD_AVENTUREIRO_H

#include <string>
#include "item.h"
#include "fila_atributos.h"

class MatrizModificadores; // em matrizmodificadores eu tbm incluo a build, virando um ciclo. P evitar isso, declarei uma classe com msm nome

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
        void equiparItem(Item item, MatrizModificadores &matrizModificadores, int idAventureiro, BuildAventureiro &build);
        bool verificaItemEquipado(int idItem);
        void listarBuild(std::string nomeAventureiro, BuildAventureiro &build, MatrizModificadores &matrizModificadores, FilaAtributos &atributos);
        Item desequiparItem();
        void Limpa();
        ~BuildAventureiro();
};

#endif