#include "ssd1306_i2c.h"
#include <string.h>

int ssd1306_send_command(ssd1306_t *dev, uint8_t cmd) {
    uint8_t buffer[2] = {0x00, cmd};
    return i2c_write_blocking(dev->i2c_port, dev->address, buffer, 2, false);
}

int ssd1306_send_data(ssd1306_t *dev, const uint8_t *data, size_t size) {
    uint8_t buf[size + 1];
    buf[0] = 0x40;
    memcpy(&buf[1], data, size);
    return i2c_write_blocking(dev->i2c_port, dev->address, buf, size + 1, false);
}
