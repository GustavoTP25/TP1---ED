#include "../include/matriz_modificadores.h"
#include <iostream>
#include <cmath>
#include <iomanip>

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
                soma += p->valor * build.contarItens(p->lin);
                p = p->proxColuna;
            }
        }
    } else {
        MatrizModoT* t = this->matrizModoT;
        for (int i = 0; i < t->tamanho; i++){
            if (t->vetor[i].idAtributo == idAtributo)
                soma += t->vetor[i].valor * build.contarItens(t->vetor[i].idItem);
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

void MatrizModificadores::calculaBuild(BuildAventureiro &build, int T, long long* b, long long &normB2){
    normB2 = 0;
    for (int a = 0; a < T; a++){
        b[a] = this->somaAtributos(build, a);
        normB2 += b[a] * b[a];
    }
}

double MatrizModificadores::calculaSinergia(const long long* b, int T, long long normB2, int idItem){
    if (normB2 == 0) return 0.0;                 // build vazia

    long long dot = 0;                           // soma de v_i(a) * b(a)
    long long n2 = 0;                            // soma de v_i(a)^2

    if (this->modo == 'L'){
        if (idItem >= 0 && idItem < matrizModoL->numeroLinhas){
            CelulaMatriz* p = matrizModoL->CabecasLinha[idItem]->proxLinha;
            while (p != NULL){
                if (p->col < T){
                    dot += (long long)p->valor * b[p->col];
                    n2  += (long long)p->valor * p->valor;
                }
                p = p->proxLinha;
            }
        }
    } else {
        MatrizModoT* t = this->matrizModoT;
        for (int i = 0; i < t->tamanho; i++){
            if (t->vetor[i].idItem == idItem && t->vetor[i].idAtributo < T){
                dot += (long long)t->vetor[i].valor * b[t->vetor[i].idAtributo];
                n2  += (long long)t->vetor[i].valor * t->vetor[i].valor;
            }
        }
    }

    if (n2 == 0) return 0.0;                     // item sem modificador
    return (double)dot / (std::sqrt((double)n2) * std::sqrt((double)normB2));
}

void MatrizModificadores::consultaRecomendacao(int idAventureiro, FilaAventureiros &aventureiros, FilaAtributos &atributos, FilaItens &itens, std::string metricas[], double pesos[], int m, int n){
    int T = atributos.tamanho;
    int N = itens.tamanho;

    Aventureiro* aventureiro = aventureiros.pesquisa(idAventureiro);
    BuildAventureiro *build = &aventureiro->build;


    long long* b = new long long[T];
    long long normB2;
    calculaBuild(*build, T, b, normB2);

    for (int i = 0; i < N; i++){
        filaPoder.setValor(i, calculaPoderItem(i));
        filaEquilibrio.setValor(i, calculaEquilibrioItem(atributos, i));
        filaSinergia.setValor(i, calculaSinergia(b, T, normB2, i));
    }

    long long* pontos = new long long[N];
    for (int i = 0; i < N; i++) pontos[i] = 0;
    

    for (int i = 0; i < m; i++){
        long long pesoCent = std::llround(pesos[i] * 100.0);
        if (metricas[i] == "SINERGIA")
            filaSinergia.acumulaPontos(pontos, pesoCent, N);
        else if (metricas[i] == "PODER")
            filaPoder.acumulaPontos(pontos, pesoCent, N);
        else if (metricas[i] == "EQUILIBRIO")
            filaEquilibrio.acumulaPontos(pontos, pesoCent, N);
    }

    //////////////////////////////////////////////

    long long* maximos = new long long[n]; // guarda os n maiores valores
    int* maximos_id = new int[n]; // guarda os ids dos n maiores valores

    bool* selecionado = new bool[N];; // armazena se um valor ja foi selecionado dentre os n maiores
    int quantidade = 0;
    for (int j = 0; j < N; j++)selecionado[j] = false;

    for (int i = 0; i < n && i < N; i++) {
        long long max = -1;
        int max_j = -1;

        for (int j = 0; j < N; j++) {
            if (!build->verificaItemEquipado(j) && !selecionado[j]) {
                if (max_j == -1 || pontos[j] > max) {
                    max = pontos[j];
                    max_j = j;
                }
            }
        }

        // Não existem mais itens candidatos.
        if (max_j == -1) {
            break;
        }

        maximos[i] = max;
        maximos_id[i] = max_j;

        selecionado[max_j] = true;
        quantidade++;
    }
    
    for (int i = 0; i < quantidade; i++)
        std::cout << "Q " << i + 1 << " " << maximos_id[i] << " "
        << std::fixed << std::setprecision(2) << maximos[i] / 100.0<< std::endl;

    delete[] b;
    delete[] maximos;
    delete[] maximos_id;
    delete[] selecionado;
    delete[] pontos;

    this->filaPoder.Limpa();
    this->filaEquilibrio.Limpa();
    this->filaSinergia.Limpa();
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