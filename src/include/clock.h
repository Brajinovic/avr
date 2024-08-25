#ifndef CLOCK_H
#define CLOCK_H

enum clock_types{
	NO_CLOCK = 0b11110001,
	SOFTWARE_STROBE = 0b11110011,
	EXTERNAL_POSITIVE_EDGE = 0b11111001
};

int set_clock();
int clock_strobe();

#endif