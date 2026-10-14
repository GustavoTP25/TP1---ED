#include "../include/matriz_modificadores.h"
#include <iostream>

MatrizModificadores::MatrizModificadores(){
    this->modo = 'L'; // por padrão sempre ira inicializar no modo L
    this->matrizModoL = new MatrizModoL();
    this->matrizModoT = NULL;
}

void MatrizModificadores::transicionaTparaL(){
    MatrizModoT* matrizT = this->matrizModoT;
    MatrizModoL* matrizL = new MatrizModoL();

    for (int i = 0; i < matrizT->tamanho; i++){
        Tripla tripla = matrizT->vetor[i];
        matrizL->setValor(tripla.idItem, tripla.idAtributo, tripla.valor);
    }
    delete matrizT;                
    this->matrizModoT = NULL;       
    this->matrizModoL = matrizL;
}

void MatrizModificadores::transicionaLparaT(){
    MatrizModoL* matrizL = this->matrizModoL;
    MatrizModoT* matrizT = new MatrizModoT();

    for (int i = 0; i < matrizL->numeroLinhas; i++) {
        CelulaMatriz* p = matrizL->CabecasLinha[i]->proxLinha;
        while (p != NULL) {
            matrizT->setValor(p->lin, p->col, p->valor);
            p = p->proxLinha;
        }
    }
    delete matrizL;
    this->matrizModoL = NULL;
    this->matrizModoT = matrizT;
}

void MatrizModificadores::setModo(char modo){
    std::cout << "E " << modo << std::endl;
    if (modo == this->modo) return;
    
    if (modo == 'L'){
        transicionaTparaL();
    } else if (modo == 'T'){
        transicionaLparaT();
    }
    this->modo = modo;
}

void MatrizModificadores::consultaItem(FilaAtributos &atributos, FilaItens &itens, int idItem){
    if (this->modo == 'L')
        this->matrizModoL->consultaItem(atributos, itens, idItem);
    else
        this->matrizModoT->consultaItem(atributos, itens, idItem);
}

void MatrizModificadores::setValor(int idItem, int idAtributo, int valor){
    if (this->modo == 'L')
        this->matrizModoL->setValor(idItem, idAtributo, valor);
    else if (this->modo == 'T')
        this->matrizModoT->setValor(idItem, idAtributo, valor);
}

int MatrizModificadores::getValor(int idItem, int idAtributo){
    int valor;
    if (this->modo == 'L')
        valor = this->matrizModoL->getValor(idItem, idAtributo);
    else
        valor = this->matrizModoT->getValor(idItem, idAtributo);
    return valor;
}

void MatrizModificadores::imprime() const{
    if (this->modo == 'L')
        matrizModoL->imprime();
    if (this->modo == 'T')
        matrizModoT->imprime();
}


MatrizModificadores::~MatrizModificadores(){
    if (this->modo == 'L')
        delete matrizModoL;
    else if (this->modo == 'T')
        delete matrizModoT;
}