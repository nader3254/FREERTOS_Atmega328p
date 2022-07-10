/*
 * 7seg.c
 *
 * Created: 7/6/2022 11:12:44 AM
 * Author : Nader
 */ 

#include <avr/io.h>
#include <util/delay.h>

static struct seven_segment_type
{
	uint8_t * ddr;
	uint8_t * data_port ;
	
	uint8_t * ctrl_ddr;
	
	
	uint8_t s0;uint8_t s1;
	
	uint8_t data;
	uint8_t digit1 ;
	uint8_t digit2  ;

}sev;

void init_SevenSegment()
{
	 
	sev.ddr      =& DDRD ;  sev.data_port =& PORTD ;
	sev.ctrl_ddr =& DDRC ;  sev.s0 = 0x01  ; sev.s1 = 0x02;     
	
	*(sev.ddr)       = 0xff;
    *(sev.data_port) = 0xff;
	  sev.data=0;
	  
	 /* *(sev.ctrl_ddr) |= sev.s0  ; 
	  _delay_ms(1000);
	 *(sev.data_port) = 0x00;
	 _delay_ms(1000);
	 *(sev.data_port) = 0xff;
	 *(sev.ctrl_ddr) &= !sev.s0  ;
	  _delay_ms(1000);
	 *(sev.ctrl_ddr) |= sev.s1  ;
	 _delay_ms(1000);
	 *(sev.data_port) = 0x00;
	 _delay_ms(1000);
	 *(sev.data_port) = 0xff;
  */
	// *(sev.ctrl_ddr) |= sev.s0 | sev.s1  ;
	 
	 //PORTC =0x03; 
	 PORTC = 0x08  ; 
	 for (int i=0;i<8;i++)
	 {
		 *(sev.data_port) =(1<<i);
		 _delay_ms(100);
	 }
	 _delay_ms(50);
	 PORTC = 0x00;
	 	 
	 PORTC = 0x04;  
	 
	
	 for (int i=0;i<8;i++)
	 {
		 *(sev.data_port) =(1<<i);
		 _delay_ms(100);
	 }
	// PORTC = 0x08;
     _delay_ms(50);
	 PORTC = 0x00;
}

uint8_t evaluate(unsigned char x)
{
	uint8_t DATA_7SEG=0;
	switch(x)
	{
		case 0  : DATA_7SEG = 0x3f;     break;
		case 1  : DATA_7SEG = 0x06;     break;
		case 2  : DATA_7SEG = 0x5b;     break;
		case 3  : DATA_7SEG = 0x4f;     break;
		
		case 4  : DATA_7SEG = 0x66;     break;
		case 5  : DATA_7SEG = 0x6d;     break;
		case 6  : DATA_7SEG = 0x7d;     break;
		
		case 7  : DATA_7SEG = 0x07;     break;
		case 8  : DATA_7SEG = 0x7f;     break;
		case 9  : DATA_7SEG = 0x6f;     break;
		
		default :
		DATA_7SEG = 0xfc;     break;
		
		
	}
	
	return DATA_7SEG;
	
}



int main() {
	
    DDRB  |= 0x20;DDRC =0x0c;
	PORTB =0x00;
	PORTC =0x0c;
	init_SevenSegment();
	while (1)
	{
		for (int i=0;i<100;i++)
		{
			for (int j=0;j<25;j++)
			{
			   PORTC = 0x08  ;
			   *(sev.data_port) = evaluate(i%10);
			   _delay_ms(8);
			   PORTC = 0x00;
				 
				 PORTC = 0x04;
				 *(sev.data_port) =evaluate((i%100)/10);
				 _delay_ms(8);
				 PORTC = 0x00;
			}
			
			
			
		}
		
		
	}
}