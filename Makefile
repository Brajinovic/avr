# makefile, R.G, May 03, 2020

MCU=attiny85
F_CPU = 16500000L
CC=avr-gcc
vpath %.c $(src/)
vpath %.o %(src/)
OBJCOPY=avr-objcopy
CFLAGS=-g -mmcu=$(MCU) -Wall -Wstrict-prototypes -Os -mcall-prologues -Isrc/include
SRCS = $(wildcard src/*.c)
OBJS = $(patsubst %c, %o, $(SRCS))
#-------------------
all: main.hex
main.hex : main.o
	$(OBJCOPY) -R .eeprom -O ihex bin/main.o bin/main.hex
main.o : $(OBJS)
	@$(CC) $(CFLAGS) $^ -Wl,-Map,bin/main.map -o bin/$@
%.o : %.c
	@$(CC) $(CFLAGS) $< -c -o $@
#-------------------
help: 
	@echo "Type make or make install"	
#-------------------
install:
	sudo -E env "PATH=$(PATH)" micronucleus --run bin/main.hex	
clean:
	rm -f src/*.o bin/*.map main.hex
#-------------------
