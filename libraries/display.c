#include "display.h"

// Comando base para establecer dirección DDRAM
#define LCD_SET_DDRAM 0x80

// Direcciones de inicio para cada línea en LCD 20x4
#define LINE1_START 0x00   // Primera línea
#define LINE2_START 0x40   // Segunda línea
#define LINE3_START 0x14   // Tercera línea
#define LINE4_START 0x54   // Cuarta línea

void LCD_PulseEnable(void) {
	PORTB |= (1<<EN);
	_delay_us(1);
	PORTB &= ~(1<<EN);
	_delay_us(100);
}

void LCD_SendNibble(unsigned char nibble) {
	// Limpiar los bits de datos
	PORTB &= ~((1<<D4) | (1<<D5) | (1<<D6) | (1<<D7));
	
	// Establecer los bits según el nibble
	if(nibble & 0x01) PORTB |= (1<<D7);
	if(nibble & 0x02) PORTB |= (1<<D6);
	if(nibble & 0x04) PORTB |= (1<<D5);
	if(nibble & 0x08) PORTB |= (1<<D4);
	
	LCD_PulseEnable();
}

void LCD_Command(unsigned char cmd) {
	// Enviar nibble alto
	LCD_SendNibble(cmd >> 4);
	// Enviar nibble bajo
	LCD_SendNibble(cmd & 0x0F);
	
	// Comandos que necesitan más tiempo
	if(cmd == 0x01 || cmd == 0x02){
		_delay_ms(2);
		} else{
		_delay_us(100);
	}
}

void LCD_Char(unsigned char data) {
	// RS alto para datos
	PORTB |= (1<<RS);
	
	// Enviar nibble alto
	LCD_SendNibble(data >> 4);
	// Enviar nibble bajo
	LCD_SendNibble(data & 0x0F);
	
	// RS bajo para comandos
	PORTB &= ~(1<<RS);
	
	_delay_us(100);
}

void LCD_String(const char *str) {
	while(*str) {
		LCD_Char(*str++);
	}
}

void LCD_Init(void) {
	// Configurar pines como salida
	DDRB |= (1<<D4) | (1<<D5) | (1<<D6) | (1<<D7) | (1<<EN) | (1<<RS);
	
	// Esperar a que el LCD se inicialice
	_delay_ms(50);
	
	// Secuencia de inicialización en modo 4 bits
	PORTB = (PORTB & 0xC3) | (1<<D5); // 0x03 -> 0011 (solo D5 y D4)
	LCD_PulseEnable();
	_delay_ms(5);
	LCD_PulseEnable();
	_delay_us(100);
	LCD_PulseEnable();
	_delay_us(100);
	
	// Configurar modo 4 bits
	LCD_SendNibble(0x02);
	_delay_us(100);
	
	// Configurar LCD: 4 líneas, fuente 5x8 (aunque físicamente son 2 líneas con breaks)
	// Para LCD 20x4 usamos el comando 0x28 (2 líneas) ya que internamente está dividido
	LCD_Command(0x28);
	// Display ON, cursor OFF, blink OFF
	LCD_Command(0x0C);
	// Limpiar display
	LCD_Command(0x01);
	_delay_ms(2);
	// Modo de entrada: incrementar, no desplazar
	LCD_Command(0x06);
}

void LCD_SetCursor(uint8_t row, uint8_t col) {
	const uint8_t LCD_LINE_OFFSETS[] = {LINE1_START, LINE2_START, LINE3_START, LINE4_START};
	
	// Asegurarse que la fila y columna estén dentro de los límites
	if(row > 3) row = 3;
	if(col > 19) col = 19;
	
	// Enviar comando para establecer la posición del cursor
	LCD_Command(LCD_SET_DDRAM | (col + LCD_LINE_OFFSETS[row]));
}

void LCD_Clear() {
	LCD_Command(0x01);  // Envía el comando de limpieza (0x01)
	_delay_ms(2);       // Espera 2ms (tiempo requerido por el datasheet)
}

void display_mode(){
	LCD_String("Modo: ");
	if(estado == OFF){
		LCD_String("OFF");
	} else{
		LCD_String("ON");
	}
}

void display_riego(){
	if(estado == ON){
		LCD_String("Riego:");
		if(t_riego == 0){
			LCD_String("1 hora");
		} else if(t_riego == 1){
			LCD_String("3 horas");
		} else{
			LCD_String("5 horas");
		}
	}
}

void display_valve(){
	if(estado == ON){
		LCD_String("Valvula:");
		if(t_riego == 0){
			LCD_String("10 seg");
			} else if(t_riego == 1){
			LCD_String("15 seg");
			} else{
			LCD_String("20 seg");
		}
	}
}

void display_humedad(){
	if(estado == ON){
		LCD_String("HumMin:");
		if(t_riego == 0){
			LCD_String("20%");
			} else if(t_riego == 1){
			LCD_String("30%");
			} else{
			LCD_String("40%");
		}
		LCD_Char('-');
		LCD_Char(humedad);
		LCD_Char('%');
	}
}

void trigger_lcd(){
	LCD_Clear();

	LCD_SetCursor(0,0);
	display_mode();
	LCD_SetCursor(1,0);
	display_riego();
	LCD_SetCursor(2,0);
	display_valve();
	LCD_SetCursor(3,0);
	display_humedad();
}