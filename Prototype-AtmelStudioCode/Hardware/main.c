/*
 * Hardware.c
 *
 * APOS
 * ATMEGA2560
 */ 

#include "lib/main.h"


int main(void)
{
	//init_uart0(BAUD,1,1);
	
	uint8_t threshold_lfs = 90;
    init_lf_sensors(threshold_lfs);	
	init_lcd();
	
	init_dc_motor(50);
	
    while (1) 
    {
		line_guidance();
    }
}

