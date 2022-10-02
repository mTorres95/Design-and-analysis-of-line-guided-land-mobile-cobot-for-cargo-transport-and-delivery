/*
 * dc_motor.c
 *
 * APOS
 * ATMEGA2560
 */ 

#include "dc_motor.h"

void init_dc_motor(float period){
	output_setting_timer1();			// Salida en OC1A, OC1B y OC1C
	T_ms = period;							// [ms] periodo del PWM para controlar los servomotores
	set_mode_timer1(FAST_PWM_ICRx);		// Fast PWM con ICR1 como TOP
	select_prescaler_ms_timer1(T_ms);	// Prescaler de acuerdo al periodo requerido
	set_ICR1_TOP(T_ms);
	set_outputMode_timer1(2,2,0);		// Salida OC1A en Clear, OC1B en Clear, OC1C en Clear

	output_setting_timer3();			// Salida en OC3A, OC3B y OC3C
	set_mode_timer3(FAST_PWM_ICRx);		// Fast PWM con ICR3 como TOP
	select_prescaler_ms_timer3(T_ms);	// Prescaler de acuerdo al periodo requerido
	set_ICR3_TOP(T_ms);
	set_outputMode_timer3(2,2,0);		// Salida OC3A en Clear, OC3B en Off, OC3C en Off
}

void set_velocity_left(float velocity){
	if(velocity>0){
		float dutycicleA = T_ms*velocity; //[ms]
		uint16_t OCR1A_val = (uint16_t)( (dutycicleA/1000.0)*(F_CPU/prescaler_TC1)+1 );
		set_OCR1(OCR1A_val,0,-1);
		
	}else if(velocity<0){
		float dutycicleB = T_ms*velocity*(-1); //[ms]
		uint16_t OCR1B_val = (uint16_t)( (dutycicleB/1000.0)*(F_CPU/prescaler_TC1)+1 );
		set_OCR1(0,OCR1B_val,-1);
	}
}

void set_velocity_right(float velocity){
	if(velocity>0){
		float dutycicleA = T_ms*velocity; //[ms]
		uint16_t OCR1A_val = (uint16_t)( (dutycicleA/1000.0)*(F_CPU/prescaler_TC1)+1 );
		set_OCR3(OCR1A_val,0,-1);
		
	} else if(velocity<0){
		float dutycicleB = T_ms*velocity*(-1); //[ms]
		uint16_t OCR3B_val = (uint16_t)( (dutycicleB/1000.0)*(F_CPU/prescaler_TC3)+1 );
		set_OCR3(0,OCR3B_val,-1);
	}
}

void stop(){
	set_velocity_left(0);
	set_velocity_right(0);
}

void turn_clockwise(){
	set_velocity_left(0.5);
	set_velocity_right(-0.5);
}

void turn_anticlockwise(){
	set_velocity_left(-0.5);
	set_velocity_right(0.5);
}

void move_forward(){
	set_velocity_right(1);
	set_velocity_left(1);
}

void reduce_right(){
	set_velocity_right(0.8);
}

void reduce_left(){
	set_velocity_left(0.8);
}

void move_backward(){
	set_velocity_right(-1);
	set_velocity_left(-1);
}