#ifndef ADC_H
#define ADC_H

#include "adc.c"

void ADC_init();
uint16_t ADC_read(uint8_t channel);

#endif