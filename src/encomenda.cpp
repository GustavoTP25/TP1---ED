#include "encomenda.h"

Encomenda::Encomenda(){
    this->idAventureiro = -1;
    this->idItem = -1;
}

int Encomenda::getIdAventureiro(){
    return this->idAventureiro;
}

int Encomenda::getIdItem(){
    return this->idItem;
}

void Encomenda::setIdAventureiro(int idAventureiro){
    this->idAventureiro = idAventureiro;
}

void Encomenda::setIdItem(int idItem){
    this->idItem = idItem;
}