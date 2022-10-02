/*
 * timers.c
 *
 *  Author: miact
 */ 
#include "timers.h"

// ======================= TIMER 0 =============================
// ====================== END TIMER 0 ==========================

// ======================= TIMER 1 =============================
void output_setting_timer1(){
	// Configuracion de salidas
	DDRB |= (1<<DDB5)|(1<<DDB6)|(1<<DDB7);		// Salida en OC1A, OC1B y OC1C
}

void set_mode_timer1(uint8_t modo){
	printf("TIMER 1 en modo %d\r\n", modo);
	// Resetear a 0 los bits de configuracion de modo
	TCCR1A &=~ (3<<WGM10);  // 3 -> 0b11
	TCCR1B &=~ (3<<WGM12);
	
	switch(modo){
		case 0: // 0 0 0 0
			break;
		case 1: // 0 0 0 1
			TCCR1A |=  (1<<WGM10);
			break;
		case 2: // 0 0 1 0
			TCCR1A |=  (1<<WGM11);
			break;
		case 3: // 0 0 1 1
			TCCR1A |=  (3<<WGM10);
			break;
		case 4: // 0 1 0 0
			TCCR1B |=  (1<<WGM12);
			break;
		case 5: // 0 1 0 1
			TCCR1A |=  (1<<WGM10);
			TCCR1B |=  (1<<WGM12);
			break;
		case 6: // 0 1 1 0
			TCCR1A |=  (1<<WGM11);
			TCCR1B |=  (1<<WGM12);
			break;
		case 7: // 0 1 1 1
			TCCR1A |=  (3<<WGM10);
			TCCR1B |=  (1<<WGM12);
			break;
		case 8: // 1 0 0 0
			TCCR1B |=  (1<<WGM13);
			break;
		case 9: // 1 0 0 1
			TCCR1A |=  (1<<WGM10);
			TCCR1B |=  (1<<WGM13);
			break;
		case 10: // 1 0 1 0
			TCCR1A |=  (1<<WGM11);
			TCCR1B |=  (1<<WGM13);
			break;
		case 11: // 1 0 1 1
			TCCR1A |=  (3<<WGM10);
			TCCR1B |=  (1<<WGM13);
			break;
		case 12: // 1 1 0 0
			TCCR1B |=  (3<<WGM12);
			break;
		case 14: // 1 1 1 0
			TCCR1A |=  (1<<WGM11);
			TCCR1B |=  (3<<WGM12);
			break;
		case 15: // 1 1 1 1
			TCCR1A |=  (3<<WGM10);
			TCCR1B |=  (3<<WGM12);
			break;
		default:
			printf("Invalid mode\r\n");
			break;	
	}
}


void set_prescaler_timer1(uint16_t prescaler){
	printf("TIMER 1 with prescaler -> %d\r\n", prescaler);
	// Resetear a 0 los bits de configuracion del prescaler
	TCCR1B &=~ (7<<CS10);  // 7 -> 0b111
	
	switch(prescaler){
		case 0:
			printf("Timer 1 off\r\n");
			break;
		case 1:			// 0 0 1
			TCCR1B |= (1<<CS10);
			break;
		case 8:			// 0 1 0
			TCCR1B |= (1<<CS11);
			break;
		case 64:		// 0 1 1
			TCCR1B |= (3<<CS10);
			break;
		case 256:		// 1 0 0
			TCCR1B |= (1<<CS12);
			break;
		case 1024:		// 1 0 1
			TCCR1B |= (1<<CS10)|(1<<CS12);
			break;
		default:
			printf("Prescaler invalido. Can't initialize TIMER 1\r\n");
			break;	
	}
}


void select_prescaler_ms_timer1(float T){	//[ms]
	prescaler_TC1 = 0;
	T = T/1000.0;		// pasa a [seg]
	float aux = (float)(pow(2, 16)/F_CPU);	// tiempo maximo con prescaler=1 para Timer de 16 bits
	if		(T <=      aux) prescaler_TC1 = 1;
	else if (T <=    8*aux) prescaler_TC1 = 8;
	else if (T <=   64*aux) prescaler_TC1 = 64;
	else if (T <=  256*aux) prescaler_TC1 = 256;
	else if (T <= 1024*aux) prescaler_TC1 = 1024;
	else printf("Tiempo fuera de rango!\r\n");
	
	set_prescaler_timer1(prescaler_TC1);
}


