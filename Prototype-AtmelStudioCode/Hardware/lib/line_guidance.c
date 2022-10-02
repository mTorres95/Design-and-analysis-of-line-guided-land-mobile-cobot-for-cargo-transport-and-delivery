/*
 * line_guidance.c
 *
 * APOS
 * ATMEGA2560
 */ 

#include "line_guidance.h"

char state[10] = "lineFollow";
uint8_t cond_1 = 0;
uint8_t cond_2 = 0;
uint8_t cond_3 = 0;
uint8_t turn_count = 0;

void line_guidance(){
	uint8_t sensors_on_black = read_lf_sensors();
	/* LINE FOLLOWING*/
	if (0 == strcmp(state, "lineFollow")) {
		if (sensors_on_black & (1<<SENSOR1) && sensors_on_black & (1<<SENSOR2)) {
			lcd_print("Avanza");
			move_forward();
		}
		if (sensors_on_black & (1<<SENSOR1) && (~sensors_on_black & (1<<SENSOR2))) {
			lcd_print("->");
			reduce_right();
		} 
		if ((~sensors_on_black & (1<<SENSOR1)) && sensors_on_black & (1<<SENSOR2)) {
			lcd_print("<-");
			reduce_left();
		}
		
		// STOP
		if (sensors_on_black & (1<<SENSOR3) && sensors_on_black & (1<<SENSOR7) && (~sensors_on_black & (1<<SENSOR4)) ) {
			lcd_print("Frenar");
			strcpy(state,"stop");
			//stop();
		}
		
		// TURN
		if (sensors_on_black & (1<<SENSOR3) && sensors_on_black & (1<<SENSOR4) && sensors_on_black & (1<<SENSOR7)) {
			lcd_print("Turn");
			strcpy(state,"turn");
			cond_1 = 0;
			cond_2 = 0;
			cond_3 = 0;
		}
	 /* STOP */
	} else if (0 == strcmp(state, "stop")) {
		lcd_print("Stop");
		stop();
		_delay_ms(1000); // REPLACE WITH TIMER
		lcd_print("End stop");
		
		strcpy(state, "lineFollow");
	/* TURN */
	} else if (0 == strcmp(state, "turn")) {
		if (cond_2 == 0) {
			turn_clockwise();
			lcd_print("Turn");
		}
		if (cond_1 == 0 && (~sensors_on_black & (1<<SENSOR3)) && (~sensors_on_black & (1<<SENSOR4))) {
			cond_1 = 1;
			lcd_print("cond 1");
		}
		if (cond_2 == 0 && cond_1 == 1 && sensors_on_black & (1<<SENSOR5) && (~sensors_on_black & (1<<SENSOR6))) {
			cond_2 = 1;
			lcd_print("cond 2");
		}
		if (cond_3 == 0 && cond_2 == 1 && sensors_on_black & (1<<SENSOR6)) {
			lcd_print("Avanza - cond 3");
			move_forward();
			cond_3 = 1;
		}
		// END OF TURN
		if (cond_3 == 1 && (~sensors_on_black & (1<<SENSOR3))) {
			if (turn_count < 2) {
				turn_count++;
				lcd_print("Turn count");
			}
			if (turn_count == 2) {
				strcpy(state, "outRoom");
				lcd_print("outRoom");
				turn_count = 0;
			} else {
				strcpy(state,"lineFollow");
				lcd_print("lineFollow");
			}
		}
	} else if (strcmp(state,"outRoom")) {
		if (sensors_on_black & (1<<SENSOR1) && sensors_on_black & (1<<SENSOR2)) {
			lcd_print("Avanza");
			move_forward();
		}
		if (sensors_on_black & (1<<SENSOR1) && (sensors_on_black & (1<<SENSOR2))) {
			lcd_print("Giro derecha");
			reduce_right();
		}
		if ((~sensors_on_black & (1<<SENSOR1)) && sensors_on_black & (1<<SENSOR2)) {
			lcd_print("Giro izquierda");
			reduce_left();
		}
		if ((~sensors_on_black & (1<<SENSOR1)) && (~sensors_on_black & (1<<SENSOR2)) && sensors_on_black & (1<<SENSOR7)) {
			lcd_print("Avanza especial");
			move_forward();
		}
		if (sensors_on_black & (1<<SENSOR3) || sensors_on_black & (1<<SENSOR4)) {
			strcmp(state,"turn");
			turn_count = 0;
		}
	}
	_delay_ms(1000);
	lcd_write(LCD_INST,CLEAR);
}