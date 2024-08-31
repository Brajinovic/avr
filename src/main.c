#include <avr/io.h>
#include <util/delay.h>

#define MOSI_PIN PB0  // PB0 is MOSI : OUTPUT
#define MISO_PIN PB1  // PB1 is MISO : INPUT
#define SCK_PIN  PB2  // PB2 is SCK : OUTPUT
#define SS_PIN   PB3  // PB3 is SS (Slave Select) : OUTPUT

#define SCK_HIGH() (PORTB |= 0b00000100)   // Set SCK high
#define SCK_LOW()  (PORTB &= 0b11111011)  // Set SCK low
#define SS_LOW()   (PORTB &= 0b11110111)   // Set SS low (select slave)
#define SS_HIGH()  (PORTB |= 0b00001000)    // Set SS high (deselect slave)

void usi_init(void) {
    // Set MOSI, SCK, and SS as outputs, MISO as input
    // DDRB |= (1 << MOSI_PIN) | (1 << SCK_PIN) | (1 << SS_PIN);
    // DDRB &= ~(1 << MISO_PIN);  // MISO is input
    DDRB = 0b11111110;
    // Set SS high initially (deselect the slave)
    SS_HIGH();

    // Set up USI for SPI master mode, with software clock strobe
    USICR = (1 << USIWM0) | (1 << USICS1);}

uint8_t usi_transfer(uint8_t data) {
    USIDR = 0xAA;  // Load data into USI Data Register
    USISR = (1 << USIOIF);  // Clear the USI overflow flag

    for (uint8_t i = 0; i < 8; i++) {
        PORTB |= (1 << SCK_PIN);  // Clock high
        _delay_us(1);
        PORTB &= ~(1 << SCK_PIN);  // Clock low
        _delay_us(1);

    }
    return USIDR;  // Return received data
}

int main(void) {
    usi_init();  // Initialize USI for SPI

    while (1) {
        // Start communication by pulling SS low
        SS_LOW();

        // Send data and receive response
        uint8_t received = usi_transfer(0x1A);  // Send 0xAA and receive response

        // End communication by pulling SS high
        SS_HIGH();

        _delay_ms(1000);  // Wait a bit before the next transfer
    }

    return 0;
}