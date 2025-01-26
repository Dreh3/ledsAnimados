#ifndef FRAME_FLOWER_H
#define FRAME_FLOWER_H

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

void print_flower(Matriz_config configuracao, PIO pio, uint sm){
    for (int contadorLinha = 4; contadorLinha >= 0; contadorLinha--){
        if(contadorLinha % 2){
            for (int contadorColuna = 0; contadorColuna < 5; contadorColuna++){
                uint32_t valor_cor_binario = matrix_rgb(
                    configuracao[contadorLinha][contadorColuna].blue,
                    configuracao[contadorLinha][contadorColuna].red,
                    configuracao[contadorLinha][contadorColuna].green
                );
                pio_sm_put_blocking(pio, sm, valor_cor_binario);
            }
        } else {
            for (int contadorColuna = 4; contadorColuna >= 0; contadorColuna--){
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

// Função para definir as cores para a flor
RGB_cod RGB_parameter(int red, int green, int blue){
    RGB_cod cor_customizada = {red/255.0, green/255.0, blue/255.0};
    return cor_customizada;
}

void frame_flower(PIO pio, uint sm) {
    Matriz_leds_config flower_frames[] = {
        // Frame 1 - Apenas o centro da flor (amarelo)
        {
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}  // Linha 4
        },

        // Frame 2 - Primeira pétala aparece (vermelha)
        {
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 1.0, 1.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
            {{0.0, 0.0, 0.0}, {0.0, 1.0, 1.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 1.0}, {0.0, 0.0, 0.0}}, // Linha 1
            {{0.0, 1.0, 1.0}, {1.0, 0.0, 0.0}, {1.0, 1.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 1.0}}, // Linha 2
            {{0.0, 0.0, 0.0}, {0.0, 1.0, 1.0}, {0.0, 0.0, 0.0}, {0.0, 1.0, 1.0}, {0.0, 0.0, 0.0}}, // Linha 3
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 1.0, 1.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}  // Linha 4
        },

        // Frame 3 - Segunda pétala aparece
        {
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 1.0, 1.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
            {{0.0, 0.0, 0.0}, {0.0, 1.0, 1.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 1.0}, {0.0, 0.0, 0.0}}, // Linha 1
            {{0.0, 1.0, 1.0}, {1.0, 0.0, 0.0}, {1.0, 1.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 1.0}}, // Linha 2
            {{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 1.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 1.0, 1.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}  // Linha 4
        },

        // Frame 4 - Terceira pétala aparece
        {
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 1.0, 1.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
            {{0.0, 0.0, 0.0}, {0.0, 1.0, 1.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 1.0}, {0.0, 0.0, 0.0}}, // Linha 1
            {{0.0, 1.0, 1.0}, {1.0, 0.0, 0.0}, {1.0, 1.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 1.0}}, // Linha 2
            {{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 1.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 1.0, 1.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}  // Linha 4
        },

        // Frame 5 - Flor completa
        {
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 1.0, 1.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
            {{0.0, 0.0, 0.0}, {0.0, 1.0, 1.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 1.0}, {0.0, 0.0, 0.0}}, // Linha 1
            {{0.0, 1.0, 1.0}, {1.0, 0.0, 0.0}, {1.0, 1.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 1.0}}, // Linha 2
            {{0.0, 0.0, 0.0}, {0.0, 1.0, 1.0}, {0.0, 0.0, 0.0}, {0.0, 1.0, 1.0}, {0.0, 0.0, 0.0}}, // Linha 3
            {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 1.0, 1.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}  // Linha 4
        }
    };

    // Exibe a animação de frames da flor
    for (int i = 0; i < 5; i++) {
        imprimir_frame_2(flower_frames[i], pio, sm);
        sleep_ms(500); // Intervalo entre os frames para a animação
    }
}

#endif
