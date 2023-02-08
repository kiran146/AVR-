/*Functions and macros for Atmega16/32 series */

#ifndef	_USART_H_
#define	_USART_H_ 	

#include<avr/io.h>
#include<util/delay.h>

/*The function is declared to initialize the USART with following cinfiguration:-
USART mode - Asynchronous
Baud rate - 9600
Data bits - 8
Stop bit - 1
Parity - No parity.*/

void usart_init();							/*initialize the USART mode */

void usart_data_transmit(unsigned char data );	/*The function is declared to transmit data.*/
unsigned char usart_data_receive( void );		/*The function is declared to receive data.*/
void usart_string_transmit(char *string);		/*The function is declared to transmit string.*/
char *usart_string_receive(char *receive_string,unsigned char terminating_character);	/*The function is declared to receive string.*/

/*Function defination*/
void usart_init()
{
UBRRH =(BAUD_PRESCALE>>8);
UBRRL =BAUD_PRESCALE;
UCSRB|= (1<<RXEN)|(1<<TXEN);
UCSRC |=  (1 << URSEL) | (0<<USBS) | (1 << UCSZ0) | (1 << UCSZ1);
}


void usart_data_transmit(unsigned char data )
{
while ( !( UCSRA & (1<<UDRE)) );
UDR = data;
_delay_ms(1);
}

unsigned char usart_data_receive( void )
{
while ( !(UCSRA & (1<<RXC)) );
return UDR;
}

void usart_string_transmit(char *string)
{
while(*string)
{
usart_data_transmit(*string++);
}
}

char *usart_string_receive(char *receive_string,unsigned char terminating_character)
{
	unsigned char temp=0x00;
	for(unsigned char i=0;;i++)
	{
		*(receive_string+i)=usart_data_receive();
		if(*(receive_string+i)==terminating_character)
			break;
		else
		temp++;
	}
	*(receive_string+temp)='\0';
	return receive_string;
}
#endif
