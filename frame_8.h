//Código desenvolvido por Andressa Sousa Fonseca

#ifndef FRAME_8_H
#define FRAME_8_H

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

}Led_config8;

typedef Led_config8 RGB_cod8;

// Definição de tipo da matriz de leds
typedef Led_config8 Matriz_leds_config8[5][5];

//função para definição da intensidade de cores do led
uint32_t matrixrgb8(double b, double r, double g)

{
  unsigned char R, G, B;
  R = r * 255;
  G = g * 255;
  B = b * 255;
  return (G << 24) | (R << 16) | (B << 8);
}

void printer_anchor(Matriz_leds_config8 configuracao, PIO pio, uint sm){
    for (int contadorLinha = 4; contadorLinha >= 0; contadorLinha--){
        if(contadorLinha % 2){
            for (int contadorColuna = 0; contadorColuna < 5; contadorColuna ++){
                uint32_t valor_cor_binario = matrixrgb8(
                    configuracao[contadorLinha][contadorColuna].blue,
                    configuracao[contadorLinha][contadorColuna].red,
                    configuracao[contadorLinha][contadorColuna].green
                );

                pio_sm_put_blocking(pio, sm, valor_cor_binario);
            }
        }else{
            for (int contadorColuna = 4; contadorColuna >= 0; contadorColuna --){
                uint32_t valor_cor_binario = matrixrgb8(
                    configuracao[contadorLinha][contadorColuna].blue,
                    configuracao[contadorLinha][contadorColuna].red,
                    configuracao[contadorLinha][contadorColuna].green
                );

                pio_sm_put_blocking(pio, sm, valor_cor_binario);
            }
        }
    }
}

RGB_cod8 cor_parametro8 (double red, double green, double blue){
    RGB_cod8 cor_customizada = {red/255.0,green/255.0,blue/255.0};

    return cor_customizada;
}

void frame_ancora(PIO pio, uint sm, float intsty){

    //Definição de cores usadas na intensidade adequada para o simulador
    
    RGB_cod8 verde;
    RGB_cod8 verde_claro;

    if (intsty != 1) {
        //Definição de cores usadas na intensidade adequada para a placa
        verde = cor_parametro8(0,7,0);
        verde_claro = cor_parametro8(0.0,2,0);
    } else {
        verde = cor_parametro8(0.0,510,0.0);
        verde_claro = cor_parametro8(0,100,0);
    };
    

    
    //Matriz com todos os frames da animação em ordem - Animação é uma árvore subindo e intensificando de cor
    Matriz_leds_config8 frames[] ={
        //1
        { {{0.0, 0.0, 0.0}, verde, verde, verde, {0.0, 0.0, 0.0}},{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}},
        //2
        { {verde, {0.0, 0.0, 0.0}, verde,{0.0, 0.0, 0.0}, verde}, {{0.0, 0.0, 0.0}, verde, verde, verde, {0.0, 0.0, 0.0}},{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}},
        //3
        { {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},verde, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {verde, {0.0, 0.0, 0.0}, verde,{0.0, 0.0, 0.0}, verde}, {{0.0, 0.0, 0.0}, verde, verde, verde, {0.0, 0.0, 0.0}},{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}},
        //4
        {{{0.0, 0.0, 0.0}, verde, verde, verde, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},verde, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {verde, {0.0, 0.0, 0.0}, verde,{0.0, 0.0, 0.0}, verde}, {{0.0, 0.0, 0.0}, verde, verde, verde, {0.0, 0.0, 0.0}},{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}} },
        //5
        {{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, verde, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, verde, verde, verde, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},verde, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {verde, {0.0, 0.0, 0.0}, verde,{0.0, 0.0, 0.0}, verde}, {{0.0, 0.0, 0.0}, verde, verde, verde, {0.0, 0.0, 0.0}}},
        //6
        {{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, verde, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, verde, verde, verde, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},verde_claro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {verde, {0.0, 0.0, 0.0}, verde,{0.0, 0.0, 0.0}, verde}, {{0.0, 0.0, 0.0}, verde, verde_claro, verde, {0.0, 0.0, 0.0}}}, 
        //7
        {{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, verde, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, verde_claro, verde, verde_claro, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},verde_claro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {verde, {0.0, 0.0, 0.0}, verde,{0.0, 0.0, 0.0}, verde}, {{0.0, 0.0, 0.0}, verde, verde_claro, verde, {0.0, 0.0, 0.0}}},
        //8
        {{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, verde, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, verde_claro, verde_claro, verde_claro, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},verde_claro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {verde, {0.0, 0.0, 0.0}, verde,{0.0, 0.0, 0.0}, verde}, {{0.0, 0.0, 0.0}, verde, verde_claro, verde, {0.0, 0.0, 0.0}}},
        //9
        {{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, verde, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, verde_claro, verde_claro, verde_claro, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},verde_claro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {verde, {0.0, 0.0, 0.0}, verde_claro,{0.0, 0.0, 0.0}, verde}, {{0.0, 0.0, 0.0}, verde, verde_claro, verde, {0.0, 0.0, 0.0}}},
        //10
        {{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, verde, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, verde_claro, verde_claro, verde_claro, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},verde_claro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {verde, {0.0, 0.0, 0.0}, verde_claro,{0.0, 0.0, 0.0}, verde}, {{0.0, 0.0, 0.0}, verde_claro, verde_claro, verde_claro, {0.0, 0.0, 0.0}}},
        //11
        {{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, verde, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, verde_claro, verde_claro, verde_claro, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},verde_claro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {verde_claro, {0.0, 0.0, 0.0}, verde_claro,{0.0, 0.0, 0.0}, verde_claro}, {{0.0, 0.0, 0.0}, verde_claro, verde_claro, verde_claro, {0.0, 0.0, 0.0}}},
        //12
        {{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, verde_claro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, verde_claro, verde_claro, verde_claro, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},verde_claro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {verde_claro, {0.0, 0.0, 0.0}, verde_claro,{0.0, 0.0, 0.0}, verde_claro}, {{0.0, 0.0, 0.0}, verde_claro, verde_claro, verde_claro, {0.0, 0.0, 0.0}}},       
    };
    

    //For para apresentar todos os 12 frames em ordem com intervalo de 100ms (10fps)
    for(int i=0;i<12;i++){
            //imprimir os frames 
            printer_anchor(frames[i],pio,sm);
            sleep_ms(100);
    };

};

#endif
