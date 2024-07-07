#include "adc.h"
#include <avr/io.h>        

void configure_ADC(struct adc_config* adc_config){
    // set voltage reference
    ADMUX &= adc_config->voltage_reference;
    // set the result adjustment
    ADMUX |= adc_config->adjustment;
    // select the ADC mux
    ADMUX &= adc_config->mux_select;
    // enable the ADC
    if(adc_config->enable == 1){
        ADCSRA |= 0b10000000;
    }
    if(adc_config->start_conversion == 1){
        ADCSRA |= 0b01000000;
    }

}