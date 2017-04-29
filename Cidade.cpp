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
int Cidade::retornarCidadeSorteada(float alfa)
{
    int p = (int)(vecDist.size() * alfa);
    p = 4;
    int r = (rand() % p);
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
  //  for(int i = 0;i<vecItensCidade.size(); i++)
    //    std::cout<<vecItensCidade[i]->retornarDif()<<"\n";

  
}
static bool  ordena_esse_diabo(float a, float a1) {
    return a > a1;
}
static bool ordena_esse_diabo2(Item* a, Item *a1)
{
    return a->retornarDif() > a1->retornarDif();
}

std::vector<Item*>  Cidade::retornaVecItens() {return vecItensCidade;}
