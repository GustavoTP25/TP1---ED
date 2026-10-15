#include "../include/fila_itens.h"
#include <iostream>
#include "matriz_modificadores.h"

CelulaItem::CelulaItem(){
    proximo = NULL;
}

////////////////////////////////////////////

FilaItens::FilaItens(){
    frente = new CelulaItem();
    tras = frente;
    tamanho = 0;
}

void FilaItens::adicionarItem(std::string nome, MatrizModificadores &matrizMestricas){
    CelulaItem* p = new CelulaItem();
    p->item.setNome(nome);
    p->item.setId(tamanho);
    p->proximo = NULL;

    tras->proximo = p;
    tras = p;

    tamanho++;

    std::cout << "I " << p->item.getId() << std::endl;
}

Item FilaItens::pesquisa(int id){
    CelulaItem* p = frente->proximo;
    Item aux; // serve para somente caso não haja um item com determinado item (pois não é possível retornar null, então retorna um item que n existe)
    while (p != NULL){
        if (p->item.getId() == id)
            return p->item;
        p = p->proximo;
    }
    return aux;
}

void FilaItens::listarItens(){
    CelulaItem* p = frente->proximo;
    while (p != NULL){
        std::cout << p->item.getId() << " - " << p->item.getNome() << std::endl;
        p = p->proximo;
    }
}

void FilaItens::Limpa(){
    CelulaItem *p;
    p = frente->proximo;
    while (p != NULL) {
        frente->proximo = p->proximo;
        delete p;
        p = frente->proximo;
    }
    tras = frente;
}

FilaItens::~FilaItens(){
    FilaItens::Limpa();
    delete frente;
}