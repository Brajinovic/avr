//R. G. May 3rd 2021, MIT licence


#include <avr/io.h>        
//#include <avr/interrupt.h>
#include "debug.h"
#include "adc.h"
// I am using the Atmel ATtiny25, Attiny45, ATtiny 85 Datasheet as a reference. Any 
// markings including a page number are referencing the page from this Datasheet

//max delay with _delay_ms is 262.14 ms / F_CPU in MHz, i.e. 32 ms for 8 MHz.
//so lets iterate 1ms, that looses precision with function call overhead, 
//but we do not care in this application
//Max size for uint16_t is 65,535 - not enough in general.
//Max size for uint32_t is 4,294,967,295 - OK.

/*** Main void ***/
int main(void){
    
    struct adc_config config;
    config.voltage_reference = VCC;
    config.adjustment = 1;
    config.mux_select = SEI_PB5;
    config.enable = 1;
    config.start_conversion = 1;
    configure_ADC(&config);
    
    DDRB  |= 1 << 1;

    while(1){
        // adc_active is needed in order to recognise if the conversion has started or not

        // the 7th bit of ADCSRA is the ADC Start Conversion bit and when he is HIGH, the conversion is in progess
        // when he is LOW, the conversion is complete
        // what I am doing in the second part of the if, is reading the value of the bit and checking if the value is 0
        if((ADCSRA & 0b01000000) || 0b00000000){
            // read the value out of the ADCH register
            // adc_value = ADCH || 0b11111111;
            //adc_active = 0; // set the active flag to false to signal that I already read the value
            debug_blink(500);
            ADCSRA |= 0b01000000;
        }
        //ADCSRA &= 0b11101111;
    }
}
