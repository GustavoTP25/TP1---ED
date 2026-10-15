#include "../include/fila_encomendas.h"
#include <iostream>

CelulaEncomenda::CelulaEncomenda(){
    this->proximo = NULL;
}

FilaEncomendas::FilaEncomendas(){
    frente = new CelulaEncomenda();
    tras = frente;
    tamanho = 0;
}

void FilaEncomendas::adicionarEncomenda(int idAventureiro, int idItem){
    CelulaEncomenda* p = new CelulaEncomenda();
    p->item.setIdAventureiro(idAventureiro);
    p->item.setIdItem(idItem);
    p->proximo = NULL;

    tras->proximo = p;
    tras = p;

    tamanho++;
    std::cout << "F " << tamanho << std::endl;
}

void FilaEncomendas::forjarItens(FilaAventureiros &aventureiros, FilaItens &itens, int k, MatrizModificadores &matrizModificadores){
    CelulaEncomenda *p = frente->proximo;
    std::string encomendas = ""; 

    int i = 0;
    while (p != NULL && i < k) {
        aventureiros.equiparItem(itens, p->item.getIdAventureiro(), p->item.getIdItem(), matrizModificadores);
        encomendas += "encomenda_" + std::to_string(i + 1) + " " + std::to_string(p->item.getIdAventureiro()) 
            + " " + std::to_string(p->item.getIdItem()) + " "; // conferir se o espaço no final nao dará problema no vpl

        frente->proximo = p->proximo;
        delete p;
        p = frente->proximo;
        i++;
    }
    std::cout << "Z " << i << std::endl;
    
    if (i != 0)
        std::cout << encomendas << std::endl;
    tras = frente;
}

void FilaEncomendas::Limpa(){
    CelulaEncomenda *p;
    p = frente->proximo;
    while (p != NULL) {
        frente->proximo = p->proximo;
        delete p;
        p = frente->proximo;
    }
    tras = frente;
}

FilaEncomendas::~FilaEncomendas(){
    FilaEncomendas::Limpa();
    delete frente;
}

