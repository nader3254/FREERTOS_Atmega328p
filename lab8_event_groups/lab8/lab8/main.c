/*
 * lab1.c
 *
 * Created: 7/5/2022 4:14:31 AM
 * Author : Nader
 */ 

/*************************************** L A B  6 ********************************************/
/* the main targrt of this lab is to show you how to protect shared resources using mutex   */
/********************************************************************************************/




#include <avr/io.h>
#include <util/delay.h>
/***** FREERTOS *******/
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "event_groups.h"
/****** drivers ******/
#include "uart.h"
#include "GPIO.h"

SemaphoreHandle_t Mutex1;
EventGroupHandle_t Group1;


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
	 out(D5,'l');
	 UART_init();
	// inp(BTN);
	 
 }

void task3(void)
{
	while(1)
	{
		if( xEventGroupGetBits( Group1) == 6)
		{
			toggle(D5);
		}
		
		
		
	}
	
}
void task2(void)
{
	while (1)
	{
		if (xSemaphoreTake(Mutex1,(TickType_t)1000)==pdTRUE)
		{
				char tmp =UART_recieve();
		
			    if (tmp=='a')
			    {
					xEventGroupSetBits(Group1,2 );
					
			    }
			
			
			
			
			 
		        xSemaphoreGive(Mutex1);		
		}

       }
	
   
}
void task1(void)
{
	
	   
	while (1)
	{
		
	    if (xSemaphoreTake(Mutex1,(TickType_t)1000)==pdTRUE)
	    {
			char tmp =UART_recieve();
			
		     if (tmp=='s')
		     {
			     xEventGroupSetBits(Group1,4 );
		     }
		
		
		    xSemaphoreGive(Mutex1);
	     }

	   }
	

}


int main(void)
{
    init();
	
	TaskHandle_t task1_h,task2_h,task3_h;
	
	Mutex1 = xSemaphoreCreateMutex();
	Group1 = xEventGroupCreate();
	
	
	xTaskCreate(task1,"process",250,NULL,1,&task1_h);
	xTaskCreate(task2,"handler",250,NULL,1,&task2_h);
	xTaskCreate(task3,"name"   ,250,NULL,3,&task3_h);
	
	vTaskStartScheduler();
	
	
	
   
}

