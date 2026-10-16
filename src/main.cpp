#include "../include/fila_aventureiros.h"
#include "../include/fila_encomendas.h"
#include "../include/matriz_modificadores.h"
#include <iostream>
#include <fstream>
#include <sstream>

int main(){
    std::ifstream arquivo("entrada.txt");
    if (!arquivo.is_open()) {
        std::cout << "Erro ao abrir o arquivo.";
        return 1;
    }

    FilaAventureiros aventureiros;
    FilaItens itens;
    FilaAtributos atributos;
    FilaEncomendas encomendas;
    MatrizModificadores matrizModificadores;

    std::string linha;
    while (std::getline(arquivo, linha)) {
        if (linha.empty()) 
            continue;

        std::stringstream ss(linha);
        std::string comando;
        ss >> comando;

        if (comando == "H"){ // adicionar aventureiro
            std::string nome;
            ss >> nome;
            aventureiros.adicionarAventureiro(nome);

        } else if (comando == "E"){ // seleciona o modo da matriz de modificadores
            char modo;
            ss >> modo;
            matrizModificadores.setModo(modo);

        } else if (comando == "IM"){
            matrizModificadores.imprime();

        } else if (comando == "I"){ // adicionar item
            std::string nome;
            ss>> nome;
            itens.adicionarItem(nome, matrizModificadores);

        } else if (comando == "A"){ //adicionar atributo
            std::string nome;
            ss >> nome;
            atributos.adicionarAtributo(nome);
        
        } else if (comando == "D"){ // desequipar item de um aventureiro
            int aventureiro;
            ss >> aventureiro;
            aventureiros.desequiparItem(itens, aventureiro);

        } else if (comando == "F"){ // coloca um item na fila das encomendas
            int aventureiro, item;
            ss >> aventureiro >> item;
            encomendas.adicionarEncomenda(aventureiro, item);

        } else if (comando == "Z"){ // forja n itens
            int turnos;
            ss >> turnos;
            encomendas.forjarItens(aventureiros, itens, turnos, matrizModificadores);

        } else if (comando == "M"){ // adiciona um modificador a um item
            int idItem, idAtributo, valor;
            ss >> idItem >> idAtributo >> valor;
            matrizModificadores.setValor(idItem, idAtributo, valor);
            std::cout << "M " << itens.pesquisa(idItem).getNome() << " " << atributos.pesquisa(idAtributo).getNome() << " " << valor << std::endl;
        
        } else if (comando == "LI"){ // listagem dos atributos associados a um item
            int idItem;
            ss >> idItem;
            matrizModificadores.consultaItem(atributos, itens, idItem);

        } else if (comando == "LA"){ // listagem dos itens associados a um atributo
            int idAtributo;
            ss >> idAtributo;
            matrizModificadores.consultaAtributo(atributos, itens, idAtributo);

        } else if (comando == "LH"){ // listagem da build
            int idAventureiro;
            ss >> idAventureiro;
            aventureiros.pesquisa(idAventureiro)->listarBuild(matrizModificadores, atributos);
        } else if (comando == "Q"){
            int idAventureiro, n, m;
            ss >> idAventureiro >> n >> m;
            std::string metricas[m];
            double pesos[m];

            for (int i = 0; i < m; i++){
                ss >> metricas[i];
                ss >> pesos[i];
            }
            matrizModificadores.consultaRecomendacao(idAventureiro, aventureiros, atributos, itens, metricas, pesos, m, n);

        }
    }
}