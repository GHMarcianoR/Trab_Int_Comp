//
// Created by zumbi on 28/04/17.
//

#include <iostream>
#include "Metodo.h"


Metodo::Metodo(std::vector<Cidade*> v, int tamMochila, float vMax, float vMin)
{
    vecCidades = v;
    trato = 0;
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
    custo = 0;

}

float Metodo::calculaCusto(Cidade *c2, int ind) {

    float dist = c2->distanciaAte(ind);
    return R *(dist)/carteiro->retornaVelocidadeAtual();
}
void Metodo::Construtivo()
{
    Cidade* cidadeInicial = carteiro->retornaCidadeAtual(),
            *cidade;
    int ind,qtdA , qtd;

    float beneficioTotal = 0;

    do
    {
        qtd = 0;
        cidade = carteiro->retornaCidadeAtual();
        ind = cidade->retornarCidadeSorteada(alpha);
       while(carteiro->contemNaRota(vecCidades[ind]) && carteiro->retornaRota().size() < cidade->retornarQtdCidades())
            ind = cidade->retornarCidadeSorteada(alpha);

        custo +=calculaCusto(cidade, ind);
        cidade = vecCidades[ind];
        cidade->ordenaItens();

       qtdA =(int) cidade->retornaVecItens().size();
        /*Pegando todos os itens que tem na cidade*/

        while(qtd != qtdA && carteiro->retornarPesoAtualMochila() <carteiro->retornarCapacidadeMochila())
        {
            Item *i = cidade->retornarItemSorteado(alpha);
            carteiro->adicionarItem(i);
            qtd++;
        }
        carteiro->defineCidadeAtual(cidade);

    }while(cidade != cidadeInicial);
    for(int i = 0; i <carteiro->retornaRota().size(); i++)
        std::cout<<carteiro->retornaRota()[i]->retornarId()<<" ";

      beneficioTotal += carteiro->retornarBeneficioAtual();

    std::cout<<"\nCusto " <<custo
             <<"\nBeneficio "<<beneficioTotal<<std::endl;
    std::cout<<"Valor Lucro "<<beneficioTotal - custo<<std::endl;
    std::cout<<"Capacidade maxima mochila: "<<carteiro->retornarCapacidadeMochila()
             <<"\nPeso Atual "<<carteiro->retornarPesoAtualMochila()<<std::endl;

}
void Metodo::definirR(float R) {this->R = R;}
void Metodo::definirAlpha(float a) {alpha = a;}

float Metodo::distancia(float x1, float x2, float y1, float y2)
{
    return (float) sqrt(pow(x1-x2,2)+ pow(y1-y2,2));
}
