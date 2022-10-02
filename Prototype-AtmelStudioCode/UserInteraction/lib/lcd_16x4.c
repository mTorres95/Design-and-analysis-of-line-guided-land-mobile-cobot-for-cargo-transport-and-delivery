/*
 * lcd_16x4.c
 *
 * APOS
 * ATMEGA2560
 */ 

#include "lcd_16x4.h"

void lcd_start(){
	// Enable (E)
	PORTA &=~ (1<<DDA2);
	_delay_us(1);
	PORTA |=  (1<<DDA2);
}

void lcd_write(uint8_t type, uint8_t inst_data){
	// RS
	if (type==LCD_DATA){
		PORTA |=  (1<<DDA3);
		_delay_us(10);
	} else {
		PORTA &=~ (1<<DDA3);
		_delay_us(10);
	}

	// Datos (D4, D5, D6, D7)
	PORTA = (PINA & 0x0F) | (inst_data & 0xF0);
	lcd_start();
	PORTA = (PINA & 0x0F) | ((inst_data<<4) & 0xF0);
	lcd_start();
	_delay_ms(2);
}

void lcd_init(){
	// Enable y RS
	DDRA  |=  (1<<DDA2) | (1<<DDA3);
	// Data
	DDRA  |=  0xF0;  // 11110000
	
	// Enable y RS
	PORTA &=~ ((1<<DDA2) | (1<<DDA3));
	
	PORTA  = (PINA & 0x0F) | 0x30;

	_delay_ms(100);
	lcd_start();
	_delay_ms(5);
	lcd_start();
	_delay_us(100);
	lcd_start();
	_delay_us(100);

	PORTA = (PINA & 0x0F) | 0x20;
	
	lcd_start();
	_delay_us(100);

	lcd_write(LCD_INST, 0x2C);
	lcd_write(LCD_INST, 0x08);
	lcd_write(LCD_INST, 0x01);
	lcd_write(LCD_INST, 0x06);
	
	lcd_write(LCD_INST, 0x0C);
}

void lcd_print(char *s)
{
	while(*s)
	{
		lcd_write(LCD_DATA, *s);
		s++;
	}
}