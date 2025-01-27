#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"
#include "hardware/pwm.h"

//arquivo .pio
#include "pio_matrix.pio.h"

#include"frame_2.h"
#include "frame_boat.h"
#include "frame_pulser.h"
#include "frame_numbers.h"
#include "frame_1.h"
#include "frame_hearth.h"
#include "frame_wesley.h"
#include "frame_color_chaser.h"
#include "frame_8.h"



#define BUZZER_PIN 21 //Define GPIO21

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

// Frequências das notas musicais (em Hz)
enum NotasMusicais {
    DO = 2640, // Dó
    RE = 2970, // Ré
    MI = 3300, // Mi
    FA = 3520, // Fá
    SOL = 3960, // Sol
    LA = 4400, // Lá
    SI = 4950  // Si
};

// Configura o PWM no pino do buzzer com uma frequência especificada
void set_buzzer_frequency(uint pin, uint frequency) {
    uint slice_num = pwm_gpio_to_slice_num(pin);
    gpio_set_function(pin, GPIO_FUNC_PWM);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, clock_get_hz(clk_sys) / (frequency * 4096));
    pwm_init(slice_num, &config, true);
    pwm_set_gpio_level(pin, 0);
}

// Função para tocar o buzzer por um tempo especificado (em milissegundos)
void play_buzzer(uint pin, uint frequency, uint duration_ms) {
    set_buzzer_frequency(pin, frequency);
    pwm_set_gpio_level(pin, 32768);
    sleep_ms(duration_ms);
    pwm_set_gpio_level(pin, 0);
}


