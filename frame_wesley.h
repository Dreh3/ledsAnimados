#ifndef FRAME_wesley_H
#define FRAME_wesley_H

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
}Led_config_5;

typedef Led_config_5 RGB_cod_5;

// Definição de tipo da matriz de leds
typedef Led_config_5 Matriz_leds_config_5[5][5];

//função para definição da intensidade de cores do led
uint32_t matrix_rgb_5(double b, double r, double g)
{
  unsigned char R, G, B;
  R = r * 255;
  G = g * 255;
  B = b * 255;
  return (G << 24) | (R << 16) | (B << 8);
}

//acionar a matrix de leds - ws2812b
void controlar_leds_2(PIO pio, uint sm, uint32_t cor)
{
  for (int16_t i = 0; i < NUM_PIXELS; i++) {
    pio_sm_put_blocking(pio, sm, cor);
  }
}

void imprimir_frame_5(Matriz_leds_config_5 configuracao, PIO pio, uint sm){
    for (int contadorLinha = 4; contadorLinha >= 0; contadorLinha--){
        if(contadorLinha % 2){
            for (int contadorColuna = 0; contadorColuna < 5; contadorColuna ++){
                uint32_t valor_cor_binario = matrix_rgb_5(
                    configuracao[contadorLinha][contadorColuna].blue,
                    configuracao[contadorLinha][contadorColuna].red,
                    configuracao[contadorLinha][contadorColuna].green
                );

                pio_sm_put_blocking(pio, sm, valor_cor_binario);
            }
        }else{
            for (int contadorColuna = 4; contadorColuna >= 0; contadorColuna --){
                uint32_t valor_cor_binario = matrix_rgb_5(
                    configuracao[contadorLinha][contadorColuna].blue,
                    configuracao[contadorLinha][contadorColuna].red,
                    configuracao[contadorLinha][contadorColuna].green
                );

                pio_sm_put_blocking(pio, sm, valor_cor_binario);
            }
        }
    }
}

RGB_cod_5 obter_cor_por_parametro_RGB_7(int red, int green, int blue){
    RGB_cod_5 cor_customizada = {red/255.0,green/255.0,blue/255.0};

    return cor_customizada;
}

void frame_wesley(PIO pio, uint sm, float itnsty) {
    Matriz_leds_config_5 frames[] = {        
        // Sorriso 1
        {
         {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
         {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
         {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
         {{1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
         {{0.5*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}  // Linha 4
        },
        // Sorriso 2
        {
         {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
         {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
         {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
         {{1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
         {{1.0*itnsty, 0.0, 0.0}, {0.5*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}  // Linha 4
        },
        // Sorriso 3
        {
         {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
         {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
         {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
         {{1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
         {{1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {0.5*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}  // Linha 4
        },
         // Sorriso 4
        {
         {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
         {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
         {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
         {{1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
         {{1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {0.5*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}}  // Linha 4
        },
        // Sorriso 5
        {
         {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
         {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
         {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
         {{1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
         {{1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {0.5*itnsty, 0.0, 0.0}}  // Linha 4
        },
        // Sorriso 6
        {
         {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
         {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
         {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
         {{1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.5*itnsty, 0.0, 0.0}}, // Linha 3
         {{1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}}  // Linha 4
        },
        // Sorriso 7
        {
         {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
         {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
         {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
         {{1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}}, // Linha 3
         {{1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}}  // Linha 4
        },
        // Sorriso 8
        {
         {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
         {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
         {{0.0, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
         {{1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}}, // Linha 3
         {{1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}}  // Linha 4
        },
        
        // Sorriso fechado
        {
         {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
         {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
         {{0.0, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
         {{1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}}, // Linha 3
         {{1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}}  // Linha 4
        },

        // Sorriso aberto
        {
         {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
         {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
         {{0.0, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
         {{1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}}, // Linha 3
         {{1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}}  // Linha 4
        },
    };

    // Exibe os quadros de forma sequencial

    for (int i = 0; i < 10; i++) {
        imprimir_frame_5(frames[i], pio, sm);
        sleep_ms(100);  // Pausa entre cada quadro da animação
    }
}

#endif