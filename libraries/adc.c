#include "adc.h"

void ADC_init(){
	// Configurar referencia de voltaje a AVCC con capacitor de desacoplo
	ADMUX |= (1 << REFS0);
	// Habilitar el ADC y configurar el prescaler a 128 para un rango de 0-5V
	ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t ADC_read(uint8_t channel){
	// Seleccionar el canal de entrada
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
	
	// Iniciar la conversi?n
	ADCSRA |= (1 << ADSC);
	
	// Esperar a que la conversi?n se complete
	while (ADCSRA & (1 << ADSC));
	
	return ADC;
}