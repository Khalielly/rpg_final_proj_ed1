/* 
utils.cpp
Implementacao das funcoes utilitarias
*/ 

#include "hpp/utils.hpp"
#include <iostream>
#include <random>
#include <ctime>

using namespace std;

// Mersenne Twister - gerador aleatorio de qualidade
static mt19937 geradorRNG;
static bool rngInicializado = false;


//gerador de numeros aleatorios (RNG)
void inicializarRNG() {
    if (!rngInicializado) {
        geradorRNG.seed(time(nullptr));//usa o tempo atual como referencia
        rngInicializado = true;
    }
}

int rolarDado(int tipoDado) {
    if (!rngInicializado) {
        inicializarRNG();//garante que RNG esta inicializado
    }
    
    if (tipoDado < 4) {
        tipoDado = 4;//dado deve ter pelo menos 4 lados
    }
    
    uniform_int_distribution<int> distribuicao(1, tipoDado);//distribuicao uniforme entre 1 e tipoDado
    
    return distribuicao(geradorRNG);
}


//funcoes de iniciativa
void rolarIniciativaPersonagem(Personagem* p) {
    if (p == nullptr) {
        return;
    }
    
    int resultadoDado = rolarDado(p->dadoBase);//rola o dado do personagem
    
    p->iniciativaAtual = calcularIniciativa(resultadoDado, p->modificador);//calcula iniciativa final
}

int calcularIniciativa(int resultadoDado, int modificador) {
    int resultado = resultadoDado + modificador;
    
    if (resultado < 1) {
        resultado = 1;//iniciativa minima eh 1
    }
    
    return resultado;
}

void rolarIniciativaTodos(Lista* lista) {
    if (lista == nullptr || lista->estaVazia()) {
        return;
    }
    
    No* atual = lista->getInicio();
    
    while (atual != nullptr) {
        rolarIniciativaPersonagem(&(atual->dados));
        atual = atual->proximo;
    }
}

//valida e corrige nivel min e max
int validarNivel(int nivel) {
    if (nivel < 1) {
        return 1;
    }

    if (nivel > 20) {
        return 20;
    }
    return nivel;
}