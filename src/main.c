#include <avr/io.h>
#include <util/delay.h>

#define DIGITAL_INPUT PB0
#define DIGITAL_OUTPUT PB1
#define SCK_PIN  PB2
#define SS_PIN   PB3

#define SCK_HIGH() (PORTB |= 0b00000100)   // Set SCK high
#define SCK_LOW()  (PORTB &= 0b11111011)  // Set SCK low
#define SS_LOW()   (PORTB &= 0b11110111)   // Set SS low (select slave)
#define SS_HIGH()  (PORTB |= 0b00001000)    // Set SS high (deselect slave)

void usi_init(void) {
    // DDRB |= (1 << DIGITAL_INPUT) | (1 << SCK_PIN) | (1 << SS_PIN);
    // DDRB &= ~(1 << DIGITAL_OUTPUT);
    DDRB = 0b11111110; // DI, DO, SS, SCK
    // Set SS high initially (deselect the slave)
    SS_HIGH();

    // Set up USI for SPI master mode, with software clock strobe
    USICR = (1 << USIWM0) | (1 << USICS1);
}

uint8_t usi_transfer(uint8_t data) {
    USIDR = data;  // Load data into USI Data Register
    // USICR &= ~(1 << USIOIF);  // Clear the USI overflow flag ??

    for(uint8_t i = 0; i < 16; i++){
        // Do I need the USICK bit?
        // generate_signal();
        /*PORTB |= (1 << SCK_PIN);  // Clock high
        _delay_us(1);
        PORTB &= ~(1 << SCK_PIN);  // Clock low
        _delay_us(1);*/
         USICR ^= (1 << USITC);
    }
    /*
    for (uint8_t i = 0; i < 8; i++) { // should this not happen on its own, after toggling the required bit
        PORTB |= (1 << SCK_PIN);  // Clock high
        _delay_us(1);
        PORTB &= ~(1 << SCK_PIN);  // Clock low
        _delay_us(1);
    }*/
    return USIDR;  // Return received data
}

int main(void) {
    usi_init();

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