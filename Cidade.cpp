//
// Created by zumbi on 28/04/17.
//

#include <iostream>
#include "Cidade.h"

static bool  ordena_esse_diabo(float a, float a1);
static bool ordena_esse_diabo2(Item* a, Item *a1);

Cidade::Cidade(float x, float y, int qtdCidades, int id)
{
    coordX = x;
    coordY = y;
    this->qtdCidades = qtdCidades;
    vecDist.reserve(qtdCidades);
    for(int i = 0; i<qtdCidades; i++)
        vecDist[i] = 0;
    idCidade = id;
}

void Cidade::definirDistancia(int indiceCidade, float dist)
{
    vecDist[indiceCidade] = dist;
}

void Cidade::adicionarItemCidade(Item *i) {vecItensCidade.push_back(i);}
int Cidade::retornarId() {return idCidade;}
float Cidade::retornarX(){return coordX;}
float Cidade::retornarY() {return coordY;}
int Cidade::retornarQtdCidades() {return qtdCidades;}
void Cidade::ordenarDistCidade()
{
     auxDisOrd.reserve(qtdCidades);
   for(int i = 0; i< qtdCidades; i++)
       auxDisOrd[i] = vecDist[i];
    std::sort(auxDisOrd.begin(), auxDisOrd.begin() + qtdCidades,ordena_esse_diabo);
}
int Cidade::retornarCidadeSorteada(float alfa, std::vector<Cidade*> c)
{
    for(int i = 0; i<c.size(); i++)
    {
        for(int j = 0; j<auxDisOrd.size(); j++)
        if(c[i]->retornarId() == auxDisOrd[j])
            auxDisOrd[j] = 0;
    }

    int r = (rand() % (int)(qtdCidades* alfa) );

    while(auxDisOrd[r] == 0)
        r = (rand() % (int)(qtdCidades* alfa) );

    for(int i = 0; i< qtdCidades; i++)
        if(vecDist[i] == auxDisOrd[r])
            return i;

}

Item* Cidade::retornarItemSorteado(float alfa)
{
    int p = (int)(vecItensCidade.size() * alfa);
    int r = (rand() % p);
    return vecItensCidade[r];

}

float Cidade::distanciaAte(int ind) {
    return vecDist[ind];
}
void Cidade::ordenaItens()
{
    std::sort(vecItensCidade.begin(), vecItensCidade.begin()+vecItensCidade.size(), ordena_esse_diabo2);

}
static bool  ordena_esse_diabo(float a, float a1) {
    return a < a1;
}
static bool ordena_esse_diabo2(Item* a, Item *a1)
{
    return a->retornarDif() > a1->retornarDif();
}

std::vector<Item*>  Cidade::retornaVecItens() {return vecItensCidade;}
