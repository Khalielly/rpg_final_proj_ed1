/*
lista.hpp
Definicao da lista duplamente encadeada
*/

#ifndef LISTA_HPP
#define LISTA_HPP

#include "personagem.hpp"

struct No {
    Personagem dados;
    No* anterior;
    No* proximo;
};


class Lista {
private:
    No* inicio;
    No* fim;
    int tamanho;
    
    void atualizarPrtrs();

public:
    //construtor e destrutor
    Lista();
    ~Lista();

    //operacoes basicas
    void inFim(Personagem p);
    void inInicio(Personagem p);
    bool remover(int id);
    No* buscar(int id);
    
    //exibicao
    void exibir();
    void exibirOrdemCombate();
    
    //getters
    int getTamanho();
    bool estaVazia();
    No* getInicio();
    No* getFim();

    //ordenacao
    void ordenarQS();
    void ordenarMerge();
};

#endif