/*
 * ADC.h
 *
 * Created: 11/13/2017 2:14:13 PM
 *  Author: elex
 */ 


#ifndef ADC_H_
#define ADC_H_
#include<avr/io.h>
#include<util/delay.h>


/*This function is declared to initialize the Analog to Digital Converter of AVR microcontrollers. 
The Analog to Digital Converter is initialized with the following features:-
Auto Triggering mode is enabled,
Free running mode is the source of trigger,
ADC conversion is started,
ADC frequency is 62.5 KHz at 1 MHz system frequency.*/

void adc_init(void);
/*This function is declared to read the digital value of the ADC conversion of the selected channel with follwoing conditions:-
AVCC is selected as the refence voltage and ADC output is right adjusted.*/

int read_adc_channel(unsigned char channel);

/*Function definations*/
void adc_init(void)
{
	ADCSRA=(1<<ADEN)|(1<<ADSC)|(1<<ADATE)|(1<<ADPS2);
	SFIOR=0x00;
	//ADMUX=0x40;
}


int read_adc_channel(unsigned char channel)
{
	int adc_value;
	unsigned char temp;
	ADMUX=(1<<REFS0)|channel;
	_delay_ms(1);
	temp=ADCL;
	adc_value=ADCH;
	adc_value=(adc_value<<8)|temp;
	return adc_value;
}
#endif /* ADC_H_ */