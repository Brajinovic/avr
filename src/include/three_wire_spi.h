#ifndef THREE_WIRE_SPI_H
#define THREE_WIRE_SPI_H


int configure_spi(int mode); // 0 - slave mode; 1 - master mode
void send();
void receive();

#endif