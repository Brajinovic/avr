#ifndef DEBUG_H
#define DEBUG_H

#include <avr/io.h>      


void delay1ms(uint32_t ms);
void delay1us(uint32_t us);
void debug_blink(int seconds);

#endif