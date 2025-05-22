#include "display.h"

void display_mode(){
	twi_lcd_msg("----M:");
	if(estado == OFF){
		twi_lcd_msg("OFF");
	} else{
		twi_lcd_msg("ON ");
	}
}

void display_riego(){
	if(estado == ON){
		twi_lcd_msg(" Riego:");
		if(t_riego == 0){
			twi_lcd_msg("1hr");
		} else if(t_riego == 1){
			twi_lcd_msg("3hrs");
		} else{
			twi_lcd_msg("5hrs");
		}
	}
}

void display_valve(){
	if(estado == ON){
		twi_lcd_msg("Vlv:");
		if(t_riego == 0){
			twi_lcd_msg("10s");
		} else if(t_riego == 1){
			twi_lcd_msg("15s");
		} else{
			twi_lcd_msg("20s");
		}
	}
}

void display_humedad(){
	if(estado == ON){
		twi_lcd_msg("-Hmin:");
		if(t_riego == 0){
			twi_lcd_msg("20%");
		} else if(t_riego == 1){
			twi_lcd_msg("30%");
		} else{
			twi_lcd_msg("40%");
		}
		//LCD_Char('-');
		//LCD_Char(humedad);
		//LCD_Char('%');
	}
}

void trigger_lcd(){
	twi_lcd_clear();

	twi_lcd_cmd(0x80);				//--- Row 1 Column 1 Address
	display_mode();
	display_riego();
	twi_lcd_cmd(0xC0);				//--- Row 2 Column 1 Address
	display_valve();
	display_humedad();
}