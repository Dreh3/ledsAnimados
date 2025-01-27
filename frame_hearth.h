//Código desenvolvido por Luiz Rodrigo 

#ifndef FRAME_HEARTH_H
#define FRAME_HEARTH_H

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
} config_heart;

typedef config_heart RGB_heart;

typedef config Matriz_config_heart[5][5];

// Função para definição da intensidade de cores do led
uint32_t rgb_matrix_heart(double b, double r, double g)
{
    unsigned char R, G, B;
    R = r * 255;
    G = g * 255;
    B = b * 255;
    return (G << 24) | (R << 16) | (B << 8);
}

// Acionar a matrix de leds - ws2812b
void led_control_heart(PIO pio, uint sm, uint32_t cor)
{
    for (int16_t i = 0; i < NUM_PIXELS; i++) {
        pio_sm_put_blocking(pio, sm, cor);
    }
}

void print_hearth(Matriz_config_heart configuracao, PIO pio, uint sm){
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

RGB RGB_parameter_heart(int red, int green, int blue){
    RGB cor_customizada = {red/255.0, green/255.0, blue/255.0};
    return cor_customizada;
}

void frame_hearth(PIO pio, uint sm,float itnsty) {

    Matriz_config_heart hearth_frames[] = {
        //1 frame Coração
        {
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}  // Linha 4
        },

        //2 frame Coração
        {
            {{0.0, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}  // Linha 4
        },

        //3 frame Coração
        {
            {{1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}}, // Linha 0
            {{0.0, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}  // Linha 4
        },

        //4 frame Coração
        {
            {{1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}}, // Linha 0
            {{1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}}, // Linha 1
            {{0.0, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}  // Linha 4
        },

        //5 frame Coração
        {
            {{1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}}, // Linha 0
            {{1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}}, // Linha 1
            {{1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}}, // Linha 2
            {{0.0, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}  // Linha 4
        },

        //6 frame Coração
        {
            {{0.0, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
            {{1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}}, // Linha 1
            {{1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}}, // Linha 2
            {{1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}}, // Linha 3
            {{1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}}  // Linha 4
        },

        //7 frame Coração
        {
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
            {{0.0, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
            {{1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}}, // Linha 2
            {{1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}}, // Linha 3
            {{1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}}  // Linha 4
        },

        //8 frame Coração
        {
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
            {{0.0, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
            {{1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}}, // Linha 3
            {{1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}}  // Linha 4
        },


        //9 frame Coração
        {
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
            {{0.0, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
            {{1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}}  // Linha 4
        },

        //10 frame Coração
        {
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
            {{0.0, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
            {{1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}}  // Linha 4
        },

        //11 frame Coração
        {
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
            {{0.0, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0*itnsty, 0.0, 0.0}, {0.0, 0.0, 0.0}}  // Linha 4
        },

        //12 frame Coração
        {
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}  // Linha 4
        }
    };

    for (int i = 0; i < 12; i++) {
        print_hearth(hearth_frames[i], pio, sm);
        sleep_ms(250); 
    }
}

#endif

