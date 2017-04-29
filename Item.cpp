//
// Created by zumbi on 28/04/17.
//

#include "Item.h"

Item::Item(float p,float v, int id) {

    peso = p;
    valor = v;
    id_item = id;
    dif = valor - peso;
}
Item::~Item() {}
float Item::retornarPeso() {return peso;}
float Item::retornarValor() {return valor;}
int Item::retornarId() {return id_item;}

