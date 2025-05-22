#include "display.h"

void display_mode(){
	//lcd.print("M:");
	if(estado == OFF){
		//lcd.print("OFF");
	} else{
		//lcd.print("ON");
	}
}

void display_riego(){
	if(estado == ON){
		//lcd.print("-Riego:");
		if(t_riego == 0){
			//lcd.print("1hr");
		} else if(t_riego == 1){
			//lcd.print("3hrs");
		} else{
			//lcd.print("5hrs");
		}
	}
}

void display_valve(){
	if(estado == ON){
		//lcd.print("Valv:");
		if(t_riego == 0){
			//lcd.print("10s");
		} else if(t_riego == 1){
			//lcd.print("15s");
		} else{
			//lcd.print("20s");
		}
	}
}

void display_humedad(){
	if(estado == ON){
		//lcd.print("-Hmin:");
		if(t_riego == 0){
			//lcd.print("20%");
		} else if(t_riego == 1){
			//lcd.print("30%");
		} else{
			//lcd.print("40%");
		}
		//LCD_Char('-');
		//LCD_Char(humedad);
		//LCD_Char('%');
	}
}

void trigger_lcd(){
	//lcd.clear();

	//lcd.setCursor(0,0);
	display_mode();
	display_riego();
	//lcd.setCursor(0,1);
	display_valve();
	display_humedad();
}