/*
 * main.h
 *
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 16000000
#define BAUD 9600

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include <string.h> 
#include "external_interrupt.h"
#include "uart.h"
#include "lcd_16x4.h"
#include "lf_sensor.h"
#include "dc_motor.h"
#include "line_guidance.h"



#endif /* MAIN_H_ */