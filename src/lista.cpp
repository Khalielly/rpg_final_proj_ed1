/*
lista.cpp
Implementacao da lista duplamente encadeada
*/

#include "hpp/lista.hpp"
#include <iostream>
#include <iomanip>

using namespace std;


//construtor
Lista::Lista() {
    inicio = nullptr;
    fim = nullptr;
    tamanho = 0;
}

//destrutor
Lista::~Lista() {
    No* atual = inicio;
    while (atual != nullptr) {
        No* proximo = atual->proximo;
        delete atual;
        atual = proximo;
    }
    inicio = nullptr;
    fim = nullptr;
    tamanho = 0;
}

//getters
int Lista::getTamanho() {
    return tamanho;
}

bool Lista::estaVazia() {
    return tamanho == 0;
}

No* Lista::getInicio() {
    return inicio;
}

No* Lista::getFim() {
    return fim;
}

//operacoes
void Lista::inInicio(Personagem p) {
    No* novoNo = new No;
    novoNo->dados = p;
    novoNo->anterior = nullptr;
    novoNo->proximo = nullptr;
    
    if (estaVazia()) {
        inicio = novoNo;
        fim = novoNo;
    }

    else {
        novoNo->proximo = inicio;
        inicio->anterior = novoNo;
        inicio = novoNo;
    }
    
    tamanho++;
}

void Lista::inFim(Personagem p) {
    No* novoNo = new No;
    novoNo->dados = p;
    novoNo->anterior = nullptr;
    novoNo->proximo = nullptr;
    
    if (estaVazia()) {
        inicio = novoNo;
        fim = novoNo;
    }

    else {
        novoNo->anterior = fim;
        fim->proximo = novoNo;
        fim = novoNo;
    }
    
    tamanho++;
}


bool Lista::remover(int id) {
    No* alvo = buscar(id);
    
    if (alvo == nullptr) {
        return false;
    }
    
    if (tamanho == 1) {
        inicio = nullptr;
        fim = nullptr;
    }
    else if (alvo == inicio) {
        inicio = alvo->proximo;
        inicio->anterior = nullptr;
    }
    else if (alvo == fim) {
        fim = alvo->anterior;
        fim->proximo = nullptr;
    }
    else {
        alvo->anterior->proximo = alvo->proximo;
        alvo->proximo->anterior = alvo->anterior;
    }
    
    delete alvo;
    tamanho--;
    
    return true;
}

No* Lista::buscar(int id) {
    No* atual = inicio;
    
    while (atual != nullptr) {
        if (atual->dados.id == id) {
            return atual;//encontrou
        }
        atual = atual->proximo;
    }
    
    return nullptr;//nao encontrou
}


//exibicao
void Lista::exibir() {
    if (estaVazia()) {
        cout << "Lista vazia!" << endl;
        return;
    }
    
    cout << endl;
    cout << "+-------------------------------------------------+" << endl;
    cout << "| ID     | Nome              | Nv | Inic | Tipo   |" << endl;
    cout << "+-------------------------------------------------+" << endl;
    
    No* atual = inicio;
    while (atual != nullptr) {
        Personagem p = atual->dados;
        cout << "| " << setw(6) << left << p.id << " | ";
        cout << setw(15) << left << p.nome.substr(0, 15) << right << " | ";
        cout << setw(2) << p.nivel << " | ";
        cout << setw(4) << p.iniciativaAtual << " | ";
        cout << setw(6) << (p.isPlayer ? "Player" : "NPC") << " |" << endl;
        atual = atual->proximo;
    }
    
    cout << "+-------------------------------------------------+" << endl;
    cout << "Total: " << tamanho << " personagem(ns)" << endl;
}

void Lista::exibirOrdemCombate() {
    if (estaVazia()) {
        cout << "Nenhum personagem no combate!" << endl;
        return;
    }
    
    cout << endl;
    cout << "========== ORDEM DE COMBATE ==========" << endl;
    
    No* atual = inicio;
    int posicao = 1;
    while (atual != nullptr) {
        Personagem p = atual->dados;
        cout << " " << posicao << "o. ";
        cout << p.nome;
        cout << " [Iniciativa: " << p.iniciativaAtual << "]";
        if (posicao == 1) {
            cout << " <-- TURNO ATUAL";
        }
        cout << endl;
        
        atual = atual->proximo;
        posicao++;
    }
    
    cout << "======================================" << endl;
}