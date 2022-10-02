#ifndef UART_H
#define UART_H

#include "main.h"
//#include "uartInterpreter.h"

void init_uart0(uint32_t baudrate, uint8_t interrupcionRx, uint8_t interrupcionTx);
void init_uart2(uint32_t baudrate, uint8_t interrupcionRx, uint8_t interrupcionTx);
int mi_putc(char, FILE *stream);
int mi_getc(FILE *stream);


#endif
