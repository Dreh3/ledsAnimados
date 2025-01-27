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

void controlar_leds(PIO pio, uint sm, uint32_t cor)
{
  for (int16_t i = 0; i < NUM_PIXELS; i++) {
    pio_sm_put_blocking(pio, sm, cor);
  }
}

void imprimir_desenho(Matriz_leds_config8 configuracao, PIO pio, uint sm){
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
    RGB_cod8 marromClaro;
    RGB_cod8 marrom;
    RGB_cod8 verde_claro;

    if (intsty == 0.05){
        //Definição de cores usadas na intensidade adequada para a placa
        verde = cor_parametro8(0,7,0);
        marromClaro = cor_parametro8(9.375,4.6875,0);
        marrom = cor_parametro8(4.6875,2.34375,0);
        verde_claro = cor_parametro8(0.0,2,0);
    }elseif (intsty == 1){
        verde = cor_parametro8(0.0,510,0.0);
        marromClaro = cor_parametro8(126,76,0);
        marrom = cor_parametro8(150,75,0);
        verde_claro = cor_parametro8(0,100,0);
    };
    

    
    //Matriz com todos os frames da animação em ordem - Animação é uma árvore subindo e intensificando de cor
    Matriz_leds_config8 frames[] ={
        //1
        { {{0.0, 0.0, 0.0}, marrom, marrom, marrom, {0.0, 0.0, 0.0}},{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}},
        //2
        { {marrom, {0.0, 0.0, 0.0}, marrom,{0.0, 0.0, 0.0}, marrom}, {{0.0, 0.0, 0.0}, marrom, marrom, marrom, {0.0, 0.0, 0.0}},{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}},
        //3
        { {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},marrom, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {marrom, {0.0, 0.0, 0.0}, marrom,{0.0, 0.0, 0.0}, marrom}, {{0.0, 0.0, 0.0}, marrom, marrom, marrom, {0.0, 0.0, 0.0}},{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}},
        //4
        {{{0.0, 0.0, 0.0}, marrom, marrom, marrom, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},marrom, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {marrom, {0.0, 0.0, 0.0}, marrom,{0.0, 0.0, 0.0}, marrom}, {{0.0, 0.0, 0.0}, marrom, marrom, marrom, {0.0, 0.0, 0.0}},{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}} },
        //5
        {{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marrom, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, marrom, marrom, marrom, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},marrom, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {marrom, {0.0, 0.0, 0.0}, marrom,{0.0, 0.0, 0.0}, marrom}, {{0.0, 0.0, 0.0}, marrom, marrom, marrom, {0.0, 0.0, 0.0}}},
        //6
        {{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marrom, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, marrom, marrom, marrom, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},marromClaro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {marrom, {0.0, 0.0, 0.0}, marrom,{0.0, 0.0, 0.0}, marrom}, {{0.0, 0.0, 0.0}, marrom, marromClaro, marrom, {0.0, 0.0, 0.0}}}, 
        //7
        {{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marrom, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, marromClaro, marrom, marromClaro, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},marromClaro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {marrom, {0.0, 0.0, 0.0}, marrom,{0.0, 0.0, 0.0}, marrom}, {{0.0, 0.0, 0.0}, marrom, marromClaro, marrom, {0.0, 0.0, 0.0}}},
        //8
        {{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marrom, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, marromClaro, marromClaro, marromClaro, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},marromClaro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {marrom, {0.0, 0.0, 0.0}, marrom,{0.0, 0.0, 0.0}, marrom}, {{0.0, 0.0, 0.0}, marrom, marromClaro, marrom, {0.0, 0.0, 0.0}}},
        //9
        {{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marrom, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, marromClaro, marromClaro, marromClaro, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},marromClaro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {marrom, {0.0, 0.0, 0.0}, marromClaro,{0.0, 0.0, 0.0}, marrom}, {{0.0, 0.0, 0.0}, marrom, marromClaro, marrom, {0.0, 0.0, 0.0}}},
        //10
        {{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marrom, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, marromClaro, marromClaro, marromClaro, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},marromClaro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {marrom, {0.0, 0.0, 0.0}, marromClaro,{0.0, 0.0, 0.0}, marrom}, {{0.0, 0.0, 0.0}, marromClaro, marromClaro, marromClaro, {0.0, 0.0, 0.0}}},
        //11
        {{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marrom, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, marromClaro, marromClaro, marromClaro, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},marromClaro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {marromClaro, {0.0, 0.0, 0.0}, marromClaro,{0.0, 0.0, 0.0}, marromClaro}, {{0.0, 0.0, 0.0}, marromClaro, marromClaro, marromClaro, {0.0, 0.0, 0.0}}},
        //12
        {{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marromClaro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, marromClaro, marromClaro, marromClaro, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},marromClaro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {marromClaro, {0.0, 0.0, 0.0}, marromClaro,{0.0, 0.0, 0.0}, marromClaro}, {{0.0, 0.0, 0.0}, marromClaro, marromClaro, marromClaro, {0.0, 0.0, 0.0}}},       
    };
    

    //For para apresentar todos os 12 frames em ordem com intervalo de 100ms (10fps)
    for(int i=0;i<12;i++){
            //imprimir os frames 
            imprimir_desenho(frames[i],pio,sm);
            sleep_ms(100);
    };

};

#endif
