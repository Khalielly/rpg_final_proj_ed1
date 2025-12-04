/*
personagem.hpp
Definicao da estrutura personagem
*/

#ifndef PERSONAGEM_HPP
#define PERSONAGEM_HPP

#include <string>

using namespace std;

struct Personagem {
    int id;                 //Identificador unico
    string nome;            //Nome do personagem
    int nivel;              //Nivel (1-20)
    int dadoBase;           //Tipo de dado (ex: 20 para d20)
    int iniciativaAtual;    //Resultado da rolagem + modificador
    bool isPlayer;          //true = jogador, false = NPC
};

#endif