#include "atributo.h"

Atributo::Atributo(){
    this->id = -1;
    this->nome = "";
}

int Atributo::getId(){
    return this->id;
}

std::string Atributo::getNome(){
    return this->nome;
}

void Atributo::setId(int id){
    this->id = id;
}

void Atributo::setNome(std::string nome){
    this->nome = nome;
}