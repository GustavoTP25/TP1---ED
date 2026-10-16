#include "fila_aventureiros.h"
#include <iostream>

CelulaAventureiro::CelulaAventureiro(){
    proximo = NULL;
}

////////////////////////////////////////////

FilaAventureiros::FilaAventureiros(){
    frente = new CelulaAventureiro();
    tras = frente;
    tamanho = 0;
}

void FilaAventureiros::adicionarAventureiro(std::string nome){
    CelulaAventureiro* p = new CelulaAventureiro();
    p->item.setNome(nome);
    p->item.setId(tamanho);
    p->proximo = NULL;

    tras->proximo = p;
    tras = p;

    tamanho++;

    std::cout << "H " << p->item.getId() << std::endl;
}

Aventureiro* FilaAventureiros::pesquisa(int id){
    CelulaAventureiro* p = frente->proximo;
    while (p != NULL){
        if (p->item.getId() == id)
            return &p->item;
        p = p->proximo;
    }
    return NULL;
}

void FilaAventureiros::listarAventureiros(){
    CelulaAventureiro* p = frente->proximo;
    while (p != NULL){
        std::cout << p->item.getId() << " - " << p->item.getNome() << std::endl;
        p = p->proximo;
    }
}

bool FilaAventureiros::equiparItem(FilaItens &itens, int idAventureiro, int idItem, MatrizModificadores &matrizModificadores){
    Item item = itens.pesquisa(idItem);
    Aventureiro* aventureiro = this->pesquisa(idAventureiro);
    if (item.getId() != -1 && aventureiro != NULL){
        aventureiro->build.equiparItem(item);
        return 1;
    }
    return 0;
}

void FilaAventureiros::desequiparItem(FilaItens &itens, int idAventureiro){
    Aventureiro* aventureiro = this->pesquisa(idAventureiro);
    Item item = aventureiro->build.desequiparItem();

    if (item.getId() == -1)
        std::cout << "D " << aventureiro->getNome() << " VAZIO" << std::endl;
    else
        std::cout << "D " << aventureiro->getNome() << " " << item.getNome() << std::endl;
}

void FilaAventureiros::Limpa(){
    CelulaAventureiro *p;
    p = frente->proximo;
    while (p != NULL) {
        frente->proximo = p->proximo;
        delete p;
        p = frente->proximo;
    }
    tras = frente;
}

FilaAventureiros::~FilaAventureiros(){
    FilaAventureiros::Limpa();
    delete frente;
}