#ifndef ADC_H
#define ADC_H


enum references { // Table 17-3, pg 134
    VCC = 0b00111111,
    AREF = 0b01111111,
    INTERNAL11V = 0b10101111,
    RESERVED = 0b11101111,
    INTERNAL256V = 0b11101111,
    INTERNAL256V_BYPASS = 0b11111111
};

enum mux_id {
    // SEI - Single Ended Input
    SEI_PB2 = 0b11111110,
    SEI_PB3 = 0b11111100,
    SEI_PB4 = 0b11111101,
    SEI_PB5 = 0b11110000

    // there are Positive and Negative Differential inputs, 
    // that I will not be implementing right now as I do not need them 
};

struct adc_config{
    enum references voltage_reference;
    int adjustment;
    enum mux_id mux_select;
    int enable;
    int start_conversion;
};

void configure_ADC(struct adc_config*);

#endif