cmake_minimum_required(VERSION 3.7)
project(Trab_Int_Comp)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Item.cpp Item.h Mochila.cpp Mochila.h Cidade.cpp Cidade.h Carteiro.cpp Carteiro.h Metodo.cpp Metodo.h)
add_executable(Trab_Int_Comp ${SOURCE_FILES} Item.cpp Item.h Item.cpp Item.h Mochila.cpp Mochila.h Carteiro.cpp Carteiro.h Metodo.cpp Metodo.h)