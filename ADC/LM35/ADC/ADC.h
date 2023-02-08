/*
 * ADC.h
 *
 * Created: 6/2/2018 2:02:16 PM
 *  Author: kiran
 */ 


#ifndef ADC_H_
#define ADC_H_

void ADC_Init()
{
	DDRA=0x00;			/* Make ADC port as input */
	ADCSRA = 0x87;		/*Enable ADC, fr/128  */
	ADMUX = 0x40;		/*Vref: Avcc, ADC channel: 0 */
	
}

int ADC_Read(char channel)
{
	int Ain,AinLow;
	
	ADMUX=ADMUX|(channel & 0x0f);		/* set input channel to read */

	ADCSRA |= (1<<ADSC);		/* start conversion */
	while((ADCSRA&(1<<ADIF))==0);	/*monitor end of conversion interrupt flag */
	
	_delay_us(10);
	AinLow = (int)ADCL;				/*read lower byte*/
	Ain = (int)ADCH*256;			/*read higher 2 bits, Multiply with weightage*/
	Ain = Ain + AinLow;
	return(Ain);					/*return digital value*/
}



#endif /* ADC_H_ */