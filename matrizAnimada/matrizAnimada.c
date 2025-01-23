#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"

//arquivo .pio
#include "pio_matrix.pio.h"

#define NUM_PIXELS 25
#define OUT_PIN 7

//botões de interupção
const uint button

#define NUM_PIXELS 25
#define OUT_PIN 7

//botões de interupção
const uint button_A = 0;  // Substituir por pinos do teclado 
const uint button_B = 1;  
const uint button_C = 2;  
const uint button_D = 3; 
const uint button_hash = 4; 
const uint button_star = 5; 

#define INTENSIDADE_ALTA 1.0
#define INTENSIDADE_MEDIA 0.8
#define INTENSIDADE_BAIXA 0.5
#define INTENSIDADE_MINIMA 0.2

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

void modo_gravacao()
{
    reset_usb_boot(0,0); //modo de gravação
}

int main()
{
    PIO pio = pio0; 
    bool ok;
    uint32_t cor;

    //frequência de clock para 128 MHz
    ok = set_sys_clock_khz(128000, false);

    stdio_init_all();

    printf("Iniciando o controle dos LEDs\n");

    uint offset = pio_add_program(pio, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, OUT_PIN);

    // Inicializa os pinos dos botões
    gpio_init(button_A);
    gpio_set_dir(button_A, GPIO_IN);
    gpio_pull_up(button_A);

    gpio_init(button_B);
    gpio_set_dir(button_B, GPIO_IN);
    gpio_pull_up(button_B);

    gpio_init(button_C);
    gpio_set_dir(button_C, GPIO_IN);
    gpio_pull_up(button_C);

    gpio_init(button_D);
    gpio_set_dir(button_D, GPIO_IN);
    gpio_pull_up(button_D);

    gpio_init(button_hash);
    gpio_set_dir(button_hash, GPIO_IN);
    gpio_pull_up(button_hash);

    gpio_init(button_star);
    gpio_set_dir(button_star, GPIO_IN);
    gpio_pull_up(button_star);

    while (true) {
        if (!gpio_get(button_A)) {
            cor = matrix_rgb(0.0, 0.0, 0.0);
            controlar_leds(pio, sm, cor);
            printf("Desligando todos os LEDs\n");
        }
        else if (!gpio_get(button_B)) {
            cor = matrix_rgb(INTENSIDADE_ALTA, 0.0, INTENSIDADE_ALTA); // Azul
            controlar_leds(pio, sm, cor);
            printf("Ligando todos os LEDs na cor azul\n");
        }
        else if (!gpio_get(button_C)) {
            cor = matrix_rgb(INTENSIDADE_ALTA, 0.0, 0.0); // Vermelho
            controlar_leds(pio, sm, cor);
            printf("Ligando todos os LEDs na cor vermelha\n");
        }
        else if (!gpio_get(button_D)) {
            cor = matrix_rgb(0.0, INTENSIDADE_MEDIA, 0.0); // Verde
            controlar_leds(pio, sm, cor);
            printf("Ligando todos os LEDs na cor verde\n");
        }
        else if (!gpio_get(button_hash)) {
            cor = matrix_rgb(INTENSIDADE_MINIMA, INTENSIDADE_MINIMA, INTENSIDADE_MINIMA); // Branco
            controlar_leds(pio, sm, cor);
            printf("Ligando todos os LEDs na cor branca\n");
        }
        else if (!gpio_get(button_star)) {
            printf("Saindo do modo de execução e habilitando o modo de gravação\n");
            modo_gravacao();
        }

        sleep_ms(100); // Aguarda 100ms para evitar leituras repetidas
    }
}