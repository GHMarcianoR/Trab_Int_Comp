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
int Metodo::aceOfspades(Cidade *cidadeAtual, float alpha)
{
    int ind, totalRetornadas, adicionadas = 0, indSorteado;
    float valSorteado;

    std::vector<float> vetCustos;
    std::list<float> indice;
    indice.clear();
    vetCustos.clear();

    alpha == 0 ? totalRetornadas =1 :
            totalRetornadas = (int)(cidadeAtual->retornarQtdCidades() * alpha);

    while(totalRetornadas != adicionadas)
    {
        ind = cidadeAtual->retornarCidadeSorteada(alpha);
        indice.push_back(calculaCusto(cidadeAtual,ind));
        indice.push_back(ind);
        vetCustos.push_back(calculaCusto(cidadeAtual,ind));
        adicionadas++;
    }
    std::sort(vetCustos.begin(),vetCustos.end());
    indSorteado = (rand() % totalRetornadas);
    valSorteado = vetCustos[indSorteado];
    for(std::list<float>::iterator it = indice.begin(); it != indice.end(); ++it)
        if(*it == valSorteado)
        {
            ++it;
            return (int)(*it);
        }


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
        ind = aceOfspades(cidade,alpha);
        if(!carteiro->contemNaRota(vecCidades[ind]) && carteiro->retornaRota().size() < cidade->retornarQtdCidades()+1)
        {
            custo +=calculaCusto(cidade, ind);

            cidade = vecCidades[ind];
            cidade->ordenaItens();

            qtdA =(int) cidade->retornaVecItens().size();
            /*Pegando todos os itens que tem na cidade*/

            qtd = 0;
            while(qtd < qtdA && carteiro->retornarPesoAtualMochila() <carteiro->retornarCapacidadeMochila())
            {
               //  Item *i = cidade->retornarItemSorteado(alpha);
                Item* i = cidade->retornaVecItens()[qtd];
                carteiro->adicionarItem(i);
                qtd++;
            }

            carteiro->defineCidadeAtual(cidade);
        }


    }while(cidade != cidadeInicial && vecCidades[ind] != cidadeInicial);


    beneficio += carteiro->retornarBeneficioAtual();

    std::cout<<"\nCusto " <<custo
             <<"\nBeneficio "<<beneficio<<std::endl;
    std::cout<<"Valor Lucro "<<beneficio - custo<<std::endl;
    std::cout<<"Capacidade maxima mochila: "<<carteiro->retornarCapacidadeMochila()
             <<"\nPeso Atual "<<carteiro->retornarPesoAtualMochila()<<std::endl;
    for(int i = 0; i<carteiro->retornaRota().size(); i++)
        std::cout<<carteiro->retornaRota()[i]->retornarId()<<" ";
    std::cout<<"\nTamanho Rota: "<<carteiro->retornaRota().size()<<std::endl;

    lucroTotal = beneficio-custo;
    buscaLocal(carteiro->retornaRota());

}
void Metodo::buscaLocal(std::vector<Cidade*> rota)
{
    std::vector<Cidade*> rotaAux= rota;

        for(unsigned long i = 1; i<rota.size() -1; i++)
        {
            for(unsigned long j = 1;j != rota.size()-1; j++)
            {
                 if(j!=i )
                    {
                        Cidade* cI = rota[i];
                        Cidade* cJ = rota[j];
                        rotaAux.at(i) = cJ;
                        rotaAux.at(j) = cI;

                        float novoLucro = reCalculaLucro(rotaAux);
                        if(novoLucro > lucroTotal)
                        {
                            rota = rotaAux;
                            lucroTotal = novoLucro;
                            std::cout<<"Lucro Aumentou:"<<lucroTotal<<std::endl;
                            for(int l = 0; l < rota.size(); l++)
                                std::cout<<rota[l]->retornarId()<<" ";
                            std::cout<<"\n";


                        }
                        else
                        {
                            /* std::cout<<"Lucro Diminuiu:"<<novoLucro<<std::endl;*/
                            rotaAux =rota;
                        }
                        /* for(int i = 0; i<rota.size(); i++)
                             std::cout<<rota[i]->retornarId()<<" ";
                         std::cout<<"\nTamanho Rota: "<<rota.size()<<std::endl;*/
                    }




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

float Metodo::reCalculaLucro(std::vector<Cidade*> rota)
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
                if (peso + rota[i]->retornaVecItens()[qtdA]->retornarPeso() <= tamMochila)
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
        float velocidadeAtual  =(vMax - (peso*(vMax - vMin))/tamMochila);

        vecCusto.push_back(custo - auxCusto);
        custo += R * rota[i]->distanciaAte(procuraCidade(rota[i+1]->retornarId()))/velocidadeAtual;
    }
    for(int i = 0; i<vecBeneficio.size(); i++)
    {
        auxDiff.push_back((vecBeneficio[i]-vecCusto[i]));
       // std::cout<<auxDiff[i]<<" ";
    }

    lucro= beneneficio - custo;
    return lucro;


}
void Metodo::definirR(float R) {this->R = R;}
void Metodo::definirAlpha(float a) {alpha = a;}
float Metodo::distancia(float x1, float x2, float y1, float y2){
    return (float) sqrt(pow(x1-x2,2)+ pow(y1-y2,2));
}
