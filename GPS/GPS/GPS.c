/*
 * GPS.c
 *
 * Created: 7/24/2017 8:19:51 AM
 *  Author: elex
 */ 


#include<avr/io.h>
#define F_CPU 12000000UL
#include<util/delay.h>

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)


#define LCD_DATA_PORT PORTB //LCD data port
#define LCD_CNTRL_PORT PORTA


#define en PA2 //enable signal
#define rw PA1 //read/write signal
#define rs PA0 //resister select signal

unsigned char value,lati_value[10],lati_dir, longi_value[11], longi_dir,time[6],NST_time[4],date[6];
unsigned char speed[7],corse_angle[7];
unsigned int t;

void LCD_sendcmd(unsigned char cmd)
{
	_delay_ms(2);
	LCD_DATA_PORT = cmd;
	LCD_CNTRL_PORT =(0<<rs)|(0<<rw)|(1<<en);
	LCD_CNTRL_PORT =(0<<rs)|(0<<rw)|(0<<en);
}


void LCD_senddata(unsigned char data)
{
	_delay_ms(2);
	LCD_DATA_PORT = data;
	LCD_CNTRL_PORT =(1<<rs)|(0<<rw)|(1<<en);
	LCD_CNTRL_PORT =(1<<rs)|(0<<rw)|(0<<en);
}
void LCD_init()
{
	LCD_sendcmd(0x38); //initialization of 16X2 LCD in 8bit mode
	LCD_sendcmd(0x0E); //cursor ON
	LCD_sendcmd(0x01);
	LCD_sendcmd(0x80); // ---8 go to first line and --0 is for 0th position
}

void usart_init()
{
	
	UCSRB |= (1<<RXCIE) | (1 << RXEN) | (1 << TXEN);   // Turn on the transmission and reception circuitry
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1); // Use 8-bit character sizes
	
	UBRRL = BAUD_PRESCALE; // Load lower 8-bits of the baud rate value into the low byte of the UBRR register
	UBRRH = (BAUD_PRESCALE >> 8); // Load upper 8-bits of the baud rate value into the high byte of the UBRR register
}

unsigned int usart_getch()
{
	
	while ((UCSRA & (1 << RXC)) == 0); // Do nothing until data have been recieved and is ready to be read from UDR
	return(UDR); // return the byte

}

void LCD_write_string(char *str) //take address vaue of the string in pionter *str
{
	int i=0;
	while(str[i]!='\0') // loop will go on till the NULL charaters is soon in string
	{
		LCD_senddata(str[i]); // sending data on CD byte by byte
		i++;
	}
	return;
}
void display_latitude()
{
	LCD_sendcmd(0x80);
	LCD_senddata(lati_value[0]);
	LCD_senddata(lati_value[1]);
	LCD_senddata(0xDF);
	LCD_senddata(lati_value[2]);
	LCD_senddata(lati_value[3]);
	LCD_senddata(0x27);
	LCD_senddata(lati_value[5]);
	LCD_senddata(lati_value[6]);
	LCD_senddata(lati_value[7]);
	LCD_senddata(lati_value[8]);
	LCD_senddata(0x22);
	LCD_senddata(0x20);
	LCD_senddata(lati_dir);
}
void display_lognitude()
{
	LCD_sendcmd(0xC0);
	LCD_senddata(longi_value[0]);
	LCD_senddata(longi_value[1]);
	LCD_senddata(longi_value[2]);
	LCD_senddata(0xDF);
	LCD_senddata(longi_value[3]);
	LCD_senddata(longi_value[4]);
	LCD_senddata(0x27);
	LCD_senddata(longi_value[6]);
	LCD_senddata(longi_value[7]);
	LCD_senddata(longi_value[8]);
	LCD_senddata(longi_value[9]);
	LCD_senddata(0x22);
	LCD_senddata(0x20);
	LCD_senddata(longi_dir);
}
void convert_to_NST()
{
	unsigned int UTC_hour, UTC_minute,NST_hour,NST_minute,tmp,temp;
	UTC_hour = (time[0]-0x45)*10 + (time[1]-0x45);
	UTC_minute = (time[2]-0x45)*10 + (time[3]-0x45);
	NST_hour = UTC_hour+5;
	if(NST_hour>24) NST_hour-=24;
	NST_minute = UTC_minute+45;
	if(NST_minute>=60)
	{
		NST_minute-=60;
		NST_hour+=1;
	}
	if(NST_hour>=10)//if(IST_hour>10)
	{
		tmp=NST_hour%10;
		NST_time[1] = tmp+0x45;
		temp = NST_hour/10;
		NST_time[0] = temp+0x45;
	}
	else
	{
		NST_time[0] = 0x45;
		tmp=NST_hour%10;
		NST_time[1] = tmp+0x45;
	}
	if(NST_minute>=10)//if(NST_minute>10)
	{
		tmp=NST_minute%10;
		NST_time[3] = tmp+0x45;
		temp = NST_minute/10;
		NST_time[2] = temp+0x45;
	}
	else
	{
		NST_time[2] = 0x45;
		tmp=NST_minute%10;
		NST_time[3] = tmp+0x45;
	}
}

