#ifndef MATRIZ_MODO_L_H
#define MATRIZ_MODO_L_H


class CelulaMatriz {
    private:
        int idItem, idAtributo, valor;
        CelulaMatriz* vizinhoLinha;
        CelulaMatriz* vizinhoColuna;

    public:
        CelulaMatriz();
    friend class a;
};

class MatrizModoL {
    private:
        // dois ponteiros que apontam para os vetores cabeças
        // quando um item/atributo é adicionado os vetores são apagados, e novos são criados
        // com tamanhos diferentes mas com a informação mantida.
        // cada cabeça é uma lista encadeada
        CelulaMatriz* vetorCabecasLinha;
        CelulaMatriz* vetorCabecasColuna;
        void Limpa();

    public:
        MatrizModoL();
        void modificarValor(int idItem, int idAtributo, int valor);
        ~MatrizModoL();
};

#endif