/*
 * lab1.c
 *
 * Created: 7/5/2022 4:14:31 AM
 * Author : Nader
 */ 

/*************************************** L A B  7 ********************************************/
/* the main targrt of this lab is to show you how to use software timers                    */
/********************************************************************************************/




#include <avr/io.h>
#include <util/delay.h>
/***** FREERTOS *******/
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "timers.h"
/****** drivers ******/
#include "uart.h"
#include "GPIO.h"



#define  BTN B0

TimerHandle_t T1;


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

 
 void init()
  {
	 out(D4,0);
	 UART_init();
	// inp(BTN);
	 
 }

void timer_handler(TimerHandle_t t1)
{
	
	toggle(D4);
}


void task1(void)
{
	uint16_t tme=100;
	while (1)
	{
		char tmp =UART_recieve();
		if (tmp=='s')
		{
			xTimerStop(T1,1000);
		}
		if (tmp=='i')
		{
			tme= tme/2;
			xTimerChangePeriod(T1,tme,1000);
		}
		if (tmp=='d')
		{
			tme = tme*2;
			xTimerChangePeriod(T1,tme,1000);
		}
		if (tmp=='r')
		{
			xTimerReset(T1,1000);
		}
		
     }
	
   
}
/*void task1(void)
{
	
	   
	while (1)
	{
		
		
		
	
	
		
		
		

	}
	
	
*/


int main(void)
{
    init();
	
	TaskHandle_t task1_h;//,task2_h;
	

    T1 = xTimerCreate(  "MyTimer",100, pdTRUE,( void * ) 0, timer_handler);
	 xTimerStart( T1, 0 );
	xTaskCreate(task1,"process",250,NULL,1,&task1_h);
//	xTaskCreate(task2,"handler",250,NULL,1,&task2_h);
	
	
	vTaskStartScheduler();
	
	
	
   
}

