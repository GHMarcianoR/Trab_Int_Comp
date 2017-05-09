//
// Created by zumbi on 28/04/17.
//

#ifndef TRAB_INT_COMP_CIDADE_H
#define TRAB_INT_COMP_CIDADE_H


#include <vector>
#include <list>
#include <algorithm>
#include "Item.h"

class Cidade {
    std::vector<float> vecDist;
    std::vector<float> auxDisOrd;
    float coordX, coordY;
    int qtdCidades;
    int idCidade;
    std::vector<Item*> vecItensCidade;
    std::vector<Item*> vecItensCidade2;




public:
    Cidade(float x, float y, int qtdCidades, int id);

    void definirDistancia(int indiceCidade, float dist);
    void adicionarItemCidade(Item *i);
    void ordenarDistCidade();
    void remove(int ind);

    int retornarCidadeSorteada(float alfa);
    Item* retornarItemSorteado(float alfa);

    void ordenaItens();

    float distanciaAte(int ind);
    float retornarX();
    float retornarY();
    int retornarId();
    int   retornarQtdCidades();
    std::vector<Item*> retornaVecItens();
    std::vector<Item*> retornaVecItens2();
   // static bool  ordena_esse_diabo(float a, float a1);



};


#endif //TRAB_INT_COMP_CIDADE_H
