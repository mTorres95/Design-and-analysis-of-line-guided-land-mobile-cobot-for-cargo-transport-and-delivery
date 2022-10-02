/*
 * dc_motor.h
 *
 * APOS
 * ATMEGA2560
 */ 


#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "timers.h"

float T_ms;

void init_dc_motor(float period);
void stop();
void move_forward();
void reduce_right();
void reduce_left();
void turn_clockwise();
void turn_anticlockwise();
void move_backward();

#endif /* DC_MOTOR_H_ */