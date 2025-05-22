#ifndef SSD1306_I2C_H
#define SSD1306_I2C_H

#include "ssd1306.h"

int ssd1306_send_command(ssd1306_t *dev, uint8_t cmd);
int ssd1306_send_data(ssd1306_t *dev, const uint8_t *data, size_t size);

#endif