int main()
{
    PIO pio = pio0; 
    bool ok;
    uint32_t cor;

    float itnsty = 1;

    char tecla='\0';
    char buffer='\0';

    //frequência de clock para 128 MHz
    ok = set_sys_clock_khz(128000, false);

    init_teclado();
    stdio_init_all();
    uart_init(uart0, 115200);

    printf("           CONTROLE DOS LEDs                                                ANIMAÇÕES PERSONALIZADAS \n");
    printf("                         \n");
    printf("A - Desliga todos os LEDs acesos;                                     0 - Luiz;\n");
    printf("B - Liga todos os LEDs da cor azul;                                   1 - Andressa;\n");
    printf("C - Liga todos os LEDs da cor vermelha;                               2 - Matheus;\n");
    printf("D - Liga todos os LEDs da cor verde;                                  3 - Ana Karolina;\n");          
    printf("# - Liga todos os LEDs da cor branca;                                 4 - Lucas;\n");    
    printf("* - Sai do modo de execução e habilita o de gravação;                 5 - Wesley;\n");       
    printf("                                                                      6 - Gabriel.\n");   
               
    uint offset = pio_add_program(pio, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, OUT_PIN);

    while (true) {
        while(tecla=='\0') {
            tecla=keypad_leitura();
            sleep_ms(200);
            if(tecla == '\0') {
                itnsty = 0.05;
                tecla = getchar_timeout_us(50);
                if(tecla == PICO_ERROR_TIMEOUT) tecla = '\0';
            } else {
                itnsty = 1;
            }
        }
        if(('0' <= tecla && tecla <= '9') || tecla == 'A' || tecla == 'B' || tecla == 'C' || tecla == 'D' || tecla == '#') printf("Tecla %c pressionada!\n",tecla);
        if (tecla=='A') { 
            if(buffer != tecla) {play_buzzer(BUZZER_PIN, DO, 500);}
            cor = matrix_rgb(0.0, 0.0, 0.0);
            controlar_leds(pio, sm, cor);
            printf("Desligando todos os LEDs\n\n");
        }
        else if (tecla=='B') {
            if(buffer != tecla) {play_buzzer(BUZZER_PIN, RE, 500);}
            cor = matrix_rgb(1*itnsty, 0.0, 0.0); // Azul
            controlar_leds(pio, sm, cor);
            printf("Ligando todos os LEDs na cor azul\n\n");
        }
        else if (tecla=='C') {
            if(buffer != tecla) {play_buzzer(BUZZER_PIN, MI, 500);}
            cor = matrix_rgb(0.0, 1*itnsty, 0.0); // Vermelho
            controlar_leds(pio, sm, cor);
            printf("Ligando todos os LEDs na cor vermelha\n\n");
        }
        else if (tecla=='D') {
            if(buffer != tecla) {play_buzzer(BUZZER_PIN, FA, 500);}
            cor = matrix_rgb(0.0, 0.0, 1*itnsty); // Verde
            controlar_leds(pio, sm, cor);
            printf("Ligando todos os LEDs na cor verde\n\n");
        }
        else if (tecla=='#') {
            if(buffer != tecla) {play_buzzer(BUZZER_PIN, SOL, 500);}
            cor = matrix_rgb(1*itnsty, 1*itnsty, 1*itnsty); // Branco
            controlar_leds(pio, sm, cor);
            printf("Ligando todos os LEDs na cor branca\n\n");
        }
        else if (tecla=='*') {
            if(buffer != tecla) {play_buzzer(BUZZER_PIN, LA, 500);}
            printf("Saindo do modo de execução e habilitando o modo de gravação\n\n");
            modo_gravacao();
        }
        else if(tecla=='0'){
            if(buffer != tecla) {
                play_buzzer(BUZZER_PIN, DO, 500);
                frame_numbers(0,pio,sm,itnsty);
                controlar_leds(pio, sm, matrix_rgb(0.0, 0.0, 0.0));
            }
        }
        else if(tecla=='1') {
            if(buffer != tecla) {
                play_buzzer(BUZZER_PIN, RE, 500);
                frame_numbers(1,pio,sm,itnsty);
                controlar_leds(pio, sm, matrix_rgb(0.0, 0.0, 0.0));
            }
            printf("Apresentando a animação de Andressa Sousa (Arvore...)\n\n");  
            frame_arvore(pio, sm,itnsty);
        }
        else if(tecla=='2') {
            if(buffer != tecla) {
                play_buzzer(BUZZER_PIN, MI, 500);
                frame_numbers(2,pio,sm,itnsty);
                controlar_leds(pio, sm, matrix_rgb(0.0, 0.0, 0.0));
            }
            printf("Apresentando a animação de Matheus Santos Souza (");
            printf("Ponto -> Quadrado -> Quadrado Maior -> Ponto -> X -> Quadrado X)\n\n");
            frame_2(pio,sm,itnsty);
        }
        else if(tecla=='3') {
            if(buffer != tecla) {
                play_buzzer(BUZZER_PIN, FA, 500);
                frame_numbers(3,pio,sm,itnsty);
                controlar_leds(pio, sm, matrix_rgb(0.0, 0.0, 0.0));
            }
            printf("Apresentando a animação de Ana Karolina Disigant (Barco...)\n\n");
            frame_boat(pio, sm,itnsty);
        }
        else if(tecla=='4') {
            if(buffer != tecla) {
                play_buzzer(BUZZER_PIN, SOL, 500);
                frame_numbers(4,pio,sm,itnsty);
                controlar_leds(pio, sm, matrix_rgb(0.0, 0.0, 0.0));
            }
            printf("Apresentando a animação de Lucas Carneiro de A. Lima (Pulser...)\n\n");
            frame_pulser(pio, sm,itnsty==1);
        }
        else if(tecla=='5'){
            if(buffer != tecla) {
                play_buzzer(BUZZER_PIN, LA, 500);
                frame_numbers(5,pio,sm,itnsty);
                controlar_leds(pio, sm, matrix_rgb(0.0, 0.0, 0.0));
            }
            printf("Apresentando a animação de Wesley ( ;) )\n\n");
            frame_wesley(pio, sm,itnsty);
        }
        else if(tecla=='6') {
            if(buffer != tecla) {
                play_buzzer(BUZZER_PIN, SI, 500);
                frame_numbers(6,pio,sm,itnsty);
                controlar_leds(pio, sm, matrix_rgb(0.0, 0.0, 0.0));
            }
            printf("Apresentando a animação de Luiz Rodrigo (Coração...)\n\n");
            frame_hearth(pio,sm,itnsty);
        }
        else if(tecla=='7') {
            if(buffer != tecla) {
                play_buzzer(BUZZER_PIN, DO, 500);
                frame_numbers(7,pio,sm,itnsty);
                controlar_leds(pio, sm, matrix_rgb(0.0, 0.0, 0.0));
            }
            printf("Apresentando animação EXTRA! (Perseguidor de cores..)\n\n");
            chaser_animation(pio, sm,itnsty==1);
        } else if(tecla=='8') {
            if(buffer != tecla) {
                play_buzzer(BUZZER_PIN, SOL, 500);
                frame_numbers(8,pio,sm,itnsty);
                controlar_leds(pio, sm, matrix_rgb(0.0, 0.0, 0.0));
            }
            printf("Apresentando animação EXTRA! (Âncora..)\n\n");
            frame_ancora(pio,sm,itnsty);
        }
        else{
        }
        buffer = tecla;
        tecla='\0';
        sleep_ms(100); // Aguarda 100ms para evitar leituras repetidas
    }
}