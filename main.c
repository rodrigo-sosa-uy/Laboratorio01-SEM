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

///////////////////////////// Librerías /////////////////////////////
#include <avr/io.h>
#include <util/delay.h>
/////////////////////////////////////////////////////////////////////

/////////////////////////// Definiciones ////////////////////////////
#define HUM1 PORTC0

#define BUT1 PORTD2
#define BUT2 PORTD3
#define BUT3 PORTD5
#define BUT4 PORTD3
#define BUT_PORT PIND

#define REL1 PORTD6
/////////////////////////////////////////////////////////////////////

int main(void){
	// Define entradas y salidas
    DDRB = 0xFF;
	DDRC = 0x00;
	DDRD = 0x40;
	
	// Habilita Pull-up interno
	PORTD = ((1 << BUT1) | (1 << BUT2) | (1 << BUT3) | (1 << BUT4));
		
	// Variables
	uint16_t humedad;
	
    while(1){

    }
}