#include "fila_equilibrio.h"
#include <iostream>
#include <cmath>

// para considerar as 6 casas decimais
static long long chave6(double x){
    return std::llround(x * 1000000.0);
}

CelulaEquilibrio::CelulaEquilibrio(){
    this->idItem = -1;
    this->valor = 0;
    this->proximo = NULL;
}

FilaEquilibrio::FilaEquilibrio(){
    frente = new CelulaEquilibrio();
    tamanho = 0;
}

void FilaEquilibrio::setValor(int idItem, double valor){
    CelulaEquilibrio* ant = frente;
    CelulaEquilibrio* p = frente->proximo;

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
        p = new CelulaEquilibrio();
        p->idItem = idItem;
        tamanho++;
    }

    p->valor = valor;

    // Procura a posição correta: valor decrescente,
    // e ID crescente em caso de empate
    ant = frente;
    CelulaEquilibrio* atual = frente->proximo;

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

void FilaEquilibrio::acumulaPontos(long long* pontos, long long pesoCent, int N){
    CelulaEquilibrio* p = frente->proximo;                // pula a cabeça
    int pos = 0;
    while (p != NULL){
        pontos[p->idItem] += pesoCent * (N - pos);
        pos++;
        p = p->proximo;
    }
}

void FilaEquilibrio::Limpa(){
    CelulaEquilibrio *p = frente->proximo;
    while (p != NULL) {
        frente->proximo = p->proximo;
        delete p;
        p = frente->proximo;
    }
    tamanho = 0;
}

FilaEquilibrio::~FilaEquilibrio(){
    Limpa();
    delete frente;
}