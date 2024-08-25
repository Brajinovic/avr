#include <avr/io.h>
#include <util/delay.h>

// Define USI pins for ATtiny85
#define SS_PIN   PB3
#define MOSI_PIN PB0
#define MISO_PIN PB1
#define SCK_PIN  PB2

void USI_SPI_MasterInit(void) {
    // Set MOSI, SCK, and SS as output, MISO as input
    DDRB |= (1 << MOSI_PIN) | (1 << SCK_PIN) | (1 << SS_PIN);
    DDRB &= ~(1 << MISO_PIN);  // MISO is input

    // Set USI to three-wire mode, clock source: external, positive edge
    USICR = (1 << USIWM0) | (1 << USICS1); // 3-wire mode, ext. clock positive edge
    
    // Set SS high to deselect the slave initially
    PORTB |= (1 << SS_PIN);
}

void USI_SPI_MasterTransmit(uint8_t data) {
    // Load data into the USI data register
    USIDR = data;

    // Clear the USI counter overflow flag
    USISR = (1 << USIOIF);

    // Manually generate clock pulses by toggling SCK
    for (uint8_t i = 0; i < 16; i++) { // 8 cycles for each bit, 16 edges total
        USICR |= (1 << USITC);  // Toggle the clock
    }

    // Wait for transmission to complete (check overflow flag)
    while (!(USISR & (1 << USIOIF)));
}

void SPI_SetSlaveSelectLow(void) {
    PORTB &= ~(1 << SS_PIN);  // Pull SS low to select the slave
}

void SPI_SetSlaveSelectHigh(void) {
    PORTB |= (1 << SS_PIN);   // Pull SS high to deselect the slave
}

int main(void) {
    // Initialize USI as SPI Master
    USI_SPI_MasterInit();

    // Loop and send data continuously
    while (1) {
        // Select the slave
        SPI_SetSlaveSelectLow();

        // Transmit data (example: 0x55)
        USI_SPI_MasterTransmit(0x55);

        // Deselect the slave
        SPI_SetSlaveSelectHigh();

        // Delay for visibility (example: 1 second)
        _delay_ms(1000);
    }

    return 0;
}