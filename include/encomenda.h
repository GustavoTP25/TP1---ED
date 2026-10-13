#ifndef ENCOMENDA_H
#define ENCOMENDA_H

#include <string>

class Encomenda {
    private:
        int idAventureiro;
        int idItem;

    public:
        Encomenda();
        int getIdAventureiro();
        int getIdItem();
        void setIdAventureiro(int idAventureiro);
        void setIdItem(int idItem);
};

#endif