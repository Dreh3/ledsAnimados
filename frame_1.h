//Código desenvolvido por Andressa Sousa Fonseca

#ifndef FRAME_1_H
#define FRAME_1_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"

#define NUM_PIXELS 25

// Definição de tipo da estrutura que irá controlar a cor dos LED's
typedef struct {
    double red;
    double green;
    double blue;

}Led_config1;

typedef Led_config1 RGB_cod1;

// Definição de tipo da matriz de leds
typedef Led_config1 Matriz_leds_config1[5][5];

//função para definição da intensidade de cores do led
uint32_t matrixrgb1(double b, double r, double g)

{
  unsigned char R, G, B;
  R = r * 255;
  G = g * 255;
  B = b * 255;
  return (G << 24) | (R << 16) | (B << 8);
}

void imprimir_desenho(Matriz_leds_config1 configuracao, PIO pio, uint sm){
    for (int contadorLinha = 4; contadorLinha >= 0; contadorLinha--){
        if(contadorLinha % 2){
            for (int contadorColuna = 0; contadorColuna < 5; contadorColuna ++){
                uint32_t valor_cor_binario = matrixrgb1(
                    configuracao[contadorLinha][contadorColuna].blue,
                    configuracao[contadorLinha][contadorColuna].red,
                    configuracao[contadorLinha][contadorColuna].green
                );

                pio_sm_put_blocking(pio, sm, valor_cor_binario);
            }
        }else{
            for (int contadorColuna = 4; contadorColuna >= 0; contadorColuna --){
                uint32_t valor_cor_binario = matrixrgb1(
                    configuracao[contadorLinha][contadorColuna].blue,
                    configuracao[contadorLinha][contadorColuna].red,
                    configuracao[contadorLinha][contadorColuna].green
                );

                pio_sm_put_blocking(pio, sm, valor_cor_binario);
            }
        }
    }
}

RGB_cod1 cor_parametro (double red, double green, double blue){
    RGB_cod1 cor_customizada = {red/255.0,green/255.0,blue/255.0};

    return cor_customizada;
}

void frame_arvore(PIO pio, uint sm, float intsty){

    //Definição de cores usadas na intensidade adequada para o simulador
    
    RGB_cod1 verde = cor_parametro(0.0,510,0.0);
    RGB_cod1 marromClaro = cor_parametro(126,76,0);
    RGB_cod1 marrom = cor_parametro(150,75,0);
    RGB_cod1 verde_claro = cor_parametro(0,100,0);

    if (intsty != 1){
        //Definição de cores usadas na intensidade adequada para a placa
        verde = cor_parametro(0,7,0);
        marromClaro = cor_parametro(9.375,4.6875,0);
        marrom = cor_parametro(4.6875,2.34375,0);
        verde_claro = cor_parametro(0.0,2,0);
    };
    

    
    //Matriz com todos os frames da animação em ordem - Animação é uma árvore subindo e intensificando de cor
    Matriz_leds_config1 frames[] ={
        //frame 0 arvore subindo linha 1
        {{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, verde_claro, verde_claro, verde_claro, {0.0, 0.0, 0.0}} },
        //frame 1 arvore subindo linha 2
        {{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, verde_claro, verde_claro, verde_claro, {0.0, 0.0, 0.0}}, {verde_claro, verde_claro, verde_claro, verde_claro, verde_claro}},
        //frame 2 arvore subindo linha 3
        {{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, verde_claro, verde_claro, verde_claro, {0.0, 0.0, 0.0}}, {verde_claro, verde_claro, verde_claro, verde_claro, verde_claro}, {verde_claro, verde_claro, verde_claro, verde_claro, verde_claro}},
        //frame 3 arvore subindo linhas 4
        {{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, verde_claro, verde_claro, verde_claro, {0.0, 0.0, 0.0}}, {verde_claro, verde_claro, verde_claro, verde_claro, verde_claro}, {verde_claro, verde_claro, verde_claro, verde_claro, verde_claro}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marromClaro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}},
        //frame 4 arvore completa
        {{{0.0, 0.0, 0.0}, verde_claro, verde_claro, verde_claro, {0.0, 0.0, 0.0}}, {verde_claro, verde_claro, verde_claro, verde_claro, verde_claro},{verde_claro, verde_claro, verde_claro, verde_claro, verde_claro}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marromClaro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marromClaro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}},
        //frame 5 arvore completa novo frame mudando cor de ramos da arvore 
        {{{0.0, 0.0, 0.0}, verde, verde_claro, verde_claro, {0.0, 0.0, 0.0}}, {verde_claro, verde_claro, verde_claro, verde_claro, verde_claro},{verde_claro, verde_claro, verde_claro, verde, verde_claro}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marromClaro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marromClaro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}},
        //frame 6 arvore completa novo frame mudando cor de ramos da arvore 
        {{{0.0, 0.0, 0.0}, verde, verde_claro, verde_claro, {0.0, 0.0, 0.0}}, {verde_claro, verde_claro, verde, verde_claro, verde_claro},{verde_claro, verde, verde_claro, verde, verde_claro}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marrom, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marromClaro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}},
        //frame 6 arvore completa novo frame mudando cor de ramos da arvore 
        {{{0.0, 0.0, 0.0}, verde, verde_claro, verde, {0.0, 0.0, 0.0}}, {verde, verde_claro, verde, verde_claro, verde},{verde_claro, verde, verde_claro, verde, verde_claro}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marrom, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marromClaro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}},
        //frame 7
        {{{0.0, 0.0, 0.0}, verde, verde_claro, verde, {0.0, 0.0, 0.0}}, {verde, verde_claro, verde, verde_claro, verde},{verde_claro, verde, verde, verde, verde_claro}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marrom, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marromClaro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}},
        //frame 8
        {{{0.0, 0.0, 0.0}, verde, verde, verde, {0.0, 0.0, 0.0}}, {verde, verde_claro, verde, verde_claro, verde},{verde_claro, verde, verde, verde, verde_claro}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marrom, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marromClaro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}},
        //frame 9
        {{{0.0, 0.0, 0.0}, verde, verde, verde, {0.0, 0.0, 0.0}}, {verde, verde, verde, verde, verde},{verde_claro, verde, verde, verde, verde_claro}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marrom, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marromClaro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}},
        //frame 10
        {{{0.0, 0.0, 0.0}, verde, verde, verde, {0.0, 0.0, 0.0}}, {verde, verde, verde, verde, verde},{verde, verde, verde, verde, verde}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marrom, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marromClaro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}},
        //frame 11
        {{{0.0, 0.0, 0.0}, verde, verde, verde, {0.0, 0.0, 0.0}}, {verde, verde, verde, verde, verde},{verde, verde, verde, verde, verde}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marrom, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marrom, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}}    
    };
    

    //For para apresentar todos os 12 frames em ordem com intervalo de 250ms (4fps)
    for(int i=0;i<12;i++){
            //imprimir os frames 
            imprimir_desenho(frames[i],pio,sm);
            sleep_ms(100);
    };

};

#endif
