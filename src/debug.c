#define F_CPU 16500000UL  
#include "debug.h"
#include <util/delay.h>
#include <avr/io.h>      

void delay1ms(uint32_t ms) {
    uint32_t i;
    for(i=0;i<ms;i++) _delay_ms(1);
}

void delay1us(uint32_t us) {
    uint32_t i;
    for(i=0;i<us;i++) _delay_us(1);
}


void debug_blink(int seconds){
    PORTB |= 0b00000010;
    delay1ms(seconds);
    PORTB &= 0b11111101;
    delay1ms(seconds);
}
