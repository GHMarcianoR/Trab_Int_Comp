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

void Cidade::adicionarItemCidade(Item *i) {
    vecItensCidade.push_back(i);
    vecItensCidade2.push_back(i);

}
int Cidade::retornarId() {return idCidade;}
float Cidade::retornarX(){return coordX;}
float Cidade::retornarY() {return coordY;}
int Cidade::retornarQtdCidades() {return qtdCidades;}
void Cidade::ordenarDistCidade()
{
     auxDisOrd.reserve(qtdCidades);
   for(int i = 0; i< qtdCidades; i++)
       auxDisOrd.push_back(vecDist[i]);
    std::sort(auxDisOrd.begin(), auxDisOrd.begin() + qtdCidades,ordena_esse_diabo);
}
int Cidade::retornarCidadeSorteada(float alfa)
{
    long int t = (int) (auxDisOrd.size() * alfa);
    int r;
     if(t != 0)
        r = (int)(rand() % t);
     else
         r = 0;

    std::list<float> auxaux;
    auxaux.assign(auxDisOrd.begin(),auxDisOrd.end());
    float valSorteado = auxDisOrd[r];
    auxaux.remove(valSorteado);
    auxDisOrd.assign(auxaux.begin(),auxaux.end());

    for(int i = 0; i< qtdCidades; i++)
        if(vecDist[i] == valSorteado)
            return i;

}

Item* Cidade::retornarItemSorteado(float alfa)
{
    int p = (int)(vecItensCidade.size() * alfa);
    int r = 0;
    if(p !=0)
        r = (rand() % p);

    std::list<Item*> auxaux;
    auxaux.assign(vecItensCidade.begin(),vecItensCidade.end());
    Item* valSorteado = vecItensCidade[r];
    auxaux.remove(valSorteado);
    vecItensCidade.assign(auxaux.begin(),auxaux.end());

    return valSorteado;

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
    return a->retornarValor() > a1->retornarValor();
}

std::vector<Item*>  Cidade::retornaVecItens() {return vecItensCidade;}
std::vector<Item*> Cidade::retornaVecItens2(){return vecItensCidade2;}