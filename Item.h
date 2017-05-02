//
// Created by zumbi on 28/04/17.
//

#ifndef TRAB_INT_COMP_ITEM_H
#define TRAB_INT_COMP_ITEM_H


class Item {
    float peso;
    float valor;
    int id_item;

    float dif;

public:
    Item(float p,float v,int id);
    ~Item();


    float retornarPeso();
    float retornarValor();
    int retornarId();

   float retornarDif(){return dif;}


};


#endif //TRAB_INT_COMP_ITEM_H
