/*
 * adc.c
 * APOS
 * ATMEGA2560
 * Autor: Jordán Emmanuel
 */ 

#include "adc.h"

tADConfig myADConfig;	// Estructura para configuracion de ADC

// Función del usuario de inicialización del AD. 
// Completa los parámetros de la estructura ADConfig e invoca la función AD_Init
void init_adc()	
{
	//myADConfig.canal      = 0;   //<-- se reconfigura el canal en cada llamada a la función leerAD();
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
	
	// Habilita la lógica del ADC, AutoTrigger, y establece prescaler de clock  
	ADCSRA = 0;			// Inicializa ADCSRA
	ADCSRA |= (1<<ADEN);
	ADCSRA |= (ADConfig->autoTrigger<<ADATE);
	ADCSRA |= (ADConfig->prescaler<<ADPS0);
	
	ADCSRA |= (ADConfig->interrupcion<<ADIE);	// Habilita interrupción por fin de conversión, si interrupt=1
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