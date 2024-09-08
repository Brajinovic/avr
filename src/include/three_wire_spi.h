#ifndef THREE_WIRE_SPI_H
#define THREE_WIRE_SPI_H

#include <avr/io.h>

#define DIGITAL_INPUT PB0
#define DIGITAL_OUTPUT PB1
#define CLOCK  PB2
#define SLAVE_SELECT   PB3

void usi_config(void);
uint8_t usi_transfer(uint8_t data);


#endif