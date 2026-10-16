#ifndef FILA_EQUILIBRIO_H
#define FILA_EQUILIBRIO_H

class CelulaEquilibrio {
    private:
        int idItem;
        double valor;
        CelulaEquilibrio* proximo;
    public:
        CelulaEquilibrio();
    friend class FilaEquilibrio;
};  


class FilaEquilibrio {
    private:
        CelulaEquilibrio* frente;
        int tamanho;
        void Limpa();
    
    public:
        FilaEquilibrio();
        void setValor(int idItem, double valor);
        void acumulaPontos(long long* pontos, long long pesoCent, int N);
        ~FilaEquilibrio();
    friend class MatrizModificadores;
};

#endif