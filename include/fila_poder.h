#ifndef FILA_PODER_H
#define FILA_PODER_H

class CelulaPoder {
    private:
        int idItem;
        double valor;
        CelulaPoder* proximo;
    public:
        CelulaPoder();
    friend class FilaPoder;
};  

class FilaPoder {
    private:
        CelulaPoder* frente;
        int tamanho;
        void Limpa();
    
    public:
        FilaPoder();
        void setValor(int idItem, double valor);
        void acumulaPontos(long long* pontos, long long pesoCent, int N);
        ~FilaPoder();
    friend class MatrizModificadores;
};

#endif