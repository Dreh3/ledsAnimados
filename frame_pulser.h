#ifndef FRAME_PULSER_H
#define FRAME_PULSER_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"
#include <string.h>

// Definição de tipo da estrutura que irá controlar a cor dos LED's
typedef struct {
    double red;
    double green;
    double blue;
}Led_config_3;

typedef Led_config_3 RGB_cod_3;

// Definição de tipo da matriz de leds
typedef Led_config_3 Matriz_leds_config_3[5][5];

Matriz_leds_config_3 default_frame = {
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}  // Linha 4
};


//função para definição da intensidade de cores do led
uint32_t matrix_rgb_3(double b, double r, double g)
{
  unsigned char R, G, B;
  R = r * 255;
  G = g * 255;
  B = b * 255;
  return (G << 24) | (R << 16) | (B << 8);
}


void print_pulser(Matriz_leds_config_3 configuracao, PIO pio, uint sm){
    for (int contadorLinha = 4; contadorLinha >= 0; contadorLinha--){
        if(contadorLinha % 2){
            for (int contadorColuna = 0; contadorColuna < 5; contadorColuna ++){
                uint32_t valor_cor_binario = matrix_rgb_3(
                    configuracao[contadorLinha][contadorColuna].blue,
                    configuracao[contadorLinha][contadorColuna].red,
                    configuracao[contadorLinha][contadorColuna].green
                );

                pio_sm_put_blocking(pio, sm, valor_cor_binario);
            }
        }else{
            for (int contadorColuna = 4; contadorColuna >= 0; contadorColuna --){
                uint32_t valor_cor_binario = matrix_rgb_3(
                    configuracao[contadorLinha][contadorColuna].blue,
                    configuracao[contadorLinha][contadorColuna].red,
                    configuracao[contadorLinha][contadorColuna].green
                );

                pio_sm_put_blocking(pio, sm, valor_cor_binario);
            }
        }
    }
}

void configurar_matriz(Matriz_leds_config_3* frame,float r, float g, float b, int row, int col) {
    (*frame)[row][col].red = r;
    (*frame)[row][col].blue = b;
    (*frame)[row][col].green = g;
}

void framer(Matriz_leds_config_3* frame,Matriz_leds_config_3* base_frame,float r, float g, float b, int row, int col, bool clear,PIO pio,uint sm,bool print,int sleep) {
    if(clear) memcpy(*frame, *base_frame, sizeof(Matriz_leds_config_3));
    configurar_matriz(frame,r,g,b,row,col);
    if(print) {
        print_pulser(*frame, pio, sm);
        sleep_ms(sleep);    
    }
}

void pulser_framing(Matriz_leds_config_3* frame,Matriz_leds_config_3* base_frame, int row [5], int col[5],PIO pio, uint sm) {
    framer(frame,base_frame,0.0625,0,0,row[0],col[0],true,pio,sm,false,0);
    framer(frame,base_frame,0.125,0,0,row[1],col[1],false,pio,sm,false,0);
    framer(frame,base_frame,0.25,0,0,row[2],col[2],false,pio,sm,false,0);
    framer(frame,base_frame,0.5,0,0,row[3],col[3],false,pio,sm,false,0);
    framer(frame,base_frame,1,0,0,row[4],col[4],false,pio,sm,true,100);
}

