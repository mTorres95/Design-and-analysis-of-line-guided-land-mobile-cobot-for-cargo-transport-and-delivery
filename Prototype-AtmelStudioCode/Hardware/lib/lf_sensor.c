/*
 * lf_sensor.c
 *
 * APOS
 * ATMEGA2560
 */ 

#include "lf_sensor.h"

void init_lf_sensors(uint8_t threshold_value){
	total_sensors = 7;
	init_adc();
	threshold = threshold_value;
}

uint8_t read_lf_sensors(){
	sensors_on_black = 0;
	for (int sensor_nb=0; sensor_nb<total_sensors;sensor_nb++){
		if (read_AD_channel(sensor_nb) > threshold)		sensors_on_black |= (1<<sensor_nb);
	}
	return sensors_on_black;
}

void verify_black(){
	uint8_t sensors_on_black = read_lf_sensors();
	for (int sensor_nb=0; sensor_nb<total_sensors;sensor_nb++){
		if (sensors_on_black & (1<<sensor_nb)) lcd_print("|1");
		else lcd_print("|0");
	}
	lcd_print("|");
	
}