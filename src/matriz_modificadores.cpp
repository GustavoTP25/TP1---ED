#include "../include/matriz_modificadores.h"
#include <iostream>
#include <cmath>

FilaPoder::FilaPoder(){
    frente = new CelulaMetrica();
    tamanho = 0;
}

FilaEquilibrio::FilaEquilibrio(){
    frente = new CelulaMetrica();
    tamanho = 0;
}

FilaSinergia::FilaSinergia(){
    frente = new CelulaSinergia();
    tamanho = 0;
}

FilaPoder::~FilaPoder(){
    CelulaMetrica *p;
    p = frente->proximo;
    while (p != NULL) {
        frente->proximo = p->proximo;
        delete p;
        p = frente->proximo;
    }
    delete frente;
}

FilaEquilibrio::~FilaEquilibrio(){
    CelulaMetrica *p;
    p = frente->proximo;
    while (p != NULL) {
        frente->proximo = p->proximo;
        delete p;
        p = frente->proximo;
    }
    delete frente;
}

FilaSinergia::~FilaSinergia(){
    CelulaSinergia *p;
    p = frente->proximo;
    while (p != NULL) {
        frente->proximo = p->proximo;
        delete p;
        p = frente->proximo;
    }
    delete frente;
}

void FilaPoder::setValor(int idItem, double valor) {
    CelulaMetrica* ant = frente;
    CelulaMetrica* p = frente->proximo;

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
        p = new CelulaMetrica();
        p->idItem = idItem;
        tamanho++;
    }

    p->valor = valor;

    // Procura a posição correta: valor decrescente,
    // e ID crescente em caso de empate
    ant = frente;
    CelulaMetrica* atual = frente->proximo;

    while (atual != NULL &&
           (atual->valor > valor ||
            (atual->valor == valor && atual->idItem < idItem))) {
        ant = atual;
        atual = atual->proximo;
    }

    // Insere na posição correta
    p->proximo = atual;
    ant->proximo = p;
}

void FilaEquilibrio::setValor(int idItem, double valor){
    CelulaMetrica* ant = frente;
    CelulaMetrica* p = frente->proximo;

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
        p = new CelulaMetrica();
        p->idItem = idItem;
        tamanho++;
    }

    p->valor = valor;

    // Procura a posição correta: valor decrescente,
    // e ID crescente em caso de empate
    ant = frente;
    CelulaMetrica* atual = frente->proximo;

    while (atual != NULL &&
           (atual->valor > valor ||
            (atual->valor == valor && atual->idItem < idItem))) {
        ant = atual;
        atual = atual->proximo;
    }

    // Insere na posição correta
    p->proximo = atual;
    ant->proximo = p;
}

void FilaSinergia::setValor(int idItem, int idAventureiro, double valor) {
    CelulaSinergia* ant = frente;
    CelulaSinergia* p = frente->proximo;

    // Procura o item e o aventureiro na lista
    while (p != NULL) {
        if (p->idItem == idItem && p->idAventureiro == idAventureiro)
            break;
    
        ant = p;
        p = p->proximo;
    }

    // Se encontrou, remove a célula da posição atual
    if (p != NULL) {
        ant->proximo = p->proximo;
    } else {
        // Se não encontrou, cria uma nova célula
        p = new CelulaSinergia();
        p->idItem = idItem;
        p->idAventureiro = idAventureiro;

        tamanho++;
    }

    p->valor = valor;

    // Procura a posição correta para inserir a célula
    ant = frente;
    CelulaSinergia* atual = frente->proximo;

    while (atual != NULL) {
        // Se o valor atual for maior, continua avançando
        if (atual->valor > valor) {
            ant = atual;
            atual = atual->proximo;
        }
        // Se os valores forem iguais, compara os IDs
        else if (atual->valor == valor) {
            if (atual->idItem < idItem) {
                ant = atual;
                atual = atual->proximo;
            }
            else if (atual->idItem == idItem &&
                     atual->idAventureiro < idAventureiro) {
                ant = atual;
                atual = atual->proximo;
            }
            else {
                break;
            }
        }
        // Se o valor atual for menor, encontrou a posição
        else {
            break;
        }
    }

    // Insere a célula na posição encontrada
    p->proximo = atual;
    ant->proximo = p;
}

//////////////////////////////////////////////////////////////

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

void MatrizModificadores::consultaAtributo(FilaAtributos &atributos, FilaItens &itens, int idAtributo){
    if (this->modo == 'L')
        this->matrizModoL->consultaAtributo(atributos, itens, idAtributo);
    else
        this->matrizModoT->consultaAtributo(atributos, itens, idAtributo);
}

