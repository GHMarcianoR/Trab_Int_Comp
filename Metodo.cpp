//
// Created by zumbi on 28/04/17.
//

#include <iostream>
#include "Metodo.h"


Metodo::Metodo(std::vector<Cidade*> v, int tamMochila, float vMax, float vMin)
{
    vecCidades = v;
    float d;
    for(int i = 0; i< vecCidades.size(); i++)
    {
        for(int j = 0; j< vecCidades.size(); j++)
        {

            if(i != j)
            {
                d = distancia(vecCidades[i]->retornarX(),
                              vecCidades[j]->retornarX(),
                              vecCidades[i]->retornarY(),
                              vecCidades[j]->retornarY());

                vecCidades[i]->definirDistancia(j,d);
            }


        }
        vecCidades[i]->ordenarDistCidade();
    }
    carteiro = new Carteiro(tamMochila, vMax, vMin);
    carteiro->defineCidadeAtual(vecCidades[0]);


}

float Metodo::calculaCusto(Cidade *c2, int ind) {


    return R *(c2->distanciaAte(ind))/carteiro->retornaVelocidadeAtual();

}
void Metodo::Construtivo()
{
    Cidade* cidadeInicial = carteiro->retornaCidadeAtual(),
            *cidade = carteiro->retornaCidadeAtual();
    int ind,qtdA , qtd;
    do
    {
        qtd = 0;
        ind = cidadeInicial->retornarCidadeSorteada(alpha);
        calculaCusto(cidade, ind);
        cidade = vecCidades[ind];
        cidade->ordenaItens();
        qtdA = (int)(rand()%cidade->retornaVecItens().size() );
        while(qtd != qtdA && carteiro->retornarPesoAtualMochila() <carteiro->retornarCapacidadeMochila())
        {
            carteiro->adicionarItem(cidade->retornarItemSorteado(alpha));
            qtd++;
        }
        carteiro->defineCidadeAtual(cidade);

    }while(cidade != cidadeInicial);
    for(int i = 0; i <carteiro->retornaRota().size(); i++)
       std::cout<<carteiro->retornaRota()[i]->retornarId()<<" ";

}
void Metodo::definirR(float R) {this->R = R;}
void Metodo::definirAlpha(float a) {alpha = a;}

float Metodo::distancia(float x1, float x2, float y1, float y2)
{
    return (float) sqrt(pow(x1-x2,2)+ pow(y1-y2,2));
}
