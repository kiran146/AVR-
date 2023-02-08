/*
 * PWM_AVR.c
 *
 * Created: 12/28/2017 3:12:02 PM
 *  Author: kiran
 */ 


#include <avr/io.h>
#define get_bit(reg,bitnum) ((reg & (1<<bitnum))>>bitnum)

int main(void)
{
	DDRD=0xf8; // set the first 3 pins of PORTD to be inputs to read from the push buttons    DDRB=0xff; //  Pin3 in POrt B is output as this is the OC0 pin that will produce the PWM.
	PORTD=0x00; // Initialize PORTD to zeros
	TCCR0=0x75; //Configure TCCR0 value 75 to mantain70% duty cycle
	TIMSK=0x00;
	OCR0=255; // Set OCR0 to 255 so that the duty cycle is initially 0 and the motor is not rotating

	while(1)
	{
		if (get_bit(PIND,0)==1)
		{
			OCR0=178; //If button 1 is pressed, set OCR0=178 (duty cycle=10%).
		}
		if (get_bit(PIND,1)==1)
		{
			OCR0=102; //If button 2 is pressed, set OCR0=102 (duty cycle=60%).
		}
		if (get_bit(PIND,2)==1)
		{
			OCR0=25; //If button 3 is pressed, set OCR0=25 (duty cycle=90%).
		}
	}
}
