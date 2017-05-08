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
    this->tamMochila = tamMochila;
    carteiro = new Carteiro(tamMochila, vMax, vMin);
    this->vMax =vMax;
    this->vMin = vMin;

    carteiro->defineCidadeAtual(vecCidades[0]);
    custo = 0;
    beneficio = 0;

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
    std::vector<float> vecBeneficio, prejuizo;
    float auxCusto=0, auxBeneficio =0;

    do
    {

        cidade = carteiro->retornaCidadeAtual();
        ind = cidade->retornarCidadeSorteada(alpha);
       vecBeneficio.push_back(carteiro->retornarBeneficioAtual() - auxBeneficio);
       while(carteiro->contemNaRota(vecCidades[ind]) && carteiro->retornaRota().size() < cidade->retornarQtdCidades())
            ind = cidade->retornarCidadeSorteada(alpha);

        custo +=calculaCusto(cidade, ind);
        prejuizo.push_back(custo-auxCusto);
        auxCusto = custo;
        auxBeneficio = carteiro->retornarBeneficioAtual();

        cidade = vecCidades[ind];
        cidade->ordenaItens();

       qtdA =(int) cidade->retornaVecItens().size();
        /*Pegando todos os itens que tem na cidade*/

        qtd = 0;
        while(qtd < qtdA && carteiro->retornarPesoAtualMochila() <carteiro->retornarCapacidadeMochila())
        {
           // Item *i = cidade->retornarItemSorteado(alpha);
            Item* i = cidade->retornaVecItens()[qtd];
            carteiro->adicionarItem(i);
            qtd++;
        }

        carteiro->defineCidadeAtual(cidade);


    }while(cidade != cidadeInicial);

    std::cout<<"Itens: "<<std::endl;
    std::cout<<std::endl;
    std::vector<float> diff, diffOrdenado;
    for(int i = 0; i<vecBeneficio.size(); i++)
    {
        diff.push_back(prejuizo[i]-vecBeneficio[i]);
        diffOrdenado.push_back(prejuizo[i]-vecBeneficio[i]);

    }
    std::sort(diffOrdenado.begin(), diffOrdenado.begin()+diffOrdenado.size());

    beneficio += carteiro->retornarBeneficioAtual();

    std::cout<<"\nCusto " <<custo
             <<"\nBeneficio "<<beneficio<<std::endl;
    std::cout<<"Valor Lucro "<<beneficio - custo<<std::endl;
    std::cout<<"Capacidade maxima mochila: "<<carteiro->retornarCapacidadeMochila()
             <<"\nPeso Atual "<<carteiro->retornarPesoAtualMochila()<<std::endl;

 /*   for(int i = 0; i< carteiro->retornaRota().size(); i++)
        std::cout<<carteiro->retornaRota()[i]->retornarId()<<" ";
    std::cout<<std::endl;*/

    buscaLocal(carteiro->retornaRota(),diff,diffOrdenado,(beneficio-custo));

}
void Metodo::buscaLocal(std::vector<Cidade*> rota,std::vector<float> diff, std::vector<float> diffOrdenado,float lucro )
{
    float ultimo  = diffOrdenado[diffOrdenado.size()-1], lucroR;
    std::vector<Cidade*> auxRota = rota;
    int ind = procura(ultimo,diff);
    Cidade * c = rota[ind];

    for(int j = 0; j<rota.size();j++)
       for(int i = 1; i<auxRota.size()-1; i++ )
        {
            Cidade * aux = auxRota[i+1];
            auxRota[i] = auxRota[i];
            auxRota[ind] = aux;
            lucroR = reCalculaLucro(auxRota, diff);
            if(lucroR >= lucro)
            {
                std::cout<<"\nFUNCIONOU SAPORRA DIABO FDP"<<std::endl;
                std::cout<<"Lucro: "<<lucroR<<std::endl;
                rota = auxRota;
                ind = procura(ultimo,diff);
                lucro = lucroR;
            }
            else
            {
                std::cout<<"Lucro: "<<lucroR<<"\n";
                auxRota = rota;
            }


        }

}


int Metodo::procura(float ultimo, std::vector<float> diff)
{

    for(int i = 0; i< diff.size(); i++)
        if(diff[i] == ultimo)
            return i;

}
int Metodo::procuraCidade(int id)
{

    for(int i = 0; i< vecCidades.size(); i++)
        if(vecCidades[i]->retornarId() == id)
            return i;

}

float Metodo::reCalculaLucro(std::vector<Cidade*> rota, std::vector<float> diff)
{
    float custo = 0;
    int peso = 0;
    int qtdA = 0;
    int beneneficio = 0;

    float lucro, auxBeneficio = 0, auxCusto = 0 ;
    std::vector<float> vecBeneficio, vecCusto, auxDiff;

    for(int i = 0; i<rota.size()-1; i++) {

        float  beneficioAtual = 0;

        while(qtdA != rota[i]->retornaVecItens().size())
        {
                if (peso +  rota[i]->retornaVecItens()[qtdA]->retornarPeso() <= tamMochila)
                {
                    peso += rota[i]->retornaVecItens()[qtdA]->retornarPeso();
                    beneneficio += rota[i]->retornaVecItens()[qtdA]->retornarValor();
                    beneficioAtual +=rota[i]->retornaVecItens()[qtdA]->retornarValor();
                }

            qtdA++;
        }qtdA = 0;
        vecBeneficio.push_back(beneficioAtual- auxBeneficio );
        auxBeneficio = beneficioAtual;
        auxCusto = custo;
        float veloCidadeAtual  =(vMax - (peso*(vMax - vMin))/tamMochila);

        vecCusto.push_back(custo - auxCusto);
        custo += R * rota[i]->distanciaAte(procuraCidade(rota[i+1]->retornarId()))/veloCidadeAtual;
    }
    for(int i = 0; i<vecBeneficio.size(); i++)
    {
        auxDiff.push_back((vecBeneficio[i]-vecCusto[i]));
       // std::cout<<auxDiff[i]<<" ";
    }

    diff  = auxDiff;
    std::cout<<"\n";
    std::sort(diff.begin(), diff.end());

    lucro= beneneficio - custo;
    return lucro;


}
void Metodo::definirR(float R) {this->R = R;}
void Metodo::definirAlpha(float a) {alpha = a;}
float Metodo::distancia(float x1, float x2, float y1, float y2){
    return (float) sqrt(pow(x1-x2,2)+ pow(y1-y2,2));
}
