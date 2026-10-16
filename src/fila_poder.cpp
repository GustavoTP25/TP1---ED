#include "../include/fila_poder.h"
#include <iostream>
#include <cmath>

// para considerar as 6 casas decimais
static long long chave6(double x){
    return std::llround(x * 1000000.0);
}

CelulaPoder::CelulaPoder(){
    this->idItem = -1;
    this->valor = 0;
    this->proximo = NULL;
}

FilaPoder::FilaPoder(){
    frente = new CelulaPoder();
    tamanho = 0;
}

void FilaPoder::setValor(int idItem, double valor) {
    CelulaPoder* ant = frente;
    CelulaPoder* p = frente->proximo;

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
        p = new CelulaPoder();
        p->idItem = idItem;
        tamanho++;
    }

    p->valor = valor;

    // Procura a posição correta: valor decrescente,
    // e ID crescente em caso de empate
    ant = frente;
    CelulaPoder* atual = frente->proximo;

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

void FilaPoder::acumulaPontos(long long* pontos, long long pesoCent, int N){
    CelulaPoder* p = frente->proximo;                // pula a cabeça
    int pos = 0;
    while (p != NULL){
        pontos[p->idItem] += pesoCent * (N - pos);
        pos++;
        p = p->proximo;
    }
}

void FilaPoder::Limpa(){
    CelulaPoder *p = frente->proximo;
    while (p != NULL) {
        frente->proximo = p->proximo;
        delete p;
        p = frente->proximo;
    }
    tamanho = 0;
}

FilaPoder::~FilaPoder(){
    Limpa();
    delete frente;
}