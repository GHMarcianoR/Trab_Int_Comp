//
// Created by zumbi on 28/04/17.
//

#ifndef TRAB_INT_COMP_CARTEIRO_H
#define TRAB_INT_COMP_CARTEIRO_H


#include "Mochila.h"
#include "Cidade.h"

class Carteiro {

    Mochila* mochila;
    Cidade* cidadeAtual;
    float velocidade;
    float vMax, vMin;
    std::vector<Cidade*> rota;
    void calculaVelocidade();
    void adicionarCidadeRota(Cidade *c);
    void adicionaItensMochila();

public:
    Carteiro(int t,float vMax,float vMin );
    ~Carteiro();

    void adicionarItem(Item *i);
    void defineCidadeAtual(Cidade *c);

    Cidade* retornaCidadeAtual();
    float retornaVelocidadeAtual();
    int retornarTamanhoMochila();
    int retornarQuantidadeItensMochila();
    bool contemNaRota(Cidade* c);
    int retornarPesoAtualMochila();
    int retornarCapacidadeMochila();
    std::vector<Cidade*> retornaRota();

};


#endif //TRAB_INT_COMP_CARTEIRO_H
