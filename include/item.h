#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
    private:
        int id;
        std::string nome;

    public:
        Item();
        int getId();
        std::string getNome();
        void setId(int id);
        void setNome(std::string nome);
};

#endif