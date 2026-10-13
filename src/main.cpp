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
            itens.adicionarItem(nome);

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
            encomendas.forjarItens(aventureiros, itens, turnos);

        } else if (comando == "M"){
            int idItem, idAtributo, valor;
            ss >> idItem >> idAtributo >> valor;
            matrizModificadores.setValor(idItem, idAtributo, valor);
        }
    }
}