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

//acionar a matrix de leds - ws2812b
void controlar_leds(PIO pio, uint sm, uint32_t cor)
{
  for (int16_t i = 0; i < NUM_PIXELS; i++) {
    pio_sm_put_blocking(pio, sm, cor);
  }
}

void imprimir_frame_2(Matriz_leds_config configuracao, PIO pio, uint sm){
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

void modo_gravacao()
{
    reset_usb_boot(0,0); //modo de gravação
}


void frame_wesley(PIO pio, uint sm) {
    Matriz_leds_config frames[] = {
        // W
        {
         {{1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}}, // Linha 0
         {{1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}}, // Linha 1
         {{1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}}, // Linha 2
         {{1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}}, // Linha 3
         {{1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}}  // Linha 4
        },
         // E
        {
         {{1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}}, // Linha 0
         {{1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
         {{1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}}, // Linha 2
         {{1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
         {{1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}}  // Linha 4
        },
        // S
        {
         {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}}, // Linha 0
         {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
         {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
         {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
         {{1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}  // Linha 4
        },
        // L
        {
         {{1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
         {{1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
         {{1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
         {{1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
         {{1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}}  // Linha 4
        },
         // E
        {
         {{1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}}, // Linha 0
         {{1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
         {{1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}}, // Linha 2
         {{1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
         {{1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}}  // Linha 4
        },
        // y
        {
         {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}}, // Linha 0
         {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
         {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
         {{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
         {{1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}  // Linha 4
        },
          // Sorriso aberto
        {
         {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
         {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
         {{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
         {{1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}}, // Linha 3
         {{1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}}  // Linha 4
        },
        // Sorriso fechado
        {
         {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
         {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
         {{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
         {{1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}}, // Linha 3
         {{1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}}  // Linha 4
        },
        // Sorriso aberto
        {
         {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
         {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
         {{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
         {{1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}}, // Linha 3
         {{1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}}  // Linha 4
        },
        
    };

    // Exibe os quadros de forma sequencial
    for (int i = 0; i < 9; i++) {
        imprimir_frame_2(frames[i], pio, sm);
        sleep_ms(250);  // Pausa entre cada quadro da animação
    }
}

#endif