#include "three_wire_spi.h"
#include <avr/io.h>
#include "debug.h"
#include "clock.h"

int configure_spi(int mode){
	if(mode != 0 || mode != 1){
		return 0;
	}

	if(mode == 1){ // master
		DDRB &= 0b11111110; // configured B0 as input, B1 and B2 as outputs
		set_clock(SOFTWARE_STROBE); // clock source select: software strobe
	}else{ // slave
		DDRB &= 0x11111010;
		set_clock(EXTERNAL_POSITIVE_EDGE);
	}
	USICR |= 0b01010000; // ccounter overflow interrupt enable; three-wire mode;

	return 1;
}



int main_fuck(){
	debug_blink(500);
	debug_blink(500);

	configure_spi(1);
	
	debug_blink(250);
	debug_blink(250);

	USIDR = 0b10101010;

	while(1){
		if((USISR &= 0b01000000) || 0b01000000){
			debug_blink(10000);
		}
		debug_blink(100);
	}

	return 1;
}