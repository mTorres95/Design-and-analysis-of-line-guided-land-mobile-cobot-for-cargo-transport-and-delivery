/*
 * timers.h
 *
 *  Author: miact
 */ 

// Para ATMega2560, que cuenta con 2 timers de 8 bits (TIMER O y TIMER 2)
// y cuatro timers de 16 bits (TIMER 1, TIMER 3, TIMER 4 Y TIMER 5).
// Los 6 timers cuentan con prescaler y modo de Comparacion. 
// Los Timers de 16 bits (TC1, TC3, TC4 y TC5) traen ademas modo de Captura

#ifndef TIMERS_H_
#define TIMERS_H_

#include "main.h"

typedef enum
{	Normal			= 0,
	PWM_PCx_8b		= 1,
	PWM_PCx_9b		= 2,
	PWM_PCx_10b		= 3,
	CTC_OCR1A		= 4,
	FAST_PWMx_8b	= 5,
	FAST_PWMx_9b	= 6,
	FAST_PWMx_10b	= 7,
	PWM_PyFC_ICRx	= 8,
	PWM_PyFC_OCRxA	= 9,
	PWM_PC_ICRx		= 10,
	PWM_PC_OCRxA	= 11,
	CTC_ICRx		= 12,
	Reservado		= 13,
	FAST_PWM_ICRx	= 14,
	FAST_PWM_OCRxA	= 15
}Timer16b_modo; // Tipo modos de trabajo para timers de 16 bits

// Funciones y variables del timer 1 (16 bits)
uint16_t prescaler_TC1;
void output_setting_timer1();
void set_mode_timer1(Timer16b_modo modo_0a14);
void set_prescaler_timer1(uint16_t prescaler);
void select_prescaler_ms_timer1(float ms);
void set_outputMode_timer1(uint8_t outA, uint8_t outB, uint8_t outC);
void set_interrupt_timer1(uint8_t inputCapt, uint8_t outputCaptA, uint8_t outputCaptB, uint8_t outputCaptC, uint8_t overflow);
void set_ICR1_TOP(float period_ms);
void set_OCR1(uint16_t OCR1A_val, uint16_t OCR1B_val, uint16_t OCR1C_val);

// Funciones y variables del timer 3 (16 bits)
uint16_t prescaler_TC3;
void output_setting_timer3();
void set_mode_timer3(Timer16b_modo modo_0a14);
void set_prescaler_timer3(uint16_t prescaler);
void select_prescaler_ms_timer3(float ms);
void set_outputMode_timer3(uint8_t outA, uint8_t outB, uint8_t outC);
void set_interrupt_timer3(uint8_t inputCapt, uint8_t outputCaptA, uint8_t outputCaptB, uint8_t outputCaptC, uint8_t overflow);
void set_ICR3_TOP(float period_ms);
void set_OCR3(uint16_t OCR3A_val, uint16_t OCR3B_val, uint16_t OCR3C_val);


#endif /* TIMERS_H_ */