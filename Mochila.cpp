//
// Created by zumbi on 28/04/17.
//

#include "Mochila.h"

Mochila::Mochila(int c) {capacidade = c; pesoAtual = 0; beneficioAtual = 0;}
void Mochila::adicionarItem(Item *i)
{
    vecItem.push_back(i);
    pesoAtual += i->retornarPeso();
    beneficioAtual +=i->retornarValor();

}
int Mochila::retornarCapacidade() {return capacidade;}
int Mochila::retornarQtdCorrenteItens() {vecItem.size();}
int Mochila::retornarPesoAtual() {return pesoAtual;}
int Mochila::retornarBeneficioAtual(){return beneficioAtual;}
