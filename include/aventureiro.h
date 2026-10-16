#ifndef AVENTUREIRO_H
#define AVENTUREIRO_H

#include <string>
#include "build_aventureiro.h"
#include "fila_itens.h"
#include "fila_atributos.h"

class Aventureiro {
    private:
        int id;
        std::string nome;
        BuildAventureiro build;

    public:
        Aventureiro();
        int getId();
        std::string getNome();
        void listarBuild(MatrizModificadores &matrizModificadores, FilaAtributos &atributos);
        void setId(int id);
        void setNome(std::string nome);
    friend class FilaAventureiros;
    friend class MatrizModificadores;

};

#endif