void  set_outputMode_timer1(uint8_t outA, uint8_t outB, uint8_t outC){
	// Resetear a 0 los bits de configuracion de los modos de salida
	TCCR1A &=~ (3<<COM1A0)|(3<<COM1B0);
	
	switch(outA){
		case 0: // 0 0
			printf("OC1A modo Off\r\n");
			break;
		case 1: // 0 1
			printf("OC1A modo Toggle\r\n");
			TCCR1A |= (1<<COM1A0);
			break;
		case 2: // 1 0
			printf("OC1A modo Clear\r\n");
			TCCR1A |= (2<<COM1A0);
			break;
		case 3: // 1 1
			printf("OC1A modo Set\r\n");
			TCCR1A |= (3<<COM1A0);
			break;
		default:
			printf("Salida OC1A invalida\r\n");
			break;	
	}
	
	switch(outB){
		case 0: // 0 0
		printf("OC1B modo Off\r\n");
		break;
		case 1: // 0 1
		printf("OC1B modo Toggle\r\n");
		TCCR1A |= (1<<COM1B0);
		break;
		case 2: // 1 0
		printf("OC1B modo Clear\r\n");
		TCCR1A |= (2<<COM1B0);
		break;
		case 3: // 1 1
		printf("OC1B modo Set\r\n");
		TCCR1A |= (3<<COM1B0);
		break; 
		default:
		printf("Salida OC1B invalida\r\n");
		break;
	}
	
	switch(outC){
		case 0: // 0 0
		printf("OC1C modo Off\r\n");
		break;
		case 1: // 0 1
		printf("OC1C modo Toggle\r\n");
		TCCR1A |= (1<<COM1C0);
		break;
		case 2: // 1 0
		printf("OC1C modo Clear\r\n");
		TCCR1A |= (2<<COM1C0);
		break;
		case 3: // 1 1
		printf("OC1C modo Set\r\n");
		TCCR1A |= (3<<COM1C0);
		break;
		default:
		printf("Salida OC1C invalida\r\n");
		break;
	}
	
}


void set_interrupt_timer1(uint8_t inputCapt, uint8_t outputCaptA,
							uint8_t outputCaptB, uint8_t outputCaptC,
							uint8_t overflow){
	// Input Capture
	if(inputCapt){
		TIFR1  |= (1<<ICF1);	// apaga el flag (se apagan con 1)
		TIMSK1 |= (1<<ICIE1);	// habilita la interrupcion
	}
	if(outputCaptA){
		TIFR1  |= (1<<OCF1A);	// apaga el flag (se apagan con 1)
		TIMSK1 |= (1<<OCIE1A);	// habilita la interrupcion
	}
	if(outputCaptB){
		TIFR1  |= (1<<OCF1B);	// apaga el flag (se apagan con 1)
		TIMSK1 |= (1<<OCIE1B);	// habilita la interrupcion
	}
	
	if(outputCaptC){
		TIFR1  |= (1<<OCF1C);	// apaga el flag (se apagan con 1)
		TIMSK1 |= (1<<OCIE1C);	// habilita la interrupcion
	}
	if(overflow){
		TIFR1  |= (1<<TOV1);	// apaga el flag (se apagan con 1)
		TIMSK1 |= (1<<TOIE1);	// habilita la interrupcion
	}
}

void set_ICR1_TOP(float period_ms){
	ICR1 = (uint16_t)( ((period_ms/1000.0)*(F_CPU/prescaler_TC1))+1 );
}

void set_OCR1(uint16_t OCR1A_val, uint16_t OCR1B_val, uint16_t OCR1C_val){
	if((OCR1A_val>=0))	OCR1A = OCR1A_val;
	if((OCR1B_val>=0))	OCR1B = OCR1B_val;
	if((OCR1C_val>=0))	OCR1C = OCR1C_val;
}

