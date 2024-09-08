#include <avr/io.h>
#include <util/delay.h>
#include "three_wire_spi.h"

void usi_config(void) {
    DDRB |= (1 << DIGITAL_OUTPUT) | (1 << CLOCK) | (1 << SLAVE_SELECT); // outputs
    DDRB &= ~(1 << DIGITAL_INPUT);	// input
    // deselect slave
    SS_HIGH();

    // Set up USI for SPI master mode, with software clock strobe
    USICR = (1 << USIWM0) | (1 << USICS1);
}

uint8_t usi_transfer(uint8_t data) {
    USIDR = data;  // Load data into USI Data Register
    for(uint8_t i = 0; i < 16; i++){	// it goes untill 16 because I need to transfer 8 bits (8 clock periods is what I need) and I am toggling the clock
         USICR ^= (1 << USITC);
    }

    return USIDR;  // Return received data
}