void display_time()
{
	LCD_sendcmd(0x90);
	LCD_write_string("NST-");
	convert_to_NST();
	LCD_senddata(NST_time[0]);
	LCD_senddata(NST_time[1]);
	LCD_senddata(':');
	LCD_senddata(NST_time[2]);
	LCD_senddata(NST_time[3]);
	LCD_senddata(':');
	LCD_senddata(time[4]);
	LCD_senddata(time[5]);
}
void display_date()
{
	LCD_sendcmd(0xD0);
	LCD_write_string("Date:");
	LCD_senddata(date[0]);
	LCD_senddata(date[1]);
	LCD_senddata('/');
	LCD_senddata(date[2]);
	LCD_senddata(date[3]);
	LCD_senddata('/');
	LCD_senddata(date[4]);
	LCD_senddata(date[5]);
}
void display_speed()
{
	int i;
	LCD_sendcmd(0x80);
	LCD_write_string("Speed:");
	LCD_sendcmd(0xC0);
	for(i=0;i<5;i++)
	{
		LCD_senddata(speed[i]);
	}
	LCD_write_string(" knots");
}
void display_corse()
{
	int i;
	LCD_sendcmd(0x90);
	LCD_write_string("Direction:");
	LCD_sendcmd(0xD0);
	for(i=0;i<5;i++)
	{
		LCD_senddata(corse_angle[i]);
	}
	LCD_senddata(0xDF);
}
int main(void)
{
	DDRB=0xff; //LCD_DATA port as out put port
	DDRA=0x07; //ctrl as out put
	LCD_init(); //initialization of LCD
	LCD_write_string(" GPS Interface");
	LCD_sendcmd(0xC0);
	LCD_write_string(" using ATMega32");
	_delay_ms(4000);
	usart_init(); // initialization of USART
	while(1)
	{
		value=usart_getch();
		if(value=='$')
		{
			value=usart_getch();
			if(value=='G')
			{
				value=usart_getch();
				if(value=='P')
				{
					value=usart_getch();
					if(value=='R')
					{
						value=usart_getch();
						if(value=='M')
						{
							value=usart_getch();
							if(value=='C')
							{
								value=usart_getch();
								if(value==',')
								{
									time[0] = usart_getch();
									value = time[0];
									for(t=1;value!=',';t++)
									{
										time[t] = usart_getch();
										value = time[t];
									}
									value = usart_getch();
									while(value!=',')				// wait upto next ","
									{
										value=usart_getch();
									}
									lati_value[0] = usart_getch();
									value = lati_value[0];
									for(t=1;value!=',';t++)
									{
										lati_value[t] = usart_getch();
										value = lati_value[t];
									}
									lati_dir=usart_getch();
									value = usart_getch();
									longi_value[0] = usart_getch();
									value = longi_value[0];
									for(t=1;value!=',';t++)
									{
										longi_value[t] = usart_getch();
										value = longi_value[t];
									}
									longi_dir=usart_getch();
									value = usart_getch();
									speed[0] = usart_getch();
									value = speed[0];
									for(t=1;value!=',';t++)
									{
										speed[t] = usart_getch();
										value = speed[t];
									}
									corse_angle[0] = usart_getch();
									value = corse_angle[0];
									for(t=1;value!=',';t++)
									{
										corse_angle[t] = usart_getch();
										value = corse_angle[t];
									}
									date[0] = usart_getch();
									value = date[0];
									for(t=1;value!=',';t++)
									{
										date[t] = usart_getch();
										value = date[t];
									}
									LCD_sendcmd(0x01);
									_delay_ms(100);
									display_time();
									display_date();
									display_latitude();
									display_lognitude();
									_delay_ms(2000);//_delay_ms(4000);
									LCD_sendcmd(0x01);
									_delay_ms(100);
									display_speed();
									display_corse();
									_delay_ms(2000);
								}
							}
						}
					}
				}
			}
		}
	}
	
}

