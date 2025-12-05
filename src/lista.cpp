/*
lista.cpp
Implementacao da lista duplamente encadeada
*/

#include "hpp/lista.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm> 

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
        if(inicio != nullptr) inicio->anterior = nullptr;
    }
    else if (alvo == fim) {
        fim = alvo->anterior;
        if(fim != nullptr) fim->proximo = nullptr;
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

//ordenacao
void Lista::atualizarPrtrs() {
    if(estaVazia()) {
        inicio = nullptr;
        fim = nullptr;
        return;
    }

    inicio->anterior = nullptr;

    No* atual = inicio;
    while (atual->proximo != nullptr){
        atual = atual->proximo;
    }

    fim = atual;
    fim->proximo = nullptr;
    
}

void Lista::ordenarQS(){
    if(estaVazia() || tamanho == 1) {
        return;
    }

    quickSort(inicio, fim);
    atualizarPrtrs();
}

void Lista::ordenarMerge(){
    if(estaVazia() || tamanho == 1) {
        return;
    }

    inicio = mergeSort(inicio);
    atualizarPrtrs();
}

// Funcoes auxiliares para QuickSort
No* Lista::particao(No* low, No* high) { 
    Personagem pivot = high->dados;
    No* i = low->anterior;

    for (No* j = low; j != high; j = j->proximo) {
        if (j->dados.iniciativaAtual >= pivot.iniciativaAtual) {
            i = (i == nullptr) ? low : i->proximo;
            std::swap(i->dados, j->dados); // Usando std::swap
        }
    }
    i = (i == nullptr) ? low : i->proximo;
    
    std::swap(i->dados, high->dados); // Usando std::swap

    return i;
}

void Lista::quickSort(No* low, No* high) { 
    if (high != nullptr && low != high && low != high->proximo) {
        No* p = particao(low, high);
        quickSort(low, p->anterior);
        quickSort(p->proximo, high);
    }
}

// Funcoes auxiliares para MergeSort
No* Lista::split(No* head) { 
    No* fast = head;
    No* slow = head;

    while (fast->proximo && fast->proximo->proximo) {
        fast = fast->proximo;
        slow = slow->proximo;
    }

    No* temp = slow->proximo;
    slow->proximo = nullptr;
    if (temp) temp->anterior = nullptr;
    return temp;
}

No* Lista::merge(No* primeiro, No* segundo) { 
    if (!primeiro) return segundo;
    if (!segundo) return primeiro;

    No* resultado = nullptr;
    
    // Critério de ordenação: maior iniciativaAtual primeiro (>=)
    if (primeiro->dados.iniciativaAtual >= segundo->dados.iniciativaAtual) {
        resultado = primeiro;
        resultado->proximo = merge(primeiro->proximo, segundo);
        if (resultado->proximo) resultado->proximo->anterior = resultado;
        resultado->anterior = nullptr;
        return primeiro;
    } else {
        resultado = segundo;
        resultado->proximo = merge(primeiro, segundo->proximo);
        if (resultado->proximo) resultado->proximo->anterior = resultado;
        segundo->anterior = nullptr;
        return segundo;
    }
}

No* Lista::mergeSort(No* topo) { 
    if (!topo || !topo->proximo) return topo;
    No* segundo = split(topo);
    topo = mergeSort(topo);
    segundo = mergeSort(segundo);
    return merge(topo, segundo);
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