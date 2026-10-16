#ifndef FILA_SINERGIA_H
#define FILA_SINERGIA_H

class CelulaSinergia {
    private:
        int idItem;
        double valor;
        CelulaSinergia* proximo;
    public:
        CelulaSinergia();
    friend class FilaSinergia;
};  

class FilaSinergia {
    private:
        CelulaSinergia* frente;
        int tamanho;
        void Limpa();
    
    public:
        FilaSinergia();
        void setValor(int idItem, double valor);
        void acumulaPontos(long long* pontos, long long pesoCent, int N);
        ~FilaSinergia();
    friend class MatrizModificadores;
};

#endif