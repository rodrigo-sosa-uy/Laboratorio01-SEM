#include "configure.h"

uint8_t config_t_riego(uint8_t t_riego){
	if((BUT_PORT & (1 << BUT2)) != 1){
		if(t_riego == 2){
			t_riego = 0;
		} else{
			t_riego += 1;
		}
	}
	return t_riego;
}

uint8_t config_t_valve(uint8_t t_valve){
	if((BUT_PORT & (1 << BUT3)) != 1){
		if(t_valve == 2){
			t_valve = 0;
		} else{
			t_valve += 1;
		}
	}
	return t_valve;
}

uint8_t config_hum_min(uint8_t hum_min){
	if((BUT_PORT & (1 << BUT4)) != 1){
		if(hum_min == 2){
			hum_min = 0;
		} else{
			hum_min += 1;
		}
	}
	return hum_min;
}