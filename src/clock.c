#include "clock.h"
#include <avr/io.h>   

int clock_strobe(){ // pg. 118
	// first make sure that USICLK - Clock Strobe bit on 0 is
	// so that I can set him on 1 and then later reset him on 0
	USICR &= 0b11111101;
	USICR &= 0b11111111;
	USICR &= 0b11111101;

	return 1;
}
