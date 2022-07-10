/*
 * lab1.c
 *
 * Created: 7/5/2022 4:14:31 AM
 * Author : Nader
 */ 

#include <avr/io.h>
#include <util/delay.h>
/***** FREERTOS *******/
#include "FreeRTOS.h"
#include "task.h"



void init()
{
	DDRB  = 0xff;
	PORTB = 0x00;
		
}
void blink(void)
{
	PORTB = 0x00;
	_delay_ms(500);
	PORTB = 0x30;
	_delay_ms(500);
/*	while (1)
	{
		PORTB = 0x00;
		_delay_ms(1000);
		PORTB = 0x30;
		_delay_ms(1000);
	}
	*/
}

int main(void)
{
    init();
	
	TaskHandle_t led_blink_task;
	
	xTaskCreate(blink,"blnk",150,NULL,1,&led_blink_task);
	vTaskStartScheduler();
	
	
	
   
}

