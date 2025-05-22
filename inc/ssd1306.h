#ifndef SSD1306_H
#define SSD1306_H

#include "hardware/i2c.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

typedef struct {
    uint8_t width, height, pages, address;
    i2c_inst_t *i2c_port;
    bool external_vcc;
    uint8_t *ram_buffer;
    size_t bufsize;
    uint8_t port_buffer[2];
} ssd1306_t;

void ssd1306_init(ssd1306_t *dev);
void ssd1306_clear(ssd1306_t *dev);
void ssd1306_draw_string(ssd1306_t *dev, uint8_t x, uint8_t y, const char *str);

#endif