// ====================== END TIMER 1 ==========================

// ======================= TIMER 3 =============================
void output_setting_timer3(){
	// Configuracion de salidas
	DDRE |= (1<<DDE3)|(1<<DDE4)|(1<<DDE5);		// Salida en OC3A, OC3B y OC3C
}

void set_mode_timer3(Timer16b_modo modo){
	printf("TIMER 3 en modo %d\r\n", modo);
	// Resetear a 0 los bits de configuracion de modo
	TCCR3A &=~ (3<<WGM10);  // 3 -> 0b11
	TCCR3B &=~ (3<<WGM12);
	
	switch(modo){
		case 0: // 0 0 0 0
			break;
		case 1: // 0 0 0 1
			TCCR3A |=  (1<<WGM30);
			break;
		case 2: // 0 0 1 0
			TCCR3A |=  (1<<WGM31);
			break;
		case 3: // 0 0 1 1
			TCCR3A |=  (3<<WGM30);
			break;
		case 4: // 0 1 0 0
			TCCR3B |=  (1<<WGM32);
			break;
		case 5: // 0 1 0 1
			TCCR3A |=  (1<<WGM30);
			TCCR3B |=  (1<<WGM32);
			break;
		case 6: // 0 1 1 0
			TCCR3A |=  (1<<WGM31);
			TCCR3B |=  (1<<WGM32);
			break;
		case 7: // 0 1 1 1
			TCCR3A |=  (3<<WGM30);
			TCCR3B |=  (1<<WGM32);
			break;
		case 8: // 1 0 0 0
			TCCR3B |=  (1<<WGM33);
			break;
		case 9: // 1 0 0 1
			TCCR3A |=  (1<<WGM30);
			TCCR3B |=  (1<<WGM33);
			break;
		case 10: // 1 0 1 0
			TCCR3A |=  (1<<WGM31);
			TCCR3B |=  (1<<WGM33);
			break;
		case 11: // 1 0 1 1
			TCCR3A |=  (3<<WGM30);
			TCCR3B |=  (1<<WGM33);
			break;
		case 12: // 1 1 0 0
			TCCR3B |=  (3<<WGM32);
			break;
		case 13: // 1 1 0 1
			TCCR3A |=  (1<<WGM30);
			TCCR3B |=  (3<<WGM32);
			break;
		case 14: // 1 1 1 0
			TCCR3A |=  (1<<WGM31);
			TCCR3B |=  (3<<WGM32);
			break;
		case 15: // 1 1 1 1
			TCCR3A |=  (3<<WGM30);
			TCCR3B |=  (3<<WGM32);
			break;
		default:
			printf("Mode invalid\r\n");
			break;
	}
}

void set_prescaler_timer3(uint16_t prescaler){
	printf("TIMER 3 with prescaler -> %d\r\n", prescaler);
	// Resetear a 0 los bits de configuracion del prescaler
	TCCR3B &=~ (7<<CS30);  // 7 -> 0b111
	
	switch(prescaler){
		case 0:
		printf("Timer 3 off\r\n");
		break;
		case 1:			// 0 0 1
		TCCR3B |= (1<<CS30);
		break;
		case 8:			// 0 1 0
		TCCR3B |= (1<<CS31);
		break;
		case 64:		// 0 1 1
		TCCR3B |= (3<<CS30);
		break;
		case 256:		// 1 0 0
		TCCR3B |= (1<<CS32);
		break;
		case 1024:		// 1 0 1
		TCCR3B |= (1<<CS30)|(1<<CS32);
		break;
		default:
		printf("Prescaler invalid. Can't initialize TIMER 3\r\n");
		break;
	}
}

void select_prescaler_ms_timer3(float T){	//[ms]
	prescaler_TC3 = 0;
	T = T/1000.0;		// pasa a [seg]
	float aux = (float)(pow(2, 16)/F_CPU);	// tiempo maximo con prescaler=1 para Timer de 16 bits
	if		(T <=      aux) prescaler_TC3 = 1;
	else if (T <=    8*aux) prescaler_TC3 = 8;
	else if (T <=   64*aux) prescaler_TC3 = 64;
	else if (T <=  256*aux) prescaler_TC3 = 256;
	else if (T <= 1024*aux) prescaler_TC3 = 1024;
	else printf("Tiempo fuera de rango!\r\n");
	
	set_prescaler_timer3(prescaler_TC3);
}

