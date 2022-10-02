/*
 * lf_sensor.h
 *
 * APOS
 * ATMEGA2560
 */ 


#ifndef LF_SENSOR_H_
#define LF_SENSOR_H_

#include "main.h"
#include "adc.h"

#define SENSOR1 PF0
#define SENSOR2 PF1
#define SENSOR3 PF2
#define SENSOR4 PF3
#define SENSOR5 PF4
#define SENSOR6 PF5
#define SENSOR7 PF6

uint8_t sensors_on_black;
uint8_t threshold;			// the threshold value, read by ADC, to determine whether the sensor is reading black or white
uint8_t total_sensors;

void init_lf_sensors(uint8_t threshold_value);
uint8_t read_lf_sensors(void);
void verify_black();


#endif /* LF_SENSOR_H_ */