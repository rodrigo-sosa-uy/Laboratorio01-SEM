////////////////////////////////////////////////////////////
//           Laboratorio 01: Sistemas embebidos           //
//              Fecha de entrega: 23/05/2025              //
//   Rodrigo Sosa, Mercedes Rodriguez, Francisco Ojeda    //
////////////////////////////////////////////////////////////
	//  Sensor   |   Tipo    |  ID  | Pin | PORTXx  //
	//  Humedad  |  Analog   | HUM1 | A0  | PORTC0  //
	//  Boton_1  |  Digital  | BUT1 | D2  | PORTD2  //
	//  Boton_2  |  Digital  | BUT2 | D3  | PORTD3  //
	//  Boton_3  |  Digital  | BUT3 | D4  | PORTD4  //
	//  Boton_4  |  Digital  | BUT4 | D5  | PORTD5  //
	//////////////////////////////////////////////////
	//  Actuador |  Usage    |  ID  | Pin | PORTXx  //
	//  Relay    |  IN1      | REL1 | D6  | PORTD6  //
	//  LCD_Data |  LCD_D7   | LCD1 | D8  | PORTB0  //
	//  LCD_Data |	LCD_D6   | LCD2 | D9  | PORTB1  //
	//  LCD_Data |	LCD_D5   | LCD3 | D10 | PORTB2  //
	//  LCD_Data |	LCD_D4   | LCD4 | D11 | PORTB3  //
	//  LCD_Ctrl |	LCD_EN   | LCEN | D12 | PORTB4  //
	//  LCD_Ctrl |	LCD_RS   | LCRS | D13 | PORTB5  //
	//////////////////////////////////////////////////

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

/////////////////////////// Definiciones ////////////////////////////
#define HUM1 PORTC0

#define BUT1 PORTD2
#define BUT2 PORTD3
#define BUT3 PORTD4
#define BUT4 PORTD5
#define BUT_PORT PIND

#define PCF8574	0x27
#define LCD_DATA_PORT PORTB // Puerto de datos del LCD (DB4-DB7)
#define LCD_CTRL_PORT PORTB // Puerto de control del LCD (RS, EN)
#define D4 PORTB3
#define D5 PORTB2
#define D6 PORTB1
#define D7 PORTB0
#define LCD_EN PORTB4
#define LCD_RS PORTB5

#define REL1 PORTD6
/////////////////////////////////////////////////////////////////////

///////////////////////////// Variables /////////////////////////////
uint8_t humedad;

uint16_t cnt_tiempo_riego = 0;
uint16_t cnt_tiempo_valve = 0;
uint16_t cnt_trigg_lcd = 0;
/////////////////////////////////////////////////////////////////////

///////////////////////// Modos y estados ///////////////////////////
typedef enum{
	OFF,
	ON
} STATE;

STATE estado = OFF;

uint8_t t_riego = 0;	// (0: 1hr, 1: 3hrs, 2: 5hrs)
uint8_t t_valve = 0;	// (0: 10s, 1: 15s, 2: 20s)
uint8_t hum_min = 0;	// (0: 20%, 1: 30%, 2: 40%)
/////////////////////////////////////////////////////////////////////

///////////////////////////// Librerias /////////////////////////////
#include "libraries/lcd_i2c.h"
#include "libraries/adc.h"
#include "libraries/configure.h"
#include "libraries/controller.h"
#include "libraries/display.h"
/////////////////////////////////////////////////////////////////////

//////////////////////// Maquina de estados /////////////////////////
void F_OFF();
void F_ON();

typedef struct{
	void (*func)();
} FSM;

FSM SMHRA[] = {	// Sistema de Monitoreo de Humedad y Riego Automatico
	{F_OFF},
	{F_ON}
};
/////////////////////////////////////////////////////////////////////

///////////////////////////// Banderas //////////////////////////////
uint8_t off_fg = 1;
uint8_t on_fg = 1;
/////////////////////////////////////////////////////////////////////

void F_OFF(){
	_delay_ms(100);
	if(off_fg){
		//Serial.println("Modo OFF");
		//Serial.flush();
		trigger_lcd();
		off_fg = 0;
	}
	
	if((BUT_PORT & (1 << BUT1)) == 0){
		estado = ON;
		off_fg = 1;
		_delay_ms(100);
	}
}

void F_ON(){
	_delay_ms(100);
	if(on_fg || (cnt_trigg_lcd >= 200)){
		//Serial.println("Modo ON");
		//Serial.flush();
		trigger_lcd();
		on_fg = 0;
		cnt_trigg_lcd = 0;
	}

	humedad = map_ph(ADC_read(HUM1));
	
	trigger_riego();
	//trigger_humedad(); para que no triggeree por detectar poca humedad
	
	t_riego = config_t_riego(t_riego);
	t_valve = config_t_valve(t_valve);
	hum_min = config_hum_min(hum_min);

	cnt_trigg_lcd += 1;
	
	if((BUT_PORT & (1 << BUT1)) == 0){
		estado = OFF;
		cnt_tiempo_valve = 0;
		cnt_tiempo_riego = 0;
		on_fg = 1;
		_delay_ms(100);
	}
}

int main(void){
	//Serial.begin(9600);

	// Define entradas y salidas
	DDRB = 0xFF;
	DDRC = 0x00;
	DDRD = 0x40;
	
	// Habilita Pull-up interno
	PORTD = ((1 << BUT1) | (1 << BUT2) | (1 << BUT3) | (1 << BUT4));
	
	// Inicializa el ADC
	ADC_init();

	// Inicializa el display
	twi_init();								
	twi_lcd_init();								
	
	while(1){
		(*SMHRA[estado].func)();
	}
}