#include "controller.h"

void trigger_valve(){
	if(t_valve == 0){
		if(cnt_tiempo_valve <= 100){ // Para (10seg = 100)
			PORTD |= (1 << REL1);
			} else{
			PORTD &= ~(1 << REL1);
			//Serial.print("Tiempo Riego: "); Serial.println(cnt_tiempo_riego);
			//Serial.print("Tiempo Valve: "); Serial.println(cnt_tiempo_valve);
			//Serial.flush();
			cnt_tiempo_valve = 0;
			cnt_tiempo_riego = 0;
		}
		} else if(t_riego == 1){
		if(cnt_tiempo_valve <= 150){ // Para (15seg = 150)
			PORTD |= (1 << REL1);
			} else{
			PORTD &= ~(1 << REL1);
			cnt_tiempo_valve = 0;
			cnt_tiempo_riego = 0;
		}
		} else{
		if(cnt_tiempo_valve <= 200){ // Para (20seg = 200)
			PORTD |= (1 << REL1);
			} else{
			PORTD &= ~(1 << REL1);
			cnt_tiempo_valve = 0;
			cnt_tiempo_riego = 0;
		}
	}
	cnt_tiempo_valve += 1;
}

void trigger_riego(){
	if(t_riego == 0){
		if(cnt_tiempo_riego >= 100){ // Para (1h = 100ms * 36000) - Para simular (10seg = 100)
			trigger_valve();
			} else{
			PORTD &= ~(1 << REL1);
		}
		} else if(t_riego == 1){
		if(cnt_tiempo_riego >= 150){ // Para (3h = 100ms * 108000) - Para simular (15seg = 150)
			trigger_valve();
			} else{
			PORTD &= ~(1 << REL1);
		}
		} else{
		if(cnt_tiempo_riego >= 200){ // Para (5h = 100ms * 180000) - Para simular (20seg = 200)
			trigger_valve();
			} else{
			PORTD &= ~(1 << REL1);
		}
	}
	cnt_tiempo_riego += 1;
}

void trigger_humedad(){
	if(hum_min == 0){
		if(humedad <= 20){
			trigger_valve();
			} else{
			PORTD &= ~(1 << REL1);
		}
		} else if(hum_min == 1){
		if(humedad <= 30){
			trigger_valve();
			} else{
			PORTD &= ~(1 << REL1);
		}
		} else{
		if(humedad <= 40){
			trigger_valve();
			} else{
			PORTD &= ~(1 << REL1);
		}
	}
}

uint8_t map_ph(uint16_t humedad){
	return (humedad * 100) / 1023;
}