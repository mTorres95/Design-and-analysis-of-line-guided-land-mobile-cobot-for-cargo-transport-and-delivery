/*
 * adc.c
 * APOS
 * ATMEGA2560
 * Autor: Jord�n Emmanuel
 */ 

#include "adc.h"

tADConfig myADConfig;	// Estructura para configuracion de ADC

// Funci�n del usuario de inicializaci�n del AD. 
// Completa los par�metros de la estructura ADConfig e invoca la funci�n AD_Init
void init_adc()	
{
	//myADConfig.canal      = 0;   //<-- se reconfigura el canal en cada llamada a la funci�n leerAD();
	myADConfig.alineacion	= Derecha;
	myADConfig.prescaler	= AD_prescaler_div128; //(alrededor de 8900 Sps)
	myADConfig.interrupcion	= intNO;
	myADConfig.autoTrigger	= atNO;
	myADConfig.tensionRef	= Avcc;
	//myADConfig.tipoTrigger  = free_running;	// No importa si ADConfig.autotrig = atNO
	myADConfig.disDIs		= 0b00111111;		//deshabilita pines digitales de los 6 canales a utilizar
		
	iniciarAD(&myADConfig);
}

void iniciarAD(tADConfig * ADConfig)
{
	DIDR0 |= ADConfig->disDIs;

	ADMUX |= (ADConfig->alineacion<<ADLAR);
	ADMUX |= (ADConfig->tensionRef<<REFS0);
	
	energizaAD0;
	energizaAD1;
	
	// Habilita la l�gica del ADC, AutoTrigger, y establece prescaler de clock  
	ADCSRA = 0;			// Inicializa ADCSRA
	ADCSRA |= (1<<ADEN);
	ADCSRA |= (ADConfig->autoTrigger<<ADATE);
	ADCSRA |= (ADConfig->prescaler<<ADPS0);
	
	ADCSRA |= (ADConfig->interrupcion<<ADIE);	// Habilita interrupci�n por fin de conversi�n, si interrupt=1
}

uint16_t read_AD_channel(uint8_t canal)
{	
	uint8_t aux;
	aux  =  ADMUX&0xF0;				// preserva configuracion de ADMUX
	aux |= (canal&0x0F);
	ADMUX = aux;					// reescribe ADMUX
	flagAD_OFF;
	iniciaConversionAD;
	while(!verificaFlagAD);			// polling de ADIF hasta que se hace 1.
	return ADC;						// ADC es registro de Datos ADCH:ADCL
}