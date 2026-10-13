#ifndef ATRIBUTO_H
#define ATRIBUTO_H

#include <string>

class Atributo {
    private:
        int id;
        std::string nome;

    public:
        Atributo();
        int getId();
        std::string getNome();
        void setId(int id);
        void setNome(std::string nome);
};

#endif