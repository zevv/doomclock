#ifndef spi_h
#define spi_H

void spi_init();
void spi_tx(uint8_t *buf, size_t len, uint8_t b9);

#endif
