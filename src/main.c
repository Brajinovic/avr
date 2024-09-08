#include <avr/io.h>
#include <util/delay.h>
#include "three_wire_spi.h"

int main(void) {
    usi_config();

     while (1) {
        // Start communication by pulling SS low
        SS_LOW();

        // Send data and receive response
        uint8_t received = usi_transfer(0x1A);  // Send 0x1A and receive response

        // End communication by pulling SS high
        SS_HIGH();

        _delay_ms(1000);  // Wait a bit before the next transfer
     }

    return 0;
}