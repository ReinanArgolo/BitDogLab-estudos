#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "build/generated/ws2812.pio.h"
#include <stdlib.h>
#include "pico/binary_info.h"
#include "inc/ssd1306.h"
#include "hardware/i2c.h"

#define NUM_LEDS 25       // Número total de LEDs na matriz
#define WS2812_PIN 7      // Pino onde os LEDs estão conectados
#define IS_RGBW false     // Define se os LEDs são RGB (false) ou RGBW (true)
#define I2C_SDA = 14;
#define I2C_SCL = 15;


// Função para definir a cor de um LED individual
void set_led_color(uint32_t *leds, uint led_index, uint32_t color) {
    if (led_index < NUM_LEDS) {
        leds[led_index] = color;
    }
}

// Função para enviar os dados para os LEDs
void update_leds(PIO pio, int sm, uint32_t *leds) {
    for (int i = 0; i < NUM_LEDS; i++) {
        pio_sm_put_blocking(pio, sm, leds[i] << 8u); // Envia os dados para o PIO
    }
}


// Função para criar cores RGB
uint32_t rgb_color(uint8_t red, uint8_t green, uint8_t blue) {
    return ((uint32_t)(red) << 16) | ((uint32_t)(green) << 8) | blue;
}

void blink(uint32_t *leds, uint led_index){ 
    set_led_color(leds, led_index, rgb_color(0, 0, 255));
    update_leds(pio0, 0, leds);
    sleep_ms(100);
    set_led_color(leds, led_index, rgb_color(0, 0, 0));
    update_leds(pio0, 0, leds);
    sleep_ms(100);
    set_led_color(leds, led_index, rgb_color(0, 0, 255));
    update_leds(pio0, 0, leds);
}

int HLEDS[] = {1,3,5,7,9,10,14,16,18,22};


int main() {
    stdio_init_all(); // Inicializa a comunicação serial

    // Configuração do PIO (controlador dos LEDs)
    PIO pio = pio0;                                // Usamos o PIO 0
    int sm = 0;                                    // Usamos o state machine 0
    uint offset = pio_add_program(pio, &ws2812_program); // Carregamos o programa WS2812
    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW); // Inicializa o WS2812 no pino especificado

    // Array para armazenar as cores dos LEDs
    uint32_t leds[NUM_LEDS] = {0}; 

    // Atualiza os LEDs com a configuração
    update_leds(pio, sm, leds);

    // Loop infinito
    while (true) {
     
    for(int i = 0; i < 10; i++){
        set_led_color(leds, HLEDS[i], rgb_color(rand() % 50, 255, rand()%50));
        sleep_ms(100);
        update_leds(pio, sm, leds); //atualiza os leds
        sleep_ms(100); 
     }

     for(int i = 0; i < 10; i++){
        set_led_color(leds, HLEDS[i], rgb_color(0,0,0));
    }
        update_leds(pio, sm, leds); //atualiza os leds

        sleep_ms(100);

        for(int i = 0; i < 10; i++){
            set_led_color(leds, HLEDS[i], rgb_color(0,255,0));
        }
        update_leds(pio, sm, leds); //atualiza os leds
        
        sleep_ms(100);

        for(int i = 0; i < 10; i++){
        set_led_color(leds, HLEDS[i], rgb_color(0,0,0));
    }
        update_leds(pio, sm, leds); //atualiza os leds

        sleep_ms(100);

        for(int i = 0; i < 10; i++){
            set_led_color(leds, HLEDS[i], rgb_color(0,255,0));
        }
        update_leds(pio, sm, leds); //atualiza os leds


    for(int i = 0; i < 10; i++){
        set_led_color(leds, HLEDS[i], rgb_color(0,0,0));
        sleep_ms(100);
        update_leds(pio, sm, leds); //atualiza os leds
    }

    }

    return 0;
}