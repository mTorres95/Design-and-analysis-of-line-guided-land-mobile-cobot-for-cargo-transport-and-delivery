#include "uart.h"

uint8_t flagcom;		// flag para indicar que se inicio un comando
uint8_t indcom;			// index del buffer de recepcion

#define comSize 30
char comando[comSize];		// buffer de recepcion

#define getc() mi_getc(&uart_io)		// redefinicion de la primitiva de entrada para recibir por UART
#define putc(x) mi_putc(x, &uart_io)	// redefinicion de la primitiva de salida para transmitir por UART

FILE uart_io = FDEV_SETUP_STREAM(mi_putc, mi_getc, _FDEV_SETUP_RW);

void init_uart0(uint32_t baudrate, uint8_t InterRx, uint8_t InterTx){
	flagcom = 0;

	stdout = stdin = &uart_io;

	UBRR0  = F_CPU/16/baudrate - 1;						// Configuracion del baudrate
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);		// Habilitacion del pin Rx y Tx. Habilitacion de interrupcion por recepcion completa
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);				// 2 bits de STOP y 8 bits de datos

	// === INTERRUPCIONES DE UART (por recepcion) ===
	if(InterRx){
		UCSR0A &=~ (1<<RXC0);		// Apagar el flag de interrupcion por recepcion completa
		UCSR0B |=  (1<<RXCIE0);		// Habilitar la interrupcion Rx
	}
	// === INTERRUPCIONES DE UART (por transmision) ===
	if(InterTx){
		UCSR0A &=~ (1<<TXC0);		// Apagar el flag de interrupcion por transmision completa
		UCSR0B |=  (1<<TXCIE0);		// Habilitar la interrupcion Tx
}
}
	

void init_uart2(uint32_t baud, uint8_t InterRx, uint8_t InterTx){
	flagcom = 0;
	
	stdout = stdin = &uart_io;
	
	UBRR2  = F_CPU/16/baud - 1;						// Configuracion del baudrate
	UCSR2B = (1<<RXEN2)|(1<<TXEN2)|(1<<RXCIE2);		// Habilitacion del pin Rx y Tx. Habilitacion de interrupcion por recepcion completa
	UCSR2C = (1<<USBS2)|(3<<UCSZ20);				// 2 bits de STOP y 8 bits de datos
	
	// === INTERRUPCIONES DE UART (por recepcion) ===
	if(InterRx){
		UCSR2A &=~ (1<<RXC2);		// Apagar el flag de interrupcion por recepcion completa
		UCSR2B |=  (1<<RXCIE2);		// Habilitar la interrupcion Rx
	}
	// === INTERRUPCIONES DE UART (por transmision) ===
	if(InterTx){
		UCSR2A &=~ (1<<TXC2);		// Apagar el flag de interrupcion por transmision completa
		UCSR2B |=  (1<<TXCIE2);		// Habilitar la interrupcion Tx
	}
}

// NOTA!!!! Funciona para UART0 y asi poder usarla con Termite!! Cambiar a registros de la uart2
int mi_putc(char c, FILE *stream){
	while(!(UCSR0A & (1<<UDRE0)));		// Esperar hasta que se desocupe el buffer de transmision
	UDR0 = c;							// Poner el dato en el registro UDR0
	return 0; 
}


int mi_getc(FILE *stream){
	while ( !(UCSR0A & (1<<RXC0)));		// Esperar hasta que la recepcion se complete
	return UDR0;						// Leer el dato del registro UDR0
}


ISR(USART2_RX_vect){
	char dato;
	dato = getc();
	switch(dato)
	{
		case ':':			// Delimitador de inicio
			flagcom = 1;
			indcom = 0;		// Inicializa indice de buffer de recepcion
			break;
		case '\r':						// Delimitador de final
			if(flagcom){
				comando[indcom] = 0;		// coloca \0 luego del ultimo caracter recibido antes de \r
				//InterpretaComando(comando);	// Llama a funcion interprete de comandos
				printf("No hay interprete de comando.\r\n");
			}
			flagcom = 0;
			break;
		case 8:			// backspace
			indcom--;
			break;
		default:								// Todo lo que este entre delimitadores
			if(flagcom && indcom<comSize) comando[indcom++]=dato; // Guarda en elemento del buffer e incrementa indcom para apuntar a siguiente
			break;
	}
}
