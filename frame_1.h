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
uint32_t matrixRGB(double b, double r, double g)

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
                uint32_t valor_cor_binario = matrix_rgb(
                    configuracao[contadorLinha][contadorColuna].blue,
                    configuracao[contadorLinha][contadorColuna].red,
                    configuracao[contadorLinha][contadorColuna].green
                );

                pio_sm_put_blocking(pio, sm, valor_cor_binario);
            }
        }else{
            for (int contadorColuna = 4; contadorColuna >= 0; contadorColuna --){
                uint32_t valor_cor_binario = matrix_rgb(
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

void animacaoletraA(PIO pio, uint sm){

    //Definição de cores usadas na intensidade adequada para a placa

        /*
        RGB_cod verde = obter_cor_por_parametro_RGB(0,7,0);
        RGB_cod marromClaro = obter_cor_por_parametro_RGB(9.375,4.6875,0);
        RGB_cod marrom = obter_cor_por_parametro_RGB(4.6875,2.34375,0);
        RGB_cod verde_claro = obter_cor_por_parametro_RGB(0.0,2,0);
        */

    //Definição de cores usadas na intensidade adequada para o simulador
    
    RGB_cod verde = obter_cor_por_parametro_RGB(0.0,510,0.0);
    RGB_cod marromClaro = obter_cor_por_parametro_RGB(126,76,0);
    RGB_cod marrom = obter_cor_por_parametro_RGB(150,75,0);
    RGB_cod verde_claro = obter_cor_por_parametro_RGB(0,100,0);
    

    
    //Matriz com todos os frames da animação em ordem
    Matriz_leds_config1 frames[] ={
        //frame 0
        {{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},{verde, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}},
        //frame 1
        {{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},{verde, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marrom, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}},
        //frame 2
        {{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, verde, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},{verde, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, verde}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marrom, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}},
        //frame 3
        {{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, verde, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, verde, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},{verde, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, verde}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marrom, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}},
        //frame 4
        {{{0.0, 0.0, 0.0}, verde, verde, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, verde, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},{verde, {0.0, 0.0, 0.0}, verde, {0.0, 0.0, 0.0}, verde}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marrom, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}},
        //frame 5
        {{{0.0, 0.0, 0.0}, verde, verde, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, verde, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},{verde, {0.0, 0.0, 0.0}, verde, verde, verde}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marrom, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}},
        //frame 6
        {{{0.0, 0.0, 0.0}, verde, verde, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, verde, {0.0, 0.0, 0.0}, verde, {0.0, 0.0, 0.0}},{verde, {0.0, 0.0, 0.0}, verde, verde, verde}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marrom, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}},
        //frame 7
        {{{0.0, 0.0, 0.0}, verde, verde, verde, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, verde, verde, verde, {0.0, 0.0, 0.0}},{verde, {0.0, 0.0, 0.0}, verde, verde, verde}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marrom, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}},
        //frame 8
        {{{0.0, 0.0, 0.0}, verde, verde, verde, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, verde, verde, verde, {0.0, 0.0, 0.0}},{verde, verde, verde, verde, verde}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marrom, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}},
        //frame 9
        {{{0.0, 0.0, 0.0}, verde, verde, verde, {0.0, 0.0, 0.0}}, {verde, verde, verde, verde, {0.0, 0.0, 0.0}},{verde, verde, verde, verde, verde}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marrom, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}},
        //frame 10
        {{{0.0, 0.0, 0.0}, verde, verde, verde, {0.0, 0.0, 0.0}}, {verde, verde, verde, verde, verde},{verde, verde, verde, verde, verde}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marrom, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}},
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
