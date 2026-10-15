#include "../include/aventureiro.h"
#include "../include/fila_itens.h"

Aventureiro::Aventureiro(){
    this->id = -1;
    this->nome = "";
}

int Aventureiro::getId(){
    return this->id;
}

std::string Aventureiro::getNome(){
    return this->nome;
}

void Aventureiro::setId(int id){
    this->id = id;
}

void Aventureiro::listarBuild(MatrizModificadores &matrizModificadores, FilaAtributos &atributos){
    this->build.listarBuild(this->nome, this->build, matrizModificadores, atributos);
}

void Aventureiro::setNome(std::string nome){
    this->nome = nome;
}