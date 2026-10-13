#include "../include/build_aventureiro.h"

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

void BuildAventureiro::Limpa(){
    while (tamanho != 0){
        BuildAventureiro::desequiparItem();
    }
}

BuildAventureiro::~BuildAventureiro(){
    Limpa();
}