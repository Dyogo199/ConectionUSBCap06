#include "ssd1306.h"
#include "ssd1306_i2c.h"
#include <string.h>

void ssd1306_init(ssd1306_t *dev) {
    const uint8_t init_sequence[] = {
        0xAE, 0x20, 0x00, 0xB0, 0xC8, 0x00,
        0x10, 0x40, 0x81, 0xFF, 0xA1, 0xA6,
        0xA8, 0x3F, 0xA4, 0xD3, 0x00, 0xD5,
        0xF0, 0xD9, 0x22, 0xDA, 0x12, 0xDB,
        0x20, 0x8D, 0x14, 0xAF
    };
    for (size_t i = 0; i < sizeof(init_sequence); i++) {
        ssd1306_send_command(dev, init_sequence[i]);
    }
}

void ssd1306_clear(ssd1306_t *dev) {
    uint8_t zero_buffer[128] = {0};
    for (uint8_t page = 0; page < 8; page++) {
        ssd1306_send_command(dev, 0xB0 + page);
        ssd1306_send_command(dev, 0x00);
        ssd1306_send_command(dev, 0x10);
        ssd1306_send_data(dev, zero_buffer, 128);
    }
}

void ssd1306_draw_string(ssd1306_t *dev, uint8_t x, uint8_t y, const char *str) {
    while (*str) {
        ssd1306_send_command(dev, 0xB0 + y);
        ssd1306_send_command(dev, ((x & 0xF0) >> 4) | 0x10);
        ssd1306_send_command(dev, (x & 0x0F));
        
        uint8_t data[5] = {0x00};
        for (uint8_t i = 0; i < 5; i++) {
            data[i] = 0xFF; // Exemplo: quadrado cheio.
        }
        ssd1306_send_data(dev, data, 5);
        
        x += 6;
        str++;
    }
}