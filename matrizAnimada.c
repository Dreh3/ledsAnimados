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

#include"frame_2.h"
#include "frame_boat.h"
#include "frame_pulser.h"
#include "frame_numbers.h"

#define NUM_PIXELS 25
#define OUT_PIN 7

//botões de interupção
const uint button;

#define NUM_PIXELS 25
#define OUT_PIN 7

//Definindo pinos das linhas e colunas do teclado matricial
#define R1 9
#define R2 8
#define R3 10
#define R4 6
#define C1 5
#define C2 4
#define C3 3
#define C4 2


#define INTENSIDADE_ALTA 1.0
#define INTENSIDADE_MEDIA 0.8
#define INTENSIDADE_BAIXA 0.5
#define INTENSIDADE_MINIMA 0.2


//Função para inicializar pinos do teclado
void init_teclado(){
  gpio_init(R1);
  gpio_init(R2);
  gpio_init(R3);
  gpio_init(R4);
  gpio_init(C1);
  gpio_init(C2);
  gpio_init(C3);
  gpio_init(C4);
  gpio_set_dir(R1, GPIO_OUT);
  gpio_set_dir(R2, GPIO_OUT);
  gpio_set_dir(R3, GPIO_OUT);
  gpio_set_dir(R4, GPIO_OUT);
  gpio_set_dir(C1, GPIO_IN);
  gpio_set_dir(C2, GPIO_IN);
  gpio_set_dir(C3, GPIO_IN);
  gpio_set_dir(C4, GPIO_IN);
  gpio_pull_up(C1);
  gpio_pull_up(C2);
  gpio_pull_up(C3);
  gpio_pull_up(C4);
}

//Leitura do teclado
char keypad_leitura(){
  char teclado [4][4] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
  };
  int linhas [] = {R1,R2,R3,R4};
  int colunas [] = {C1,C2,C3,C4};

  for(int lin =0; lin<4; lin ++){
    gpio_put(linhas[lin],0);
    for(int col =0; col<4; col++){
      if(!gpio_get(colunas[col])){
        sleep_ms(100);
        gpio_put(linhas[lin],1);
        return(teclado[lin][col]);
      }
    }
    gpio_put(linhas[lin],1);
  }
  return '\0';
}


int main()
{
    PIO pio = pio0; 
    bool ok;
    uint32_t cor;

    char tecla='\0';

    //frequência de clock para 128 MHz
    ok = set_sys_clock_khz(128000, false);

    init_teclado();
    stdio_init_all();

    printf("           CONTROLE DOS LEDs                                                ANIMAÇÕES PERSONALIZADAS \n");
    printf("                         \n");
    printf("A - Desliga todos os LEDs acesos;                                     0 - Luiz;\n");
    printf("B - Liga todos os LEDs da cor azul;                                   1 - Wesley;\n");
    printf("C - Liga todos os LEDs da cor vermelha;                               2 - Matheus;\n");
    printf("D - Liga todos os LEDs da cor verde;                                  3 - Ana Karolina;\n");          
    printf("# - Liga todos os LEDs da cor branca;                                 4 - Andressa;\n");    //a partir daqui a ordem muda por ordem de commit
    printf("* - Sai do modo de execução e habilita o de gravação;                 5 - Lucas;\n");       //essa foi só p organizar
    printf("                                                                      6 - Gabriel.\n");   
               
    uint offset = pio_add_program(pio, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, OUT_PIN);


    while (true) {
        while(tecla=='\0'){
            tecla=keypad_leitura();
            sleep_ms(200);
        }
        printf("Tecla %c pressionada!!!\n",tecla);
        if (tecla=='A') {
            cor = matrix_rgb(0.0, 0.0, 0.0);
            controlar_leds(pio, sm, cor);
            printf("desligando todos os LEDs\n");
        }
        else if (tecla=='B') {
            cor = matrix_rgb(INTENSIDADE_ALTA, 0.0, 0.0); // Azul
            controlar_leds(pio, sm, cor);
            printf("ligando todos os LEDs na cor azul\n");
        }
        else if (tecla=='C') {
            cor = matrix_rgb(0.0, INTENSIDADE_MEDIA, 0.0); // Vermelho
            controlar_leds(pio, sm, cor);
            printf("ligando todos os LEDs na cor vermelha\n");
        }
        else if (tecla=='D') {
            cor = matrix_rgb(0.0, 0.0, INTENSIDADE_BAIXA); // Verde
            controlar_leds(pio, sm, cor);
            printf("ligando todos os LEDs na cor verde\n");
        }
        else if (tecla=='#') {
            cor = matrix_rgb(INTENSIDADE_MINIMA, INTENSIDADE_MINIMA, INTENSIDADE_MINIMA); // Branco
            controlar_leds(pio, sm, cor);
            printf("ligando todos os LEDs na cor branca\n");
        }
        else if (tecla=='*') {
            printf("Saindo do modo de execução e habilitando o modo de gravação\n\n");
            modo_gravacao();
        }else if(tecla=='1') {
            frame_numbers(1,pio,sm);
            controlar_leds(pio, sm, matrix_rgb(0.0, 0.0, 0.0));
            printf("Apresentando a animação de ????\n\n");
        }else if(tecla=='2') {
            frame_numbers(2,pio,sm);
            controlar_leds(pio, sm, matrix_rgb(0.0, 0.0, 0.0));
            printf("Apresentando a animação de Matheus Santos Souza (");
            printf("Ponto -> Quadrado -> Quadrado Maior -> Ponto -> X -> Quadrado X)\n\n");
            frame_2(pio,sm);
        }else if(tecla=='3') {
            frame_numbers(3,pio,sm);
            controlar_leds(pio, sm, matrix_rgb(0.0, 0.0, 0.0));
            printf("Apresentando a animação de Ana Karolina Disigant (Barco...)\n\n");
            frame_boat(pio, sm);
        }else if(tecla=='4') {
            frame_numbers(4,pio,sm);
            controlar_leds(pio, sm, matrix_rgb(0.0, 0.0, 0.0));
            printf("Apresentando a animação de Lucas Carneiro de A. Lima (Pulser...)\n\n");
            frame_pulser(pio, sm);
        }else if(tecla=='5'){
            frame_numbers(5,pio,sm);
            controlar_leds(pio, sm, matrix_rgb(0.0, 0.0, 0.0));
            printf("Apresentando a animação de ????\n\n");
        }else if(tecla=='6'){
            frame_numbers(6,pio,sm);
            controlar_leds(pio, sm, matrix_rgb(0.0, 0.0, 0.0));
            printf("Apresentando a animação de ????\n\n");
        }else if(tecla=='7'){
            frame_numbers(7,pio,sm);
            controlar_leds(pio, sm, matrix_rgb(0.0, 0.0, 0.0));
            printf("Apresentando a animação de ????\n\n");
        }else if(tecla=='8'){
            frame_numbers(8,pio,sm);
            controlar_leds(pio, sm, matrix_rgb(0.0, 0.0, 0.0));
            printf("Apresentando a animação de ????\n\n");
        }else if(tecla=='9'){
            frame_numbers(9,pio,sm);
            controlar_leds(pio, sm, matrix_rgb(0.0, 0.0, 0.0));
            printf("Apresentando a animação de ????\n\n");
        }else if(tecla=='0'){
            frame_numbers(0,pio,sm);
            controlar_leds(pio, sm, matrix_rgb(0.0, 0.0, 0.0));
            printf("Apresentando a animação de ????\n\n");
        }else{
            printf("%c",tecla);
        }
        tecla='\0';
        sleep_ms(100); // Aguarda 100ms para evitar leituras repetidas
    }
}
