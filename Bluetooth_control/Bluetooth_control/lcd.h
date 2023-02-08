#ifndef	_LCD_H_
#define	_LCD_H_	
#include<avr/io.h>
#include<util/delay.h>
#include<stdlib.h>

#ifndef LCD_DATA_PORT
#define LCD_DATA_PORT	PORTA	 
#endif

#ifndef LCD_CONT_PORT	
#define LCD_CONT_PORT PORTB
#endif

#ifndef LCD_RS
#define LCD_RS PB0
#endif

#ifndef LCD_RW
#define LCD_RW PB1
#endif

#ifndef LCD_EN
#define LCD_EN PB2
#endif

void lcd_data_write(char data);
void lcd_command_write( char command);
void lcd_init();
void lcd_string_write( char *string);
void lcd_number_write(int number,unsigned char radix);

void lcd_data_write(char data)
{
LCD_CONT_PORT=_BV(LCD_EN)|_BV(LCD_RS);
LCD_DATA_PORT=data;
_delay_ms(1);
LCD_CONT_PORT=_BV(LCD_RS);
_delay_ms(1);
}


void lcd_command_write(char command)
{
LCD_CONT_PORT=_BV(LCD_EN);
LCD_DATA_PORT=command;
_delay_ms(1);
LCD_CONT_PORT=0x00;
_delay_ms(1);
}

void lcd_init()
{
	lcd_command_write(0x38);
	lcd_command_write(0x01);
	lcd_command_write(0x06);
	lcd_command_write(0x0e);	
}

void lcd_string_write(char *string)
{
while (*string)
lcd_data_write(*string++);
}

void lcd_number_write(int number,unsigned char radix)
{
char *number_string="00000";
itoa(number,number_string,radix);
lcd_string_write(number_string);
}
#endif

