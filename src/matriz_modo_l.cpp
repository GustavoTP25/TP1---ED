#include "../include/matriz_modo_l.h"
#include <iostream>

CelulaMatriz::CelulaMatriz(int lin, int col, int valor, CelulaMatriz* proxLinha, CelulaMatriz* proxColuna){
    this->lin = lin;
    this->col = col;
    this->valor = valor;
    this->proxLinha = proxLinha;
    this->proxColuna = proxColuna;
}

MatrizModoL::MatrizModoL(){
    numeroLinhas = 0; 
    numeroColunas = 0; 
    tamanho = 0;
    CabecasLinha = NULL;
    CabecasColuna = NULL;
}

//recebe uma linha i e uma coluna j, e retorna a celula anterior na linha
// é preciso dessa função pois para adicionar e remover utilizamos ponteiros
// das celulas anteriores
CelulaMatriz* MatrizModoL::LinhaAnterior(int i, int j) const {
    CelulaMatriz* p = CabecasLinha[i];
    while (p->proxLinha != NULL && p->proxLinha->col < j)
        p = p->proxLinha;
    return p;
}

//recebe uma linha i e uma coluna j, e retorna a celula anterior na coluna
// é preciso dessa função pois para adicionar e remover utilizamos ponteiros
// das celulas anteriores
CelulaMatriz* MatrizModoL::ColunaAnterior(int i, int j) const {
    CelulaMatriz* p = CabecasColuna[j];
    while (p->proxColuna != NULL && p->proxColuna->lin < i)
        p = p->proxColuna;
    return p;
}

int MatrizModoL::getValor(int i, int j){
    CelulaMatriz* linhaAnterior = LinhaAnterior(i, j);
    CelulaMatriz* p = linhaAnterior->proxLinha;
    
    if (p != NULL && p->col == j)
        return linhaAnterior->proxLinha->valor;
        
    return 0;
}

void MatrizModoL::ampliaLinhas(int novoNumero) {
    CelulaMatriz** nova = new CelulaMatriz*[novoNumero];
    for (int k = 0; k < numeroLinhas; k++)
        nova[k] = CabecasLinha[k];                       // só copia o ponteiro
    for (int k = numeroLinhas; k < novoNumero; k++)
        nova[k] = new CelulaMatriz{k, -1, 0, NULL, NULL}; // cabeça da linha k
    delete[] CabecasLinha;                               // só o vetor de ponteiros
    CabecasLinha = nova;
    numeroLinhas = novoNumero;
}

void MatrizModoL::ampliaColunas(int novoNumero) {
    CelulaMatriz** nova = new CelulaMatriz*[novoNumero];
    for (int k = 0; k < numeroColunas; k++)
        nova[k] = CabecasColuna[k];
    for (int k = numeroColunas; k < novoNumero; k++)
        nova[k] = new CelulaMatriz{-1, k, 0, NULL, NULL}; // cabeça da coluna k
    delete[] CabecasColuna;
    CabecasColuna = nova;
    numeroColunas = novoNumero;
}

void MatrizModoL::setValor(int i, int j, int valor){
    // se a celula[i][j] nao existir, a funcao Linhaanterior e ColunaAnterior falharia
    if (i < numeroLinhas && j < numeroColunas){
        CelulaMatriz* linhaAnterior = LinhaAnterior(i, j);
        CelulaMatriz* colunaAnterior = ColunaAnterior(i, j);
        CelulaMatriz* p = linhaAnterior->proxLinha;

        if (p != NULL && p->col == j){
            // o primeiro caso é a celula existir e o valor for diferente de zero: so altera o valor
            if (valor != 0){
                p->valor = valor;
                return;
            // o segundo caso é a celula existir e o valor for 0, dai é preciso apagar a celula
            } else {
                linhaAnterior->proxLinha = p->proxLinha;
                colunaAnterior->proxColuna = p->proxColuna;
                delete p;
                tamanho--;
                return;
            }
        }
    }

    //o terceiro caso é se a celula[i][j] nao existe e o valor é 0, nao ha nada a ser feito
    if (valor == 0)
        return;

    //o ultimo caso é: a celula nao existe e o valor é diferente de zero
    // aqui é o mais delicado, pois se idItem/idAtributo nao existirem nos vetores cabeças
    // sera necessario modificar os cabecas
    if (i >= numeroLinhas)  ampliaLinhas(i + 1);
    if (j >= numeroColunas) ampliaColunas(j + 1);

    CelulaMatriz* linhaAnterior  = LinhaAnterior(i, j);
    CelulaMatriz* colunaAnterior = ColunaAnterior(i, j);
    CelulaMatriz* nova = new CelulaMatriz(i, j, valor, linhaAnterior->proxLinha, colunaAnterior->proxColuna);
    linhaAnterior->proxLinha = nova;
    colunaAnterior->proxColuna = nova;
    tamanho++;

}

void MatrizModoL::imprime() const {
    for (int i = 0; i < numeroLinhas; i++) {
        CelulaMatriz* p = CabecasLinha[i]->proxLinha;   // pula a cabeça
        for (int j = 0; j < numeroColunas; j++) {
            if (p != NULL && p->col == j) {
                std::cout << p->valor << " ";
                p = p->proxLinha;                       // avança na lista da linha
            } else {
                std::cout << "0 ";
            }
        }
        std::cout << "\n";
    }
}

MatrizModoL::~MatrizModoL(){
    // apagas as celulas pelas linhas
    for (int i = 0; i < numeroLinhas; i++) {
        CelulaMatriz* p = CabecasLinha[i];
        while (p != NULL)   {
            CelulaMatriz* q = p->proxLinha; 
            delete p; 
            p = q;
        }
    }
    // apaga os cabecas
    for (int j = 0; j < numeroColunas; j++) {
        delete CabecasColuna[j];
        delete[] CabecasLinha; 
        delete[] CabecasColuna;
    }
}