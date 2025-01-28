 # BitDogLab_GPIO

__SUBGRUPO 0__<br>
Repositório criado a fim de registrar a realização da atividade referente à aula síncrona do dia 20/01/2025.

__Componentes do grupo:__
Ana Karolina Disigant Reis, Andressa Sousa Fonseca, Gabriel Vitor, Lucas Carneiro de Araújo Lima, Luiz Rodrigo Oliveira da Silva, Matheus Santos Souza e Wesley R.

## ATIVIDADE 
__Microcontroladores - GPIO (PARTE 2)__<br>

A atividade pede que, com o auxílio do simulador de eletrônica Wokwi, utilize-se o Raspberry Pi Pico W e um teclado matricial 4x4 para gerar informações visuais em uma matriz de LEDs Coloridos (5x5 WS2812). 

__Para esta prática, os seguintes componentes e acessórios se fazem necessários:__
1) Teclado matricial 4x4.
2) Microcontrolador Raspberry Pi Pico W.
3) Matriz de LEDs Coloridos (LED-RGB 5x5 WS2812).
4) Buzzer Passivo Eletromagnético MLT-8530 SMD 3.6V

__O código com a lógica adotada pelo grupo se encontra no presente reposítório e o resultado pode ser assistido no vídeo alocado neste link: [Aplicação GPIOs - animações em LED](https://www.youtube.com/watch?v=UjJnq5CxnIs).__

## Instruções de Uso

### 1. Clone o repositório
Abra o terminal e execute o comando abaixo para clonar o repositório em sua máquina:
```bash
git clone https://github.com/Dreh3/ledsAnimados.git
```

### 2. Configure o ambiente de desenvolvimento
Certifique-se de que o [SDK do Raspberry Pi Pico](https://github.com/raspberrypi/pico-sdk) esteja instalado e configurado corretamente no seu sistema.

### 3. Compile o projeto
Navegue até o diretório raiz do projeto e execute os comandos abaixo:
```bash
mkdir build
cd build
cmake ..
make
```
O arquivo `matrizAnimada.uf2` será gerado na pasta `build`.

### 4. Carregue o programa no Raspberry Pi Pico
1. Conecte o Raspberry Pi Pico ao seu computador enquanto mantém pressionado o botão **BOOTSEL**.
2. O Pico será montado como um dispositivo de armazenamento USB.
3. Copie o arquivo `matrizAnimada.uf2` para o dispositivo montado.
4. O Pico reiniciará automaticamente e executará o programa.

### 5. Conecte a matriz de LEDs
Siga o diagrama de conexão fornecido no arquivo `diagram.json` para conectar corretamente a matriz de LEDs **WS2812** ao Raspberry Pi Pico.

### 6. Execute o programa
Após completar as etapas anteriores, o programa será executado no Raspberry Pi Pico, exibindo as animações implementadas na matriz de LEDs.

## Observações

- Certifique-se de usar cabos adequados para conexão e alimentação da matriz de LEDs.
- Para personalizar as animações, modifique os parâmetros no código fonte antes de compilar.

Para mais informações sobre o projeto, consulte a documentação completa no repositório.
