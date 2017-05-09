//
// Created by zumbi on 28/04/17.
//

#ifndef TRAB_INT_COMP_METODO_H
#define TRAB_INT_COMP_METODO_H


#include <vector>
#include <math.h>
#include "Cidade.h"
#include "Carteiro.h"

class Metodo {

    std::vector<Cidade*> vecCidades;

    Carteiro* carteiro;
    float custo;
    float beneficio;
    float lucroTotal;
    float R;
    int tamMochila;
    float vMax, vMin;

    float distancia(float x1, float x2, float y1, float y2);
    float alpha;
    float calculaCusto(Cidade *c2, int ind);
    int aceOfspades(Cidade* cidadeAtual, float alpha);
    float trato;
    float Objetivo();

public:
        Metodo(std::vector<Cidade*> v, int tamMochila, float vMax, float vMin);
        void buscaLocal(std::vector<Cidade*> rota);
        void Construtivo();
        void definirR(float R);
        void definirAlpha(float a);
        int procura(float ultimo, std::vector<float> diff);
        int procuraCidade(int id);
        float reCalculaLucro(std::vector<Cidade*> rota);
        ~Metodo();


};


#endif //TRAB_INT_COMP_METODO_H
