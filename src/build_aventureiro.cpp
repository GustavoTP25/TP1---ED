#include "build_aventureiro.h"
#include <iostream>
#include "build_aventureiro.h"
#include "matriz_modificadores.h"
#include "fila_atributos.h"

CelulaBuild::CelulaBuild(){
    this->item.setId(-1);
    this->item.setNome("");
    this->proximo = NULL;
}

////////////////////////////////////////////

BuildAventureiro::BuildAventureiro(){
    this->topo = NULL;
    this->tamanho = 0;
}

void BuildAventureiro::equiparItem(Item item){
    CelulaBuild *p = new CelulaBuild();
    p->item = item;
    p->proximo = topo;
    topo = p;
    tamanho++;
}

Item BuildAventureiro::desequiparItem(){
    Item aux;
    CelulaBuild *p;

    if (tamanho == 0){
        aux.setId(-1);
        aux.setNome("");
        return aux;
    }

    aux = topo->item;
    p = topo;
    topo = topo->proximo;
    delete p;
    tamanho--;
        
    return aux;
}

bool BuildAventureiro::verificaItemEquipado(int idItem){
    CelulaBuild* p = this->topo;
    while (p != NULL){
        if (p->item.getId() == idItem)
            return 1;
        p = p->proximo;
    }
    return 0;
}

int BuildAventureiro::contarItens(int idItem){
    CelulaBuild* p = this->topo;
    int soma = 0;
    while (p != NULL){
        if (p->item.getId() == idItem)
            soma++;
        p = p->proximo;
    }
    return soma;
}

void BuildAventureiro::listarBuild(std::string nomeAventureiro, BuildAventureiro &build, MatrizModificadores &matrizModificadores, FilaAtributos &atributos){
    CelulaAtributo* p = atributos.frente;
    std::cout << "LH " << nomeAventureiro;
    int i = 1;
    int soma;
    bool aux = 0;
    while (p != NULL){
        soma = matrizModificadores.somaAtributos(build, p->item.getId());
        if (soma != 0){
            std::cout << " atributo_" << i << " " <<  p->item.getId() << " " << soma;
            aux = 1;
            i++;
        }
        p = p->proximo;
    }
    if (aux == 0)
        std::cout << " VAZIO";
    std::cout << std::endl;
    
}

void BuildAventureiro::Limpa(){
    while (tamanho != 0){
        BuildAventureiro::desequiparItem();
    }
}

BuildAventureiro::~BuildAventureiro(){
    Limpa();
}