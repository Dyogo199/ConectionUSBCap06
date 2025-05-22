#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "tusb.h"

// Definição dos GPIOs para LEDs e Buzzer
#define LED_VERDE 11
#define LED_AZUL 12
#define LED_VERMELHO 13
#define BUZZER 10  // Para desafio extra

// Função para inicializar todos os GPIOs como saída
void gpio_init_all(void) {
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);

    gpio_init(LED_AZUL);
    gpio_set_dir(LED_AZUL, GPIO_OUT);

    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);

    gpio_init(BUZZER);
    gpio_set_dir(BUZZER, GPIO_OUT);
}

// Função para acender GPIO (LED ou buzzer) por 1 segundo
void acender_gpio(int gpio) {
    gpio_put(gpio, 1);
    sleep_ms(1000);
    gpio_put(gpio, 0);
}

// Função para processar o comando e acionar o hardware correspondente
void processar_comando(const char *comando) {
    if (strcmp(comando, "vermelho") == 0) {
        acender_gpio(LED_VERMELHO);
    } else if (strcmp(comando, "verde") == 0) {
        acender_gpio(LED_VERDE);
    } else if (strcmp(comando, "azul") == 0) {
        acender_gpio(LED_AZUL);
    } else if (strcmp(comando, "som") == 0) {  // Extra
        acender_gpio(BUZZER);
    }
}

int main() {
    stdio_init_all();
    gpio_init_all();

    // Aguarda a conexão USB
    while (!tud_cdc_connected()) {
        sleep_ms(100);
    }

    printf("USB conectado!\n");

    char comando[64] = {0};

    while (true) {
        if (tud_cdc_available()) {
            uint32_t count = tud_cdc_read(comando, sizeof(comando) - 1);
            comando[count] = '\0';  // Finaliza a string

            // Remove quebras de linha
            comando[strcspn(comando, "\r\n")] = 0;

            printf("Recebido: %s\n", comando);

            // Ecoa de volta ao host
            tud_cdc_write(comando, strlen(comando));
            tud_cdc_write_flush();

            // Processa comando e acende LED correspondente
            processar_comando(comando);
        }
        tud_task();
    }

    return 0;
}
