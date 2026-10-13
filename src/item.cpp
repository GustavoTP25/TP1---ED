#include "../include/item.h"

Item::Item(){
    this->id = -1;
    this->nome = "";
}

int Item::getId(){
    return this->id;
}

std::string Item::getNome(){
    return this->nome;
}

void Item::setId(int id){
    this->id = id;
}

void Item::setNome(std::string nome){
    this->nome = nome;
}