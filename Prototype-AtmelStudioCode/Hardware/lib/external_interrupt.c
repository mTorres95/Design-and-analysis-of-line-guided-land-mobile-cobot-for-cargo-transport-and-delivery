/*
 * external_interrupt.c
 *
 * ATMEGA2560
 */ 

#include "external_interrupt.h"

void configuracion_INT0(int0_evento evento)
{
	// INT0 como entrada
	DDRD  &=~ (1<<DDD0);
	// Configuracion del tipo de evento que levanta el flag de interrupcion
	EICRA &=~ (3<<ISC00);
	EICRA |=  (evento<<ISC00);
	// Apagado del flag
	EIFR  |=  (1<<INTF0);
	// Habilitar interrupciones en INT0
	EIMSK |=  (1<<INT0);
}

void configuracion_INT1(int1_evento evento)
{
	// INT1 como entrada
	DDRD  &=~ (1<<DDD1);
	// Configuracion del tipo de evento que levanta el flag de interrupcion
	EICRA &=~ (3<<ISC10);
	EICRA |=  (evento<<ISC10);
	// Apagado del flag
	EIFR  |=  (1<<INTF1);
	// Habilitar interrupciones en INT0
	EIMSK |=  (1<<INT1);
}

void configuracion_INT2(int2_evento evento)
{
	// INT2 como entrada
	DDRD  &=~ (1<<DDD2);
	// Configuracion del tipo de evento que levanta el flag de interrupcion
	EICRA &=~ (3<<ISC20);
	EICRA |=  (evento<<ISC20);
	// Apagado del flag
	EIFR  |=  (1<<INTF2);
	// Habilitar interrupciones en INT0
	EIMSK |=  (1<<INT2);
}

// Rutina de servicio interrupcion externa INT0
ISR(INT0_vect)
{
	
	// Apagado del flag
	EIFR  |=  (1<<INTF0);
	
}

// Rutina de interrupcion externa INT1
ISR(INT1_vect)
{	
	
	// Apagado del flag
	EIFR |= (1<<INTF1);
}

// Rutina de interrupcion externa INT2
ISR(INT2_vect)
{
	
	// Apagado del flag
	EIFR |= (1<<INTF2);
}