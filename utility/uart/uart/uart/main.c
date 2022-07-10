/*
 * uart.c
 *
 * Created: 7/8/2022 6:58:17 AM
 * Author : Nader
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "GPIO.h"




//#define  BUTTON   B0
/*
typedef enum
{
	green1 = D2,
	white  = D3,
	red    = D4,
	blue   = D5,
	green2 = D6,
	yellow = D7
}leds;
*/
//leds  pnlds[] ={green1,white,red,blue,green2,yellow};
//char* strld[] ={"green1","white","red","blue","green2","yellow"};

#define water_condition  ((h_ctr >= 2) && (o_ctr >=1))

uint16_t o_ctr=0,h_ctr=0;


void prints( char * msg)
{
	uint8_t i =0;
	while(msg[i] != '\0')
	{
		UATR_SEND(msg[i]);
		i++;
	}
	
}
void printi(uint8_t x)
{
	char asci_num[]={'0','1','2','3','4','5','6','7','8','9'};
	uint8_t digit1=0,digit2=0;
	
	digit1 = x % 10;
	digit2 = (x %100) / 10;
	
	char tmp[2] ;
	tmp[0] = asci_num[digit1];
	tmp[1] = asci_num[digit2];
	
		
		UATR_SEND(tmp[1]);
		UATR_SEND(tmp[0]);
		
	
	
}

int main(void)
{
	
	 UART_init();
	 
	 
	 while(1)
	 {
		 
		 o_ctr++;
		 prints("o is incremented ... \n");
		
		 prints("o = ");  printi(o_ctr);
		 prints('\n') ;
		 
		 if (water_condition)
		 {
			  o_ctr--; h_ctr-=2;
			 prints("new water created .... \n");
			  prints(" h = ");  printi(h_ctr);
			  // print('\n') ;
			  prints(" o = ");  printi(o_ctr);
			  prints('\n') ;
			
			 out(D4,'h');
			 _delay_ms(500);
			 out(D4,'l');
			 _delay_ms(500);
		 }
		 
		 _delay_ms(3000);
		 
		 
		 /************************************************************************/
		 /*                                                                      */
		 /************************************************************************/
		 
		 	h_ctr++;
		 	prints("h is incremented ... \n");
		 	prints("h = ");  printi(h_ctr);
		 	prints('\n') ;
		 	if (water_condition)
		 	{ 	o_ctr--; h_ctr-=2;
			 	prints("new water created ....\n");
				 prints(" h = ");  printi(h_ctr);
				// print('\n') ;
				 prints(" o = ");  printi(o_ctr);
				 prints('\n') ;
			
			 	out(D4,'h');
			 	_delay_ms(500);
			 	out(D4,'l');
			 	_delay_ms(500);
			 	
		 	}
		 	_delay_ms(1000);
		 
		 
	 }
	
	
}

/*

char a[] = "shared data problem here " ;
	
	     int i=0;
	
		 while(a[i]!='\0')
		 {
			 UATR_SEND(a[i]);
			 i++;
			// _delay_ms(20);
		 }
		 UATR_SEND((char)10);
		 i=0;
		_delay_ms(500);
		
		
		
		/*
		
		if (read(B0)==1)
		{
			out(D2,'h');
			
		}
		else
		{
			out(D2,'l');
		}
		
	/*	
		UATR_SEND('a');
		UATR_SEND('a');UATR_SEND('a');UATR_SEND('a');
		char x = UART_recieve();
		
		if (x=='a')
		{
			out(D2,'h');
		}
		if (x=='b')
		{
			out(D2,'l');
		}
		
		/*UATR_SEND('a');
		UATR_SEND('\n');
		_delay_ms(500);*/
		
		