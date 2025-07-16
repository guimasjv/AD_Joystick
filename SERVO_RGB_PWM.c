#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"

// ---------- DEFINIÇÕES DE PINOS ----------
#define VRX_PIN 27          // Eixo X (canal ADC 1)
#define VRY_PIN 26          // Eixo Y (canal ADC 0)
#define BTN_J 22            // Botão do joystick

#define LED_RED 14          // Vermelho (ligado pelo botão)
#define LED_BLUE 12         // Azul (proporcional ao eixo Y)
#define LED_GREEN 13        // Verde (proporcional ao eixo X)

// ---------- CONFIGURAÇÕES DO PWM ----------
#define PWM_WRAP 24999
#define PWM_DIV 100.0
#define DEBOUNCE_TIME 200

// ---------- VARIÁVEIS GLOBAIS ----------
volatile bool red_on = false;                 // Estado do vermelho (ON/OFF)
volatile uint32_t last_interrupt_time = 0;    // Para debounce do botão

// ---------- PROTÓTIPOS ----------
void setup_gpio();
void setup_pwm();
void handle_button_press(uint gpio, uint32_t events);

// ---------- FUNÇÃO PRINCIPAL ----------
int main() {
    adc_init();
    setup_gpio();
    setup_pwm();

    gpio_set_irq_enabled_with_callback(BTN_J, GPIO_IRQ_EDGE_FALL, true, &handle_button_press);

    while (true) {
        // ----- Leitura dos eixos -----
        adc_select_input(0);                  // VRY
        uint16_t y_value = adc_read();

        adc_select_input(1);                  // VRX
        uint16_t x_value = adc_read();

        // ----- Calcula distância ao centro (2048) -----
        float delta_x = fabs((float)x_value - 2048.0f);
        float delta_y = fabs((float)y_value - 2048.0f);

        // ----- Mapeia para PWM (quanto mais longe do centro, maior o brilho) -----
        uint16_t pwm_green = delta_x * PWM_WRAP / 2048;
        uint16_t pwm_blue  = delta_y * PWM_WRAP / 2048;
        uint16_t pwm_red   = red_on ? PWM_WRAP : 0;

        // ----- Atualiza os canais PWM -----
        pwm_set_gpio_level(LED_GREEN, pwm_green);
        pwm_set_gpio_level(LED_BLUE, pwm_blue);
        pwm_set_gpio_level(LED_RED, pwm_red);
    }
}

// ---------- CONFIGURAÇÃO DOS GPIOs ----------
void setup_gpio() {
    gpio_init(BTN_J);
    gpio_init(LED_RED);
    gpio_init(LED_GREEN);
    gpio_init(LED_BLUE);

    adc_gpio_init(VRX_PIN);  // GP27 → canal ADC1
    adc_gpio_init(VRY_PIN);  // GP26 → canal ADC0

    gpio_set_dir(BTN_J, GPIO_IN);
    gpio_pull_up(BTN_J);

    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
}

// ---------- CONFIGURAÇÃO DO PWM ----------
void setup_pwm() {
    // RED
    gpio_set_function(LED_RED, GPIO_FUNC_PWM);
    uint slice_red = pwm_gpio_to_slice_num(LED_RED);
    pwm_set_clkdiv(slice_red, PWM_DIV);
    pwm_set_wrap(slice_red, PWM_WRAP);
    pwm_set_enabled(slice_red, true);

    // GREEN
    gpio_set_function(LED_GREEN, GPIO_FUNC_PWM);
    uint slice_green = pwm_gpio_to_slice_num(LED_GREEN);
    pwm_set_clkdiv(slice_green, PWM_DIV);
    pwm_set_wrap(slice_green, PWM_WRAP);
    pwm_set_enabled(slice_green, true);

    // BLUE
    gpio_set_function(LED_BLUE, GPIO_FUNC_PWM);
    uint slice_blue = pwm_gpio_to_slice_num(LED_BLUE);
    pwm_set_clkdiv(slice_blue, PWM_DIV);
    pwm_set_wrap(slice_blue, PWM_WRAP);
    pwm_set_enabled(slice_blue, true);
}

// ---------- INTERRUPÇÃO DO BOTÃO ----------
void handle_button_press(uint gpio, uint32_t events) {
    uint32_t current_time = to_ms_since_boot(get_absolute_time());

    if (current_time - last_interrupt_time > DEBOUNCE_TIME) {
        last_interrupt_time = current_time;

        if (gpio == BTN_J) {
            red_on = !red_on;  // Alterna o estado do LED vermelho
        }
    }
}
