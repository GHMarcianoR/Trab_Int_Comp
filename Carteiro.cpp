//
// Created by zumbi on 28/04/17.
//

#include "Carteiro.h"

Carteiro::Carteiro(int t,float vMax,float vMin)
{
    mochila = new Mochila(t);
    this->vMax = vMax;
    this->vMin = vMin;
}
Carteiro::~Carteiro() {delete mochila;}

void Carteiro::adicionarItem(Item *i) {mochila->adicionarItem(i);}

void Carteiro::defineCidadeAtual(Cidade *c) {
    cidadeAtual = c;
    calculaVelocidade();
    adicionarCidadeRota(c);
}
void Carteiro::calculaVelocidade()
{
    velocidade = vMax - mochila->retornarPesoAtual()*(vMax - vMin)/mochila->retornarCapacidade();
}
Cidade* Carteiro::retornaCidadeAtual() {return cidadeAtual;}
bool Carteiro::contemNaRota(Cidade *c)
{
    if(!rota.empty())
        if(std::find(rota.begin(), rota.end(),c) != rota.end())
            return true;
    return false;

}
int Carteiro::retornarTamanhoMochila() {return mochila->retornarCapacidade();}
int Carteiro::retornarQuantidadeItensMochila() {return mochila->retornarQtdCorrenteItens();}
int Carteiro::retornarPesoAtualMochila() {return mochila->retornarPesoAtual();}
float Carteiro::retornaVelocidadeAtual() {return velocidade;}
int Carteiro::retornarCapacidadeMochila() {return mochila->retornarCapacidade();}
void Carteiro::adicionarCidadeRota(Cidade *c) {rota.push_back(c);}
std::vector<Cidade*> Carteiro::retornaRota() {return rota;}