/*
 * _7_segment.c
 *
 * Created: 12/29/2017 8:08:58 AM
 *  Author: kiran
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#define seven_segment PORTC
#define increase PINB&(1<<PB0)
#define decrease PINB&(1<<PB1)

uint8_t decode(int);  //decode funtion declared

//Main function
int main()
{
	int counter;        //variable to hold count
	DDRC=0xff;        //PORT C configured as output
	DDRB=0xfc;        //PORT B configured as input
	PORTC-0x00;
	PORTB=0x00;

	//endless loop
	while(1)
	{
		if(increase)        //increase count if increase button is pressed
		counter++;
		if(decrease)        //decrease count if decrease button is pressed
		counter--;
		if(counter>9)            //rolls count back to zero(0) if it becomes
		counter=0;            //greater than 9
		if(counter<0)            //change count to 9 if it becomes negative
		counter=9;
		seven_segment= decode(counter);
		_delay_ms(1000);
	}
	return 0;
}

//function to calculate 7_segment value 
uint8_t decode(int count)
{
	switch(count)
	{
		case 0:
		{
			return 0x3f;
			break;
		}
		case 1:
		{
			return 0x06;
			break;
		}
		case 2:
		{
			return 0x5b;
			break;
		}
		case 3:
		{
			return 0x4f;
			break;
		}
		case 4:
		{
			return 0x66;
			break;
		}
		case 5:
		{
			return 0x6d;
			break;
		}
		case 6:
		{
			return 0x7d;
			break;
		}
		case 7:
		{
			return 0x07;
			break;
		}
		case 8:
		{
			return 0x7f;
			break;
		}
		case 9:
		{
			return 0x6f;
			break;
		}
		default:
		break;
	}
	return 0;
}
