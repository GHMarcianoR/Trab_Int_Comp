#include <iostream>
#include <fstream>
#include <string>
#include<ctime>
#include <algorithm>
#include "Cidade.h"
#include "Metodo.h"

int main()
{
    std::ifstream arquivo;
    std::string nome;
    nome = "eil51_n500_bounded-strongly-corr_09.ttp";
    arquivo.open(nome, std::ios::in);
    int numCidades;
    int numItens;
    int capacidadeMochila;
    float veloMax, veloMin;
    float taxaAluguel;
    int cont = 0;
    int x,y,id;
    int beneficio, peso, localizacao;
    srand (time(NULL));

    std::string linha;
    std::vector<Cidade*> vecCidades;


    if(!arquivo.good())
    {
        std::cout<<"Erro ao ler o arquivo"<<std::endl;
        exit(1);
    }
    std::cout<<"Arquivo Aberto com sucesso"<<std::endl;
    getline(arquivo, linha);
    getline(arquivo, linha);

    arquivo>>linha; arquivo >>numCidades;
    arquivo>>linha; arquivo>>linha; arquivo>>linha; arquivo >>numItens;
    arquivo>>linha; arquivo>>linha; arquivo>>linha; arquivo >>capacidadeMochila;
    arquivo>>linha; arquivo>>linha; arquivo >>veloMin;
    arquivo>>linha; arquivo>>linha; arquivo >>veloMax;
    arquivo>>linha; arquivo>>linha; arquivo >>taxaAluguel;

    while(!arquivo.eof())
    {

        getline(arquivo,linha);
        if(linha.find("NODE_COORD_SECTION") != std::string::npos)
        {
           while(cont < numCidades)
           {
               arquivo>>id;
               arquivo>>x;
               arquivo>>y;
               Cidade * c = new Cidade(x,y,numCidades,id);
               vecCidades.push_back(c);
               cont++;

           }

        }
        else if(linha.find("ITEMS SECTION") != std::string::npos)
        {
           cont = 0;
            while(cont < numItens)
            {
                arquivo >>id;
                arquivo>>beneficio;
                arquivo>>peso;
                arquivo>>localizacao;

                Item* item = new Item(peso,beneficio,id);

               for(int i = 0; i<vecCidades.size(); i++)
                   if (vecCidades[i]->retornarId() == localizacao)
                           vecCidades[i]->adicionarItemCidade(item);

                cont++;

            }

        }



    }

    Metodo* metodo = new Metodo(vecCidades,capacidadeMochila,veloMax, veloMin);
    metodo->definirR(taxaAluguel);
    metodo->definirAlpha(0.3);
    metodo->Construtivo();


    return 0;
}