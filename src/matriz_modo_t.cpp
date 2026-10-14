#include "../include/matriz_modo_t.h"
#include <iostream>

Tripla::Tripla(){
    this->idItem = -1;
    this->idAtributo = -1;
    this->valor = 0;
}

MatrizModoT::MatrizModoT(){
    vetor = NULL;
    tamanho = 0;
}

Tripla* MatrizModoT::getTripla(int idItem, int idAtributo){
    for (int i = 0; i < tamanho; i++){
        if (vetor[i].idItem == idItem && vetor[i].idAtributo == idAtributo){
            return &vetor[i];
        }
    }
    return NULL;
}

void MatrizModoT::setValor(int idItem, int idAtributo, int valor){
    Tripla* p = getTripla(idItem, idAtributo);

    if (p != NULL){
        // o primeiro caso é se a tripla ja existe e o valor é diferente de 0, e basta então trocar seu valor
        if (valor != 0){
            p->valor = valor;
            return;
        // o segundo caso é se a tripla existe e o valor passado é zero, então é preciso apaga-la do vetor
        // a ideia vai ser criar um novo vetor com as mesmas informações, excluindo somente aquela que deve ser apagada
        } else {
            Tripla* novoVetor = new Tripla[tamanho - 1];

            int j = 0;
            for (int i = 0; i < tamanho; i++){
                if (!(vetor[i].idItem == idItem && vetor[i].idAtributo == idAtributo)){
                    novoVetor[j] = vetor[i];
                    j++;
                }
            }

            delete[] vetor;
            vetor = novoVetor;
            tamanho--;
            return;
        }
    } else {
        // o terceiro caso é se a tripla nao existe e o valor passado é zero, assim nada muda
        if (valor == 0)
            return;

        // o ultimo caso é se a tripla nao existe e o valor é diferente de zero
        // assim, é preciso criar uma nova tripla
        //obs: adicionar a inserção já ordenada dps
        Tripla* novoVetor = new Tripla[tamanho + 1];

        int j = 0;
        for (int i = 0; i < tamanho; i++){
            novoVetor[j] = vetor[i];
            j++;
        }
        novoVetor[j].idItem = idItem;
        novoVetor[j].idAtributo = idAtributo;
        novoVetor[j].valor = valor;
        delete[] vetor;
        vetor = novoVetor;
        tamanho++;
    }
}

void MatrizModoT::consultaItem(FilaAtributos &atributos, FilaItens &itens, int idItem){
    std::cout << "LI " << itens.pesquisa(idItem).getNome();
    bool aux = 0;
    for (int i = 0; i < this->tamanho; i++){
        if (this->vetor[i].idItem == idItem){
            aux = 1;
            std::cout << " " << atributos.pesquisa(vetor[i].idAtributo).getNome() << " " << vetor[i].valor;
        }
    }
    if (aux == 0)
        std::cout << " VAZIO";
    std::cout << std::endl;
}

void MatrizModoT::imprime(){
    for(int i = 0; i < this->tamanho; i++){
        std::cout << "(" << this->vetor[i].idItem << ", "<< this->vetor[i].idAtributo << ", " << this->vetor[i].valor << ") ";
    }
    std::cout << std::endl;
}


int MatrizModoT::getValor(int idItem, int idAtributo){
    Tripla* p = getTripla(idItem, idAtributo);
    if (p != NULL)
        return p->valor;
    return 0;
}

MatrizModoT::~MatrizModoT() {
    delete[] vetor;
}