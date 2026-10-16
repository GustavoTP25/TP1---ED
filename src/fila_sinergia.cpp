#include "../include/fila_sinergia.h"
#include <iostream>
#include <cmath>

// para considerar as 6 casas decimais
static long long chave6(double x){
    return std::llround(x * 1000000.0);
}

CelulaSinergia::CelulaSinergia(){
    this->idItem = -1;
    this->valor = 0;
    this->proximo = NULL;
}

FilaSinergia::FilaSinergia(){
    frente = new CelulaSinergia();
    tamanho = 0;
}

void FilaSinergia::setValor(int idItem, double valor) {
    CelulaSinergia* ant = frente;
    CelulaSinergia* p = frente->proximo;

    // Procura o item na lista, ignorando o sentinela
    while (p != NULL && p->idItem != idItem) {
        ant = p;
        p = p->proximo;
    }

    if (p != NULL) {
        // O item já existe: remove da posição atual
        ant->proximo = p->proximo;
        p->proximo = NULL;
    } else {
        // O item não existe: cria uma nova célula
        p = new CelulaSinergia();
        p->idItem = idItem;
        tamanho++;
    }

    p->valor = valor;

    // Procura a posição correta: valor decrescente,
    // e ID crescente em caso de empate
    ant = frente;
    CelulaSinergia* atual = frente->proximo;

    long long k = chave6(valor);
    while (atual != NULL &&
       (chave6(atual->valor) > k ||
       (chave6(atual->valor) == k && atual->idItem < idItem))) {
        ant = atual;
        atual = atual->proximo;
    }

    // Insere na posição correta
    p->proximo = atual;
    ant->proximo = p;
}

void FilaSinergia::acumulaPontos(long long* pontos, long long pesoCent, int N){
    CelulaSinergia* p = frente->proximo;                // pula a cabeça
    int pos = 0;
    while (p != NULL){
        pontos[p->idItem] += pesoCent * (N - pos);
        pos++;
        p = p->proximo;
    }
}

void FilaSinergia::Limpa(){
    CelulaSinergia *p = frente->proximo;
    while (p != NULL) {
        frente->proximo = p->proximo;
        delete p;
        p = frente->proximo;
    }
    tamanho = 0;
}

FilaSinergia::~FilaSinergia(){
    Limpa();
    delete frente;
}