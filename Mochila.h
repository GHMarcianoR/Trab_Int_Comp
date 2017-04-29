//
// Created by zumbi on 28/04/17.
//

#ifndef TRAB_INT_COMP_MOCHILA_H
#define TRAB_INT_COMP_MOCHILA_H


#include <vector>
#include "Item.h"
class Mochila {

    int capacidade;
    std::vector<Item*> vecItem;
    int pesoAtual;
    int beneficioAtual;

public:
    Mochila(int c);
    void adicionarItem(Item* i);

    int retornarCapacidade();
    int retornarQtdCorrenteItens();
    int retornarPesoAtual();
    int retornarBeneficioAtual();






};


#endif //TRAB_INT_COMP_MOCHILA_H
