//Código desenvolvido por Ana Karolina Disigant 

#ifndef FRAME_BOAT_H
#define FRAME_BOAT_H

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
} config;

typedef config RGB;

typedef config Matriz_config[5][5];

// Função para definição da intensidade de cores do led
uint32_t rgb_matrix(double b, double r, double g)
{
    unsigned char R, G, B;
    R = r * 255;
    G = g * 255;
    B = b * 255;
    return (G << 24) | (R << 16) | (B << 8);
}

// Acionar a matrix de leds - ws2812b
void led_control(PIO pio, uint sm, uint32_t cor)
{
    for (int16_t i = 0; i < NUM_PIXELS; i++) {
        pio_sm_put_blocking(pio, sm, cor);
    }
}

void print_boat(Matriz_config configuracao, PIO pio, uint sm){
    for (int contadorLinha = 4; contadorLinha >= 0; contadorLinha--){
        if(contadorLinha % 2){
            for (int contadorColuna = 0; contadorColuna < 5; contadorColuna++){
                uint32_t valor_cor_binario = rgb_matrix(
                    configuracao[contadorLinha][contadorColuna].blue,
                    configuracao[contadorLinha][contadorColuna].red,
                    configuracao[contadorLinha][contadorColuna].green
                );
                pio_sm_put_blocking(pio, sm, valor_cor_binario);
            }
        } else {
            for (int contadorColuna = 4; contadorColuna >= 0; contadorColuna--){
                uint32_t valor_cor_binario = rgb_matrix(
                    configuracao[contadorLinha][contadorColuna].blue,
                    configuracao[contadorLinha][contadorColuna].red,
                    configuracao[contadorLinha][contadorColuna].green
                );
                pio_sm_put_blocking(pio, sm, valor_cor_binario);
            }
        }
    }
}

RGB RGB_parameter(int red, int green, int blue){
    RGB cor_customizada = {red/255.0, green/255.0, blue/255.0};
    return cor_customizada;
}

void frame_boat(PIO pio, uint sm,float itnsty) {
    Matriz_config boat_frames[] = {
        //frame 1 - parte 1 do barco 
        {
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
            {{1.0*itnsty, 1.0*itnsty, 0.0}, {1.0*itnsty, 1.0*itnsty, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
            {{1.0*itnsty, 1.0*itnsty, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}  // Linha 4
        },

        // frame 2 - parte 2 do barco 
        {
            {{1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
            {{1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
            {{1.0*itnsty, 0.5*itnsty, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
            {{1.0*itnsty, 1.0*itnsty, 0.0}, {1.0*itnsty, 1.0*itnsty, 0.0}, {1.0*itnsty, 1.0*itnsty, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
            {{1.0*itnsty, 1.0*itnsty, 0.0}, {1.0*itnsty, 1.0*itnsty, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}  // Linha 4
        },

        // frame 3 - parte 3 do barco
        {
            {{0.0, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
            {{1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
            {{0.0, 0.0, 0.0}, {1.0*itnsty, 0.5*itnsty, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
            {{1.0*itnsty, 1.0*itnsty, 0.0}, {1.0*itnsty, 1.0*itnsty, 0.0}, {1.0*itnsty, 1.0*itnsty, 0.0}, {1.0*itnsty, 1.0*itnsty, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
            {{1.0*itnsty, 1.0*itnsty, 0.0}, {1.0*itnsty, 1.0*itnsty, 0.0}, {1.0*itnsty, 1.0*itnsty, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}  // Linha 4
        },

        // frame 4 -barco
        {
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
            {{0.0, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0*itnsty, 0.5*itnsty, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
            {{1.0*itnsty, 1.0*itnsty, 0.0}, {1.0*itnsty, 1.0*itnsty, 0.0}, {1.0*itnsty, 1.0*itnsty, 0.0}, {1.0*itnsty, 1.0*itnsty, 0.0}, {1.0*itnsty, 1.0*itnsty, 0.0}}, // Linha 3
            {{0.0, 0.0, 0.0}, {1.0*itnsty, 1.0*itnsty, 0.0}, {1.0*itnsty, 1.0*itnsty, 0.0}, {1.0*itnsty, 1.0*itnsty, 0.0}, {0.0, 0.0, 0.0}}  // Linha 4
        },

        // frame 5 -barco
        {
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
            {{0.0, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0*itnsty, 0.5*itnsty, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
            {{1.0*itnsty, 1.0*itnsty, 0.0}, {1.0*itnsty, 1.0*itnsty, 0.0}, {1.0*itnsty, 1.0*itnsty, 0.0}, {1.0*itnsty, 1.0*itnsty, 0.0}, {1.0*itnsty, 1.0*itnsty, 0.0}}, // Linha 3
            {{0.0, 0.0, 0.0}, {1.0*itnsty, 1.0*itnsty, 0.0}, {1.0*itnsty, 1.0*itnsty, 0.0}, {1.0*itnsty, 1.0*itnsty, 0.0}, {0.0, 0.0, 0.0}}  // Linha 4
        },

        // frame 6 - saída do barco 0
        {
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0*itnsty, 0.5*itnsty, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
            {{0.0, 0.0, 0.0}, {1.0*itnsty, 1.0*itnsty, 0.0}, {1.0*itnsty, 1.0*itnsty, 0.0}, {1.0*itnsty, 1.0*itnsty, 0.0}, {1.0*itnsty, 1.0*itnsty, 0.0}}, // Linha 3
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0*itnsty, 1.0*itnsty, 0.0}, {1.0*itnsty, 1.0*itnsty, 0.0}, {1.0*itnsty, 1.0*itnsty, 0.0}}  // Linha 4
        },

        // frame 7 - saída do barco 1
        {
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}}, // Linha 0
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}}, // Linha 1
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0*itnsty, 0.5*itnsty, 0.0}}, // Linha 2
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0*itnsty, 1.0*itnsty, 0.0}, {1.0*itnsty, 1.0*itnsty, 0.0}, {1.0*itnsty, 1.0*itnsty, 0.0}}, // Linha 3
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0*itnsty, 1.0*itnsty, 0.0}, {1.0*itnsty, 1.0*itnsty, 0.0}}  // Linha 4
        },

        // frame 8 - finzinho do barco
        {
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}}, // Linha 1
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0*itnsty, 1.0*itnsty, 0.0}, {1.0*itnsty, 1.0*itnsty, 0.0}}, // Linha 3
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0*itnsty, 1.0*itnsty, 0.0}}  // Linha 4
        },


        // frame 9 - fim do barco
        {
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0*itnsty, 1.0*itnsty, 0.0}}, // Linha 3
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}  // Linha 4
        },

        // frame 10 - fim
        {
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}  // Linha 4
        }

    };

    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < 10; i++) {
            print_boat(boat_frames[i], pio, sm);
            sleep_ms(100); 
        }
    }
}

#endif
