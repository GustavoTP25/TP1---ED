#include "fila_atributos.h"
#include <iostream>

CelulaAtributo::CelulaAtributo(){
    proximo = NULL;
}

////////////////////////////////////////////

FilaAtributos::FilaAtributos(){
    frente = new CelulaAtributo();
    tras = frente;
    tamanho = 0;
}

void FilaAtributos::adicionarAtributo(std::string nome){
    CelulaAtributo* p = new CelulaAtributo();
    p->item.setNome(nome);
    p->item.setId(tamanho);
    p->proximo = NULL;

    tras->proximo = p;
    tras = p;

    tamanho++;

    std::cout << "A " << p->item.getId() << std::endl;
}

Atributo FilaAtributos::pesquisa(int id){
    CelulaAtributo* p = frente->proximo;
    Atributo aux; // serve para somente caso não haja um item com determinado item (pois não é possível retornar null, então retorna um item que n existe)
    while (p != NULL){
        if (p->item.getId() == id)
            return p->item;
        p = p->proximo;
    }
    return aux;
}

void FilaAtributos::listarAtributos(){
    CelulaAtributo* p = frente->proximo;
    while (p != NULL){
        std::cout << p->item.getId() << " - " << p->item.getNome() << std::endl;
        p = p->proximo;
    }
}

void FilaAtributos::Limpa(){
    CelulaAtributo *p;
    p = frente->proximo;
    while (p != NULL) {
        frente->proximo = p->proximo;
        delete p;
        p = frente->proximo;
    }
    tras = frente;
}

FilaAtributos::~FilaAtributos(){
    FilaAtributos::Limpa();
    delete frente;
}