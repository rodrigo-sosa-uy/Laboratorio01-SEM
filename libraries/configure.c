#include "configure.h"

uint8_t config_t_riego(uint8_t t_riego){
	if((BUT_PORT & (1 << BUT2)) == 0){
		if(t_riego == 2){
			t_riego = 0;
		} else{
			t_riego += 1;
		}
		//Serial.print("T_Riego:"); Serial.println(t_riego);
		//Serial.flush();
	}
	return t_riego;
}

uint8_t config_t_valve(uint8_t t_valve){
	if((BUT_PORT & (1 << BUT3)) == 0){
		if(t_valve == 2){
			t_valve = 0;
		} else{
			t_valve += 1;
		}
		//Serial.print("T_Valve:"); Serial.println(t_valve);
		//Serial.flush();
	}
	return t_valve;
}

uint8_t config_hum_min(uint8_t hum_min){
	if((BUT_PORT & (1 << BUT4)) == 0){
		if(hum_min == 2){
			hum_min = 0;
		} else{
			hum_min += 1;
		}
		//Serial.print("Hum_Min:"); Serial.println(hum_min);
		//Serial.flush();
	}
	return hum_min;
}