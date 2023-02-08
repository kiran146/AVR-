/*
 * Bluetooth_control.c
 *
 * Created: 2/9/2017 8:05:43 AM
 *  Author: elex_eKiran
 */ 
//**************************************************************//
//Micro-controller			:ATmega32
//System Clock				:8MHz
//Project					:Bidirectional Wireless Data Communication between HC-05 Bluetooth Module and Android Mobile with ATmega32 and LCD Display
//Software					:ATmel Studio 6
//USART Baud Rate			:9600
//USART Data Bits			:8
//USART Stop Bits			:1
//USART Mode				:Asynchronous Mode
//USART Parity				:No Parity
//**************************************************************//

#include<avr/io.h>
#define	F_CPU	12000000ul
#include<util/delay.h>
#define BaudRate 9600
#define BAUD_PRESCALE (((F_CPU/(BaudRate*24UL)))-1)
#define		LCD_DATA_PORT		PORTB
#define 	LCD_CONT_PORT		PORTC
#define 	LCD_RS 		PC0
#define 	LCD_RW 		PC1
#define 	LCD_EN 		PC2
#include "lcd.h"					
#include "hc05.h"     

int main(void)
{
	DDRB=0xff;								//All the 8 pins of PortB are declared output (data pins of LCD are connected)
	DDRC=0x07;								//PC0, PC1 and PC2 pins of PortC are declared output (control pins of LCD are connected)
	
	unsigned char received_data;			//Variable declaration
	lcd_init();								//LCD initialization
	usart_init();							//USART initialization
	
	hc_05_bluetooth_transmit_string("Automate the devices");			//Transmits a string to Blue-tooth Module
	hc_05_bluetooth_transmit_byte(0x0d);								//Transmits Carriage return to Blue-tooth Module
	hc_05_bluetooth_transmit_byte(0x0a);								//Transmits New Line to Blue-tooth Module for new line
	hc_05_bluetooth_transmit_string("Send one Character at a time");	
	hc_05_bluetooth_transmit_byte(0x0d);
	hc_05_bluetooth_transmit_byte(0x0a);
	
	lcd_string_write("Kathford R&D");									//String is displayed in 1st row of LCD
	lcd_command_write(0xc0);											//Cursor moves to 2nd row 1st column
	lcd_string_write("KATHFORD");										//String is displayed in 2nd row of LCD

	_delay_ms(500);
	_delay_ms(500);
	_delay_ms(500);
	_delay_ms(500);
	/*2s delay*/
	
	lcd_command_write(0x01);									//Clear Screen
	lcd_string_write(" Received Data:");						//String is displayed in 1st row of LCD
	lcd_command_write(0xc0);									//Cursor moves to 2nd row 1st column
	
	while(1)													//Start the infinite loop
	{
		received_data=hc_05_bluetooth_receive_byte();
		//lcd_init();	
		lcd_data_write(received_data);							//Displayed received character in 2nd row of LCD
		hc_05_bluetooth_transmit_byte(received_data+1);			//Transmits the received character by incrementing it by one
		hc_05_bluetooth_transmit_byte(0x0d);					//Transmits Carriage return to Blue-tooth Module
		hc_05_bluetooth_transmit_byte(0x0a);					//Transmits New Line to Blue-tooth Module for new line
	}
}
/*End of program*/


