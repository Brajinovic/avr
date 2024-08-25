#include "clock.h"
#include <avr/io.h>   



int set_clock(enum clock_types clock_type){
	USICR &= clock_type;

	return 1;
}

int clock_strobe(){ // pg. 118
	// when using Software clock strobe, this is the way to increment the counter
	// I am toggling the Bit 1 - USICLK: Clock Strobe

	/// Note: The counter is counting to 16 i.e. rising and falling edge
	// 		  so this function is not incrementing but adding 2 to the counter (rising and falling edge)
	USICR &= 0b11111101;
	USICR &= 0b11111111;
	USICR &= 0b11111101;

	return 1;
}