void  set_outputMode_timer3(uint8_t outA, uint8_t outB, uint8_t outC){
	// Resetear a 0 los bits de configuracion de los modos de salida
	TCCR3A &=~ (3<<COM3A0)|(3<<COM3B0);
	
	switch(outA){
		case 0: // 0 0
			printf("OC3A modo Off\r\n");
			break;
		case 1: // 0 1
			printf("OC3A modo Toggle\r\n");
			TCCR3A |= (1<<COM3A0);
			break;
		case 2: // 1 0
			printf("OC3A modo Clear\r\n");
			TCCR3A |= (2<<COM3A0);
			break;
		case 3: // 1 1
			printf("OC3A modo Set\r\n");
			TCCR3A |= (3<<COM3A0);
			break;
		default:
			printf("Salida OC3A invalida\r\n");
			break;
	}
	
	switch(outB){
		case 0: // 0 0
			printf("OC3B modo Off\r\n");
			break;
		case 1: // 0 1
			printf("OC3B modo Toggle\r\n");
			TCCR3A |= (1<<COM3B0);
			break;
		case 2: // 1 0
			printf("OC3B modo Clear\r\n");
			TCCR3A |= (2<<COM3B0);
			break;
		case 3: // 1 1
			printf("OC3B modo Set\r\n");
			TCCR3A |= (3<<COM3B0);
			break;
		default:
			printf("Salida OC3B invalida\r\n");
			break;
	}
	
	switch(outC){
		case 0: // 0 0
			printf("OC3C modo Off\r\n");
			break;
		case 1: // 0 1
			printf("OC3C modo Toggle\r\n");
			TCCR3A |= (1<<COM3C0);
			break;
		case 2: // 1 0
			printf("OC3C modo Clear\r\n");
			TCCR3A |= (2<<COM3C0);
			break;
		case 3: // 1 1
			printf("OC3C modo Set\r\n");
			TCCR3A |= (3<<COM3C0);
			break;
		default:
			printf("Salida OC3C invalida\r\n");
			break;
	}
	
}


void set_interrupt_timer3(uint8_t inputCapt, uint8_t outputCaptA,
										uint8_t outputCaptB, uint8_t outputCaptC,
										uint8_t overflow){
	// Input Capture
	if(inputCapt){
		TIFR3  |= (1<<ICF3);	// apaga el flag (se apagan con 1)
		TIMSK3 |= (1<<ICIE3);	// habilita la interrupcion
	}
	if(outputCaptA){
		TIFR3  |= (1<<OCF3A);	// apaga el flag (se apagan con 1)
		TIMSK3 |= (1<<OCIE3A);	// habilita la interrupcion
	}
	if(outputCaptB){
		TIFR3  |= (1<<OCF3B);	// apaga el flag (se apagan con 1)
		TIMSK3 |= (1<<OCIE3B);	// habilita la interrupcion
	}
	
	if(outputCaptC){
		TIFR3  |= (1<<OCF3C);	// apaga el flag (se apagan con 1)
		TIMSK3 |= (1<<OCIE3C);	// habilita la interrupcion
	}
	if(overflow){
		TIFR3  |= (1<<TOV3);	// apaga el flag (se apagan con 1)
		TIMSK3 |= (1<<TOIE3);	// habilita la interrupcion
	}
}

void set_ICR3_TOP(float period_ms){
	ICR3 = (uint16_t)( ((period_ms/1000.0)*(F_CPU/prescaler_TC3))+1 );
}

void set_OCR3(uint16_t OCR3A_val, uint16_t OCR3B_val, uint16_t OCR3C_val){
	if((OCR3A_val>=0))	OCR3A = OCR3A_val;
	if((OCR3B_val>=0))	OCR3B = OCR3B_val;
	if((OCR3C_val>=0))	OCR3C = OCR3C_val;
}
// ====================== END TIMER 3 ==========================