int MatrizModificadores::somaAtributos(BuildAventureiro &build, int idAtributo){
    int soma = 0;
    if (this->modo == 'L'){
        if (idAtributo >= 0 && idAtributo < matrizModoL->numeroColunas){
            CelulaMatriz* p = matrizModoL->CabecasColuna[idAtributo]->proxColuna;
            while (p != NULL){
                if (build.verificaItemEquipado(p->lin))
                    soma += p->valor;
                p = p->proxColuna;
            }
        }
    } else {
        for (int i = 0; i < this->matrizModoT->tamanho; i++){
            if (build.verificaItemEquipado(this->matrizModoT->vetor[i].idItem) && matrizModoT->vetor[i].idAtributo == idAtributo)
                soma += this->matrizModoT->vetor[i].valor;
        }
    }
    return soma;
}

double MatrizModificadores::calculaPoderItem(int idItem){
    double poder = 0;
    if (this->modo == 'L'){
        CelulaMatriz* p = matrizModoL->CabecasLinha[idItem]->proxLinha;
            while (p != NULL){
                poder += p->valor;
                p = p->proxLinha;
            }
    } else {
        for (int i = 0; i < this->matrizModoT->tamanho; i++){
            if (this->matrizModoT->vetor[i].idItem == idItem)
                poder += this->matrizModoT->vetor[i].valor;
        }
    }
    return poder;
}

double MatrizModificadores::calculaEquilibrioItem(FilaAtributos &atributos, int idItem){
    int T = atributos.tamanho;
    if (T == 0) return 1.0;

    double u = this->calculaPoderItem(idItem) / T;
    double somatorio = 0;
    int naoNulos = 0;

    if (this->modo == 'L'){
        if (idItem >= 0 && idItem < matrizModoL->numeroLinhas){
            CelulaMatriz* p = matrizModoL->CabecasLinha[idItem]->proxLinha;
            while (p != NULL){
                somatorio += (p->valor - u) * (p->valor - u);
                naoNulos++;
                p = p->proxLinha;
            }
        }
    } else {
        MatrizModoT* t = this->matrizModoT;
        for (int i = 0; i < this->matrizModoT->tamanho; i++){
            if (this->matrizModoT->vetor[i].idItem == idItem){
                somatorio += (t->vetor[i].valor - u) * (t->vetor[i].valor - u);
                naoNulos++;
            }
        }
    }
    somatorio += (T - naoNulos) * u * u;
    double sigma = std::sqrt(somatorio / T);
    return 1.0 / (1.0 + sigma);
}

double MatrizModificadores::calculaSinergia(BuildAventureiro &build, int idItem){
    double somatorio1, somatorio2, somatorio3 = 0;
    if (this->modo == 'L'){
        if (idItem >= 0 && idItem < matrizModoL->numeroLinhas){
            CelulaMatriz* p = matrizModoL->CabecasLinha[idItem]->proxLinha;
            while (p != NULL){
                somatorio1 += p->valor * this->somaAtributos(build, p->col);
                somatorio2 += p->valor * p->valor;
                somatorio3 += this->somaAtributos(build, p->col) * this->somaAtributos(build, p->col);
                p = p->proxLinha;
            }
        }
    } else {
        MatrizModoT* t = this->matrizModoT;
        for (int i = 0; i < this->matrizModoT->tamanho; i++){
            if (this->matrizModoT->vetor[i].idItem == idItem){
                somatorio1 += this->matrizModoT->vetor[i].valor * this->somaAtributos(build, this->matrizModoT->vetor[i].idAtributo);
                somatorio2 += this->matrizModoT->vetor[i].valor * this->matrizModoT->vetor[i].valor;
                somatorio3 += this->somaAtributos(build, this->matrizModoT->vetor[i].idAtributo) * this->somaAtributos(build, this->matrizModoT->vetor[i].idAtributo);
            }
        }
    }
    if (somatorio2 == 0 || somatorio3 == 0) return 0.0;
    return somatorio1 / (sqrt(somatorio2) * sqrt(somatorio3));
}

void MatrizModificadores::setValor(int idItem, int idAtributo, int valor, FilaAtributos &atributos){
    if (this->modo == 'L')
        this->matrizModoL->setValor(idItem, idAtributo, valor);
    else if (this->modo == 'T')
        this->matrizModoT->setValor(idItem, idAtributo, valor);

    // sempre que um item é adicionado, a lista de métricas são atualizadas
    filaPoder.setValor(idItem, calculaPoderItem(idItem));
    filaEquilibrio.setValor(idItem, calculaEquilibrioItem(atributos, idItem));
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