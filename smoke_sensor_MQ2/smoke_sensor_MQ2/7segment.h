/*
 * _7segment.h
 *
 * Created: 11/13/2017 2:16:14 PM
 *  Author: elex
 */ 


#ifndef _7SEGMENT_H_
#define _7SEGMENT_H_
#include<avr/io.h>


/*This macro or preprocessor defines the PORT Register to which all the segments of the 7 segmeny display are connected.*/

#ifndef _7SEGMENT_PORT
#define _7SEGMENT_PORT	PORTC
#endif


/*This macro or preprocessor defines the 7 segment display type used - Common Anode or Common Cathode.*/

#ifndef _7SEGMENT_TYPE
#define _7SEGMENT_TYPE	COMMON_ANODE
#endif

#define COMMON_ANODE		0x01
#define COMMON_CATHODE		0x02


/*This function is declared to display numbers from 0 to 9 and dot(.) in both Common Anode and Common Cathode 7 Segment Display.*/

void display_7segment(unsigned char);


/*Function defination*/
void display_7segment(unsigned char number)
{
	if(_7SEGMENT_TYPE==COMMON_ANODE)
	{
		if(number==0)
		_7SEGMENT_PORT=0xc0;
		else if(number==1)
		_7SEGMENT_PORT=0xf9;
		else if(number==2)
		_7SEGMENT_PORT=0xa4;
		else if(number==3)
		_7SEGMENT_PORT=0xb0;
		else if(number==4)
		_7SEGMENT_PORT=0x99;
		else if(number==5)
		_7SEGMENT_PORT=0x92;
		else if(number==6)
		_7SEGMENT_PORT=0x82;
		else if(number==7)
		_7SEGMENT_PORT=0xf8;
		else if(number==8)
		_7SEGMENT_PORT=0x80;
		else if(number==9)
		_7SEGMENT_PORT=0x90;
		else if(number==10)
		_7SEGMENT_PORT=0x7f;
		else
		;
	}
	else
	{
		if(number==0)
		_7SEGMENT_PORT=!(0xc0);
		else if(number==1)
		_7SEGMENT_PORT=!(0xf9);
		else if(number==2)
		_7SEGMENT_PORT=!(0xa4);
		else if(number==3)
		_7SEGMENT_PORT=!(0xb0);
		else if(number==4)
		_7SEGMENT_PORT=!(0x99);
		else if(number==5)
		_7SEGMENT_PORT=!(0x92);
		else if(number==6)
		_7SEGMENT_PORT=!(0x82);
		else if(number==7)
		_7SEGMENT_PORT=!(0xf8);
		else if(number==8)
		_7SEGMENT_PORT=!(0x80);
		else if(number==9)
		_7SEGMENT_PORT=!(0x90);
		else if(number==10)
		_7SEGMENT_PORT=!(0x7f);
		else
		;

	}
}
#endif /* 7SEGMENT_H_ */