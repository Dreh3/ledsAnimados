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
}Led_config;

typedef Led_config RGB_cod;

// Definição de tipo da matriz de leds
typedef Led_config Matriz_leds_config[5][5];

//função para definição da intensidade de cores do led
uint32_t matrix_rgb(double b, double r, double g)
{
  unsigned char R, G, B;
  R = r * 255;
  G = g * 255;
  B = b * 255;
  return (G << 24) | (R << 16) | (B << 8);
}

void imprimir_desenho(Matriz_leds_config configuracao, PIO pio, uint sm){
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

RGB_cod obter_cor_por_parametro_RGB(int red, int green, int blue){
    RGB_cod cor_customizada = {red/255.0,green/255.0,blue/255.0};

    return cor_customizada;
}

void animacaoletraA(PIO pio, uint sm){

    //Definição de cores usadas na intensidade adeuquada para a placa

        /*
        RGB_cod cinza = obter_cor_por_parametro_RGB(5.25,5.25,5.25);
        RGB_cod branco = obter_cor_por_parametro_RGB(6.2,6.2,6.375);
        RGB_cod verde_opaco = obter_cor_por_parametro_RGB(0,5,0);
        RGB_cod marrom = obter_cor_por_parametro_RGB(9.375,4.6875,0);
        RGB_cod marrom_claro = obter_cor_por_parametro_RGB(4.6875,2.34375,0);
        RGB_cod azul_claro = obter_cor_por_parametro_RGB(0.0,0.0,2);
        RGB_cod azul_int = obter_cor_por_parametro_RGB(0.0,0.0,0.1);
        RGB_cod red_int = obter_cor_por_parametro_RGB(0.0,0.0,0.1);
        RGB_cod green_int = obter_cor_por_parametro_RGB(0.0,0.0,0.1);
        */

    //Definição de cores usadas na intensidade adequada para o simulador
    RGB_cod cinza = obter_cor_por_parametro_RGB(128,128,128);
    RGB_cod branco = obter_cor_por_parametro_RGB(255,255,255);
    RGB_cod verde_opaco = obter_cor_por_parametro_RGB(0,100,0); //antes 5
    RGB_cod marrom = obter_cor_por_parametro_RGB(150,75,0);
    RGB_cod marrom_claro = obter_cor_por_parametro_RGB(63,38,0);
    RGB_cod azul_claro = obter_cor_por_parametro_RGB(18,10,143);
    RGB_cod azul_int = obter_cor_por_parametro_RGB(0.0,0.0,255);
    RGB_cod red_int = obter_cor_por_parametro_RGB(255,0.0,0);
    RGB_cod green_int = obter_cor_por_parametro_RGB(0.0,255,0.0);


    //Matriz com todos os frames da animação em ordem
    Matriz_leds_config frames[] ={
        //frame 0 leds dispersos modelo A
        {{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, red_int, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, green_int, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, red_int, red_int, green_int, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, azul_int, azul_int, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}},
        //frame 1 leds dispersos modelo B
        {{green_int, green_int, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, azul_int, {0.0, 0.0, 0.0}, red_int}, {red_int, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, azul_int, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, azul_int, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, green_int}, {green_int, {0.0, 0.0, 0.0}, green_int, {0.0, 0.0, 0.0}, azul_int}},
        //frame 2 letra A
        {{{0.0, 0.0, 0.0}, red_int, red_int, red_int, {0.0, 0.0, 0.0}},{red_int, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, red_int}, {red_int, red_int, red_int, red_int, red_int}, {red_int, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, red_int}, {red_int, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, red_int}},
        //frame 3 arvore subindo linha 1
        {{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, green_int, green_int, green_int, {0.0, 0.0, 0.0}} },
        //frame 4 arvore subindo linha 2
        {{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, green_int, green_int, green_int, {0.0, 0.0, 0.0}}, {green_int, green_int, green_int, green_int, green_int}},
        //frame 5 arvore subindo linha 3
        {{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, green_int, green_int, green_int, {0.0, 0.0, 0.0}}, {green_int, green_int, green_int, green_int, green_int}, {green_int, green_int, green_int, green_int, green_int}},
        //frame 6 arvore subindo linhas 4
        {{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, green_int, green_int, green_int, {0.0, 0.0, 0.0}}, {green_int, green_int, green_int, green_int, green_int}, {green_int, green_int, green_int, green_int, green_int}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marrom, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}},
        //frame 7 arvore completa
        {{{0.0, 0.0, 0.0}, green_int, green_int, green_int, {0.0, 0.0, 0.0}}, {green_int, green_int, green_int, green_int, green_int},{green_int, green_int, green_int, green_int, green_int}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marrom, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marrom, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}},
        //frame 8 arvore completa novo frame mudando cor de ramos da arvore 
        {{{0.0, 0.0, 0.0}, verde_opaco, green_int, verde_opaco, {0.0, 0.0, 0.0}}, {green_int, green_int, green_int, green_int, green_int},{green_int, verde_opaco, green_int, verde_opaco, green_int}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marrom, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marrom, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}},
        //frame 9 arvore completa novo frame mudando cor de ramos da arvore 
        {{{0.0, 0.0, 0.0}, verde_opaco, green_int, verde_opaco, {0.0, 0.0, 0.0}}, {verde_opaco, green_int, verde_opaco, green_int, verde_opaco},{green_int, verde_opaco, green_int, verde_opaco, green_int}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marrom_claro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marrom, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}},
        //frame 10 arvore completa novo frame mudando cor de ramos da arvore 
        {{{0.0, 0.0, 0.0}, verde_opaco, verde_opaco, verde_opaco, {0.0, 0.0, 0.0}}, {verde_opaco, verde_opaco, verde_opaco, verde_opaco, verde_opaco},{verde_opaco, verde_opaco, verde_opaco, verde_opaco, verde_opaco}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marrom_claro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, marrom_claro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}},
        //frame 11 arvore deslizando pela esquerda coluna 1
        {{verde_opaco, verde_opaco, verde_opaco, {0.0, 0.0, 0.0}, azul_claro}, {verde_opaco, verde_opaco, verde_opaco, verde_opaco, azul_claro},{verde_opaco, verde_opaco, verde_opaco, verde_opaco, azul_claro}, {{0.0, 0.0, 0.0}, marrom_claro,{0.0, 0.0, 0.0},  {0.0, 0.0, 0.0}, azul_claro}, {{0.0, 0.0, 0.0}, marrom_claro,{0.0, 0.0, 0.0},  {0.0, 0.0, 0.0}, azul_claro}},
        //frame 12 arvore deslizando pela esquerda coluna 2
        {{verde_opaco, verde_opaco, {0.0, 0.0, 0.0}, azul_claro, azul_claro}, {verde_opaco, verde_opaco, verde_opaco, azul_claro, azul_claro},{verde_opaco, verde_opaco, verde_opaco, azul_claro, azul_claro}, {marrom_claro,{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},  azul_claro, azul_claro}, {marrom_claro,{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},  azul_claro, azul_claro}},
        //frame 13 arvore deslizando pela esquerda coluna 3
        {{verde_opaco, {0.0, 0.0, 0.0}, azul_claro, azul_claro, azul_claro}, {verde_opaco, verde_opaco, azul_claro, azul_claro, azul_claro},{verde_opaco, verde_opaco, azul_claro, azul_claro, azul_claro}, {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}, azul_claro, azul_claro, azul_claro}, {{0.0, 0.0, 0.0},{0.0, 0.0, 0.0}, azul_claro, azul_claro, azul_claro}},
        //frame 14 arvore deslizando pela esquerda coluna 4
        {{{0.0, 0.0, 0.0}, azul_claro, azul_claro, azul_claro, azul_claro}, {verde_opaco, azul_claro, azul_claro, azul_claro, azul_claro},{green_int, azul_claro, azul_claro, azul_claro, azul_claro}, {{0.0, 0.0, 0.0},azul_claro, azul_claro, azul_claro, azul_claro}, {{0.0, 0.0, 0.0},azul_claro, azul_claro, azul_claro, azul_claro}},
        //frame 15 fundo azul
        {{azul_claro, azul_claro, azul_claro, azul_claro, azul_claro}, {azul_claro, azul_claro, azul_claro, azul_claro, azul_claro},{azul_claro, azul_claro, azul_claro, azul_claro, azul_claro}, {azul_claro, azul_claro, azul_claro, azul_claro, azul_claro}, {azul_claro, azul_claro, azul_claro, azul_claro, azul_claro}},
        //frame 16 ancora descendo
        {{azul_claro, cinza, cinza, cinza, azul_claro},{azul_claro, azul_claro, azul_claro, azul_claro, azul_claro}, {azul_claro, azul_claro, azul_claro, azul_claro, azul_claro}, {azul_claro, azul_claro, azul_claro, azul_claro, azul_claro},{azul_claro, azul_claro, azul_claro, azul_claro, azul_claro}},
        //frame 17 ancora descendo
        {{cinza, azul_claro, cinza,azul_claro, cinza}, {azul_claro, cinza, cinza, cinza, azul_claro},{azul_claro, azul_claro, azul_claro, azul_claro, azul_claro}, {azul_claro, azul_claro, azul_claro, azul_claro, azul_claro},{azul_claro, azul_claro, azul_claro, azul_claro, azul_claro}},
        //frame 18 ancora descendo
        {{azul_claro, azul_claro, cinza, azul_claro, azul_claro},{cinza, azul_claro, cinza,azul_claro, cinza}, {azul_claro, cinza, cinza, cinza, azul_claro},{azul_claro, azul_claro, azul_claro, azul_claro, azul_claro}, {azul_claro, azul_claro, azul_claro, azul_claro, azul_claro}},
        //frame 19 ancora descendo
        {{azul_claro, cinza, cinza, cinza, azul_claro}, {azul_claro, azul_claro, cinza, azul_claro, azul_claro}, {cinza, azul_claro, cinza,azul_claro, cinza}, {azul_claro, cinza, cinza, cinza, azul_claro},{azul_claro, azul_claro, azul_claro, azul_claro, azul_claro}},
        //frame 20 ancora completa
        {{azul_claro, azul_claro, cinza, azul_claro, azul_claro}, {azul_claro, cinza, cinza, cinza, azul_claro}, {azul_claro, azul_claro, cinza, azul_claro, azul_claro}, {cinza, azul_claro, cinza,azul_claro, cinza}, {azul_claro, cinza, cinza, cinza, azul_claro}},
        //frame 21 invertendo cores ancora 
        {{{0.0, 0.0, 0.0}, azul_claro, cinza, azul_claro, {0.0, 0.0, 0.0}}, {azul_claro, cinza, cinza, cinza, azul_claro}, {{0.0, 0.0, 0.0}, azul_claro, azul_claro, azul_claro, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, azul_claro, cinza,azul_claro, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, cinza, azul_claro, cinza, {0.0, 0.0, 0.0}}},
        //frame 22 invertendo cores ancora 
        {{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, azul_claro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, azul_claro , cinza, azul_claro, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, azul_claro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {azul_claro, cinza, cinza,cinza, azul_claro}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, azul_claro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}},
        //frame 23 invertendo cores ancora 
        {{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, azul_claro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, azul_claro , azul_claro, azul_claro, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, azul_claro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {azul_claro, {0.0, 0.0, 0.0}, azul_claro,{0.0, 0.0, 0.0}, azul_claro}, {{0.0, 0.0, 0.0}, azul_claro, azul_claro, azul_claro, {0.0, 0.0, 0.0}}},
        //frame 24 ancora descendo
        {{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, azul_claro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, azul_claro , azul_claro, azul_claro, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, azul_claro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {azul_claro, {0.0, 0.0, 0.0}, azul_claro,{0.0, 0.0, 0.0}, azul_claro}},
        //frame 25 ancora descendo
        {{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, azul_claro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, azul_claro ,azul_claro, azul_claro, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, azul_claro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}},
        //frame 26 ancora descendo
        {{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, azul_claro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, azul_claro , azul_claro, azul_claro, {0.0, 0.0, 0.0}}},
        //frame 27 ancora descendo
        {{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, azul_claro, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}},
        //frame 28 ampulheta surgindo
        {{marrom,marrom, {0.0,0.0,0.0}, marrom, marrom}, {{0.0,0.0,0.0}, {0.0,0.0,0.0}, {0.0,0.0,0.0}, {0.0,0.0,0.0}, {0.0,0.0,0.0}},{{0.0,0.0,0.0}, {0.0,0.0,0.0}, {0.0,0.0,0.0}, {0.0,0.0,0.0}, {0.0,0.0,0.0}}, {{0.0,0.0,0.0}, {0.0,0.0,0.0}, {0.0,0.0,0.0}, {0.0,0.0,0.0}, {0.0,0.0,0.0}},{marrom, marrom, {0.0,0.0,0.0}, marrom, marrom}},
        // frame 29 ampulheta surgindo
        {{marrom,marrom, marrom, marrom, marrom}, {{0.0,0.0,0.0}, marrom, {0.0,0.0,0.0}, marrom, {0.0,0.0,0.0}},{{0.0,0.0,0.0}, {0.0,0.0,0.0}, {0.0,0.0,0.0}, {0.0,0.0,0.0}, {0.0,0.0,0.0}}, {{0.0,0.0,0.0}, marrom, {0.0,0.0,0.0}, marrom, {0.0,0.0,0.0}},{marrom, marrom, marrom, marrom, marrom}},
        // frame 30 areia caindo
        {{marrom,marrom, marrom, marrom, marrom}, {{0.0,0.0,0.0}, marrom, branco, marrom, {0.0,0.0,0.0}},{{0.0,0.0,0.0}, {0.0,0.0,0.0}, marrom, {0.0,0.0,0.0}, {0.0,0.0,0.0}}, {{0.0,0.0,0.0}, marrom, branco, marrom, {0.0,0.0,0.0}},{marrom, marrom, marrom, marrom, marrom}},
        //frame 31 areia caindo
        {{marrom,marrom, marrom, marrom, marrom}, {{0.0,0.0,0.0}, marrom, {0.0,0.0,0.0}, marrom, {0.0,0.0,0.0}},{{0.0,0.0,0.0}, {0.0,0.0,0.0}, branco, {0.0,0.0,0.0}, {0.0,0.0,0.0}}, {{0.0,0.0,0.0}, marrom, branco, marrom, {0.0,0.0,0.0}},{marrom, marrom, marrom, marrom, marrom} },
        //frame 32 areia caindo
        {{marrom,marrom, marrom, marrom, marrom}, {{0.0,0.0,0.0}, marrom, {0.0,0.0,0.0}, marrom, {0.0,0.0,0.0}},{{0.0,0.0,0.0}, {0.0,0.0,0.0}, marrom, {0.0,0.0,0.0}, {0.0,0.0,0.0}}, {{0.0,0.0,0.0}, marrom, branco, marrom, {0.0,0.0,0.0}},{marrom, marrom, marrom, marrom, marrom} },
        //frame 33 ampulheta sumindo
        {{marrom,{0.0,0.0,0.0}, {0.0,0.0,0.0}, {0.0,0.0,0.0}, marrom}, {{0.0,0.0,0.0}, marrom, {0.0,0.0,0.0}, marrom, {0.0,0.0,0.0}},{{0.0,0.0,0.0}, {0.0,0.0,0.0}, marrom, {0.0,0.0,0.0}, {0.0,0.0,0.0}}, {{0.0,0.0,0.0}, {0.0,0.0,0.0}, {0.0,0.0,0.0}, {0.0,0.0,0.0}, {0.0,0.0,0.0}},{marrom, marrom, {0.0,0.0,0.0}, marrom, marrom}},
        //frame 34 ampulheta sumindo
        {{marrom,{0.0,0.0,0.0}, {0.0,0.0,0.0}, {0.0,0.0,0.0}, marrom}, {{0.0,0.0,0.0}, marrom, {0.0,0.0,0.0}, marrom, {0.0,0.0,0.0}},{{0.0,0.0,0.0}, {0.0,0.0,0.0}, {0.0,0.0,0.0}, {0.0,0.0,0.0}, {0.0,0.0,0.0}}, {{0.0,0.0,0.0}, {0.0,0.0,0.0}, {0.0,0.0,0.0}, {0.0,0.0,0.0}, {0.0,0.0,0.0}},{marrom, {0.0,0.0,0.0}, {0.0,0.0,0.0}, {0.0,0.0,0.0}, marrom}},
        //frame 35 ampulheta sumindo
        {{marrom,{0.0,0.0,0.0}, {0.0,0.0,0.0}, {0.0,0.0,0.0}, marrom}, {{0.0,0.0,0.0}, {0.0,0.0,0.0}, {0.0,0.0,0.0}, {0.0,0.0,0.0}, {0.0,0.0,0.0}},{{0.0,0.0,0.0}, {0.0,0.0,0.0}, {0.0,0.0,0.0}, {0.0,0.0,0.0}, {0.0,0.0,0.0}}, {{0.0,0.0,0.0}, {0.0,0.0,0.0}, {0.0,0.0,0.0}, {0.0,0.0,0.0}, {0.0,0.0,0.0}},{marrom, {0.0,0.0,0.0}, {0.0,0.0,0.0}, {0.0,0.0,0.0}, marrom}}
    };
    //matriz para limpar leds
    Matriz_leds_config limpar = {
        //  apagar leds
        {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}
    };

    //For para apresentar todos os 35 frames em ordem com intervalo de 250ms (4fps)
    for(int i=0;i<36;i++){
        if(i==2 || i==23){
            for(int j=0;j<2;j++){
                //para fazer a letra A piscar
                imprimir_desenho(frames[i],pio,sm);
                sleep_ms(300);
                imprimir_desenho(limpar,pio,sm);
                sleep_ms(300);
            }
        }if(i==35){
            //para apagar todos os leds depois que a ampulheta some
            imprimir_desenho(frames[i],pio,sm);
            sleep_ms(300);
            imprimir_desenho(limpar,pio,sm);
            sleep_ms(300);
        }else{
            //imprimir os frames 
            imprimir_desenho(frames[i],pio,sm);
            sleep_ms(400);
        }
    }

};




#endif