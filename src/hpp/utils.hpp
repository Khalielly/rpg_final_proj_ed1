/*
utils.hpp
Funcoes utilitarias: RNG e iniciativa
*/

#ifndef UTILS_HPP
#define UTILS_HPP

#include "lista.hpp"
#include <string>


void inicializarRNG();

int rolarDado(int tipoDado);

int calcularIniciativa(int resultadoDado, int nivel);

void rolarIniciativaPersonagem(Personagem* p);

void rolarIniciativaTodos(Lista* lista);

int validarNivel(int nivel);

#endif
