/*
 * GccApplication1.c
 *
 * Created: 7/5/2022 12:30:56 AM
 * Author : Nader
 */ 

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    /* Replace with your application code */
	DDRB=0xff;
	
    while (1) 
    {
		PORTB =0x00;
		_delay_ms(8000);
		PORTB =0x30;
		_delay_ms(8000);
    }
}

