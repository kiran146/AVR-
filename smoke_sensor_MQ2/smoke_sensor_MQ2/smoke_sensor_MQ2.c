/*
 * smoke_sensor_MQ2.c
 * Created: 11/13/2017 1:37:47 PM
 */ 

//**************************************************************//
//Microcontroller			:ATmega32
//System Clock				:1MHz
//Project					:Smoke Monitoring and Alarm System with ATmega32 and 7-Segment Display using MQ-2 Sensor
//Software					:Atmel Studio 6
//Author					:eKiran BAgale
//**************************************************************//

#define	F_CPU	1000000
#include<util/delay.h>
#define 	_7SEGMENT_PORT		PORTC
#define 	_7SEGMENT_TYPE		COMMON_ANODE
#include "7segment.h"
#include "ADC.h"
#define MQ2_SENSOR_REF 700

int main(void)
{
	DDRC=0xff;									/*All the 8 pins of PortC are declared output (7-segment displays are connected)*/
	DDRD=0x0f;									/*LSB pins of PORTD are declared output (display select pins 1, 2, 3 and 4 of Quad 7-segment Display are connected)*/
	DDRB=0x01;
	int mq2_smoke_sensor_output;				/*Variable declarations*/
	unsigned char temp;
	adc_init();									/*ADC initialization*/
	
	while(1)
	{
		mq2_smoke_sensor_output=read_adc_channel(0);      /*Reading smoke sensor value*/
		temp=mq2_smoke_sensor_output/1000;				  /*Getting 1000th digit of smoke sensor output value*/
		display_7segment(temp);							  /*Displaying 1000th digit of smoke sensor output value in 7-segment display1*/
		PORTD=0x01;										  /*7-segment display1 is On*/
		_delay_ms(3);
		temp=mq2_smoke_sensor_output/100;				  /*Getting 1000th and 100th digit of smoke sensor output value*/
		temp=temp%10;									  /*Getting 100th digit of smoke sensor output value*/
		display_7segment(temp);
		PORTD=0x02;										  /*7-segment display2 is On*/
		_delay_ms(3);
		temp=mq2_smoke_sensor_output/10;				  /*Getting 1000th, 100th and 10th digit of smoke sensor output value*/
		temp=temp%10;									  /*Getting 10th digit of smoke sensor output value*/
		display_7segment(temp);
		PORTD=0x04;										  /*7-segment display3 is On*/
		_delay_ms(3);
		temp=mq2_smoke_sensor_output%10;				  /*Getting unit digit of smoke sensor output value*/
		display_7segment(temp);
		PORTD=0x08;										  /*7-segment display4 is On*/
		_delay_ms(10);
		
/*Checking MQ-2 Smoke Sensor output with threshold to turn On or Off Buzzer*/
		if(mq2_smoke_sensor_output > MQ2_SENSOR_REF)
		{
			PORTB=0x01;			/*Buzzer is On*/
		}
		else
		{
			PORTB=0x00;			/*Buzzer is Off*/
		}
	}
}
/*End of Program*/


