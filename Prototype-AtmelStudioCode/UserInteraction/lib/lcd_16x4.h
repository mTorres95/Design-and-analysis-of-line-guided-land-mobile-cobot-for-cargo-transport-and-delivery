/*
 * lcd_16x4.h
 *
 * APOS
 * ATMEGA2560
 */ 


#ifndef LCD_16X4_H_
#define LCD_16X4_H_

#include "main.h"

// DEFINICIONES DE APOYO
#define LCD_INST	0
#define LCD_DATA	1

// INSTRUCCIONES
#define LINE1		0x80
#define LINE2		0xC0
#define LINE3		0x94
#define LINE4		0xD4
#define CLEAR		0x01

// FUNCIONES B?SICAS
void lcd_start();
void lcd_write(uint8_t type, uint8_t inst_data);
void lcd_init();

// FUNCIONES COMPUESTAS
void lcd_print(char *s);



#endif /* LCD_16X4_H_ */