void frame_pulser(PIO pio, uint sm) {
    Matriz_leds_config_3 frame, base_frame;

    memcpy(base_frame, default_frame, sizeof(Matriz_leds_config_3));

    int count = 0;
    float weight = 1.0;

    for(int i = 0;i < 40;i++) { //40 frames (10 frames a cada 1 seg = 4 seg)
        if(!(i%2)) framer(&frame,&base_frame,0.025*weight,0.025*weight,0.025*weight,0,0,true,pio,sm,true,100);
        else framer(&frame,&base_frame,0.025*weight,0,0,0,0,true,pio,sm,true,100);
        weight=weight+1.0;
    }

    base_frame[0][0].red = 0;

    for(int i = 0; i < 4; i++) { //16 frames
        pulser_framing(&frame,&base_frame,(int []){0,1,2,3,4},(int []){0,0,0,0,0},pio,sm);
        pulser_framing(&frame,&base_frame,(int []){4,4,4,4,4},(int []){0,1,2,3,4},pio,sm);
        pulser_framing(&frame,&base_frame,(int []){4,3,2,1,0},(int []){4,4,4,4,4},pio,sm);
        pulser_framing(&frame,&base_frame,(int []){0,0,0,0,0},(int []){4,3,2,1,0},pio,sm);
    }

    for(int i = 0; i < 4; i++) { //16 frames
        pulser_framing(&frame,&base_frame,(int []){0,1,2,3,4},(int []){0,0,0,0,0},pio,sm);
        pulser_framing(&frame,&base_frame,(int []){4,3,2,1,0},(int []){0,1,2,3,4},pio,sm);
        pulser_framing(&frame,&base_frame,(int []){0,1,2,3,4},(int []){4,4,4,4,4},pio,sm);
        pulser_framing(&frame,&base_frame,(int []){4,3,2,1,0},(int []){4,3,2,1,0},pio,sm);
    }

    //2 frames
    pulser_framing(&frame,&base_frame,(int []){0,1,2,2,2},(int []){0,0,0,1,2},pio,sm);
    pulser_framing(&frame,&base_frame,(int []){2,2,2,3,4},(int []){2,3,4,3,2},pio,sm);

    for(int i = 0; i < 4; i++) { //16 frames, 16+16+16+2 = 50 frames  (10 frames a cada 1 seg = 5 seg)
        pulser_framing(&frame,&base_frame,(int []){2,3,4,3,2},(int []){4,3,2,1,0},pio,sm);
        pulser_framing(&frame,&base_frame,(int []){4,3,2,1,0},(int []){2,1,0,1,2},pio,sm);
        pulser_framing(&frame,&base_frame,(int []){2,1,0,1,2},(int []){0,1,2,3,4},pio,sm);
        pulser_framing(&frame,&base_frame,(int []){0,1,2,3,4},(int []){2,3,4,3,2},pio,sm);
    }

    //1 frame
    pulser_framing(&frame,&base_frame,(int []){2,3,4,4,4},(int []){4,3,2,1,0},pio,sm);

    for(int i = 0; i < 2; i++) { //72 frames
        pulser_framing(&frame,&base_frame,(int []){4,4,4,3,3},(int []){2,1,0,0,1},pio,sm);
        pulser_framing(&frame,&base_frame,(int []){4,3,3,3,3},(int []){0,0,1,2,3},pio,sm);
        pulser_framing(&frame,&base_frame,(int []){3,3,3,3,2},(int []){1,2,3,4,4},pio,sm);
        pulser_framing(&frame,&base_frame,(int []){3,3,2,2,2},(int []){3,4,4,3,2},pio,sm);
        pulser_framing(&frame,&base_frame,(int []){2,2,2,2,2},(int []){4,3,2,1,0},pio,sm);
        pulser_framing(&frame,&base_frame,(int []){2,2,2,1,1},(int []){2,1,0,0,1},pio,sm);
        pulser_framing(&frame,&base_frame,(int []){2,1,1,1,1},(int []){0,0,1,2,3},pio,sm);
        pulser_framing(&frame,&base_frame,(int []){1,1,1,1,0},(int []){1,2,3,4,4},pio,sm);
        pulser_framing(&frame,&base_frame,(int []){1,1,0,0,0},(int []){3,4,4,3,2},pio,sm);
        pulser_framing(&frame,&base_frame,(int []){0,0,0,0,0},(int []){4,3,2,1,0},pio,sm);
        pulser_framing(&frame,&base_frame,(int []){0,0,0,1,2},(int []){2,1,0,0,0},pio,sm);
        pulser_framing(&frame,&base_frame,(int []){0,1,2,3,4},(int []){0,0,0,0,0},pio,sm);
        pulser_framing(&frame,&base_frame,(int []){2,3,4,4,3},(int []){0,0,0,1,1},pio,sm);
        pulser_framing(&frame,&base_frame,(int []){4,4,3,2,1},(int []){0,1,1,1,1},pio,sm);
        pulser_framing(&frame,&base_frame,(int []){3,2,1,0,0},(int []){1,1,1,1,2},pio,sm);
        pulser_framing(&frame,&base_frame,(int []){1,0,0,1,2},(int []){1,1,2,2,2},pio,sm);
        pulser_framing(&frame,&base_frame,(int []){0,1,2,3,4},(int []){2,2,2,2,2},pio,sm);
        pulser_framing(&frame,&base_frame,(int []){2,3,4,4,3},(int []){2,2,2,3,3},pio,sm);
        pulser_framing(&frame,&base_frame,(int []){4,4,3,2,1},(int []){2,3,3,3,3},pio,sm);
        pulser_framing(&frame,&base_frame,(int []){3,2,1,0,0},(int []){3,3,3,3,4},pio,sm);
        pulser_framing(&frame,&base_frame,(int []){1,0,0,1,2},(int []){3,3,4,4,4},pio,sm);
        pulser_framing(&frame,&base_frame,(int []){0,1,2,3,4},(int []){4,4,4,4,4},pio,sm);
        pulser_framing(&frame,&base_frame,(int []){2,3,4,4,4},(int []){4,4,4,3,2},pio,sm);
        pulser_framing(&frame,&base_frame,(int []){4,4,4,4,4},(int []){4,3,2,1,0},pio,sm);
    }

    //4 frames
    pulser_framing(&frame,&base_frame,(int []){4,4,4,4,3},(int []){3,2,1,0,0},pio,sm);
    pulser_framing(&frame,&base_frame,(int []){4,4,4,3,2},(int []){2,1,0,0,0},pio,sm);
    pulser_framing(&frame,&base_frame,(int []){4,4,3,2,1},(int []){1,0,0,0,0},pio,sm);
    pulser_framing(&frame,&base_frame,(int []){4,3,2,1,0},(int []){0,0,0,0,0},pio,sm);

    base_frame[0][0].red = 1;

    //3 frames, 72+1+4+3 = 80 frames  (10 frames a cada 1 seg = 8 seg)
    framer(&frame,&base_frame,0.0625,0,0,3,0,true,pio,sm,false,0);
    framer(&frame,&base_frame,0.125,0,0,2,0,false,pio,sm,false,0);
    framer(&frame,&base_frame,0.25,0,0,1,0,false,pio,sm,true,100);

    framer(&frame,&base_frame,0.0625,0,0,2,0,true,pio,sm,false,0);
    framer(&frame,&base_frame,0.125,0,0,1,0,false,pio,sm,true,100);

    framer(&frame,&base_frame,0,0,0,1,0,true,pio,sm,true,100);

    //Total: 17 segundos = 170 frames
}

#endif