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
/****** drivers ******/
#include "uart.h"
#include "GPIO.h"

SemaphoreHandle_t Mutex1;

#define  BTN B0

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

 
 void init()
  {
	 
	 UART_init();
	// inp(BTN);
	 
 }

void task2(void)
{
	while (1)
	{
		if (xSemaphoreTake(Mutex1,(TickType_t)1000)==pdTRUE)
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
			 
		 xSemaphoreGive(Mutex1);		
		}
			
			
		
			
		

       }
	
   
}
void task1(void)
{
	
	   
	while (1)
	{
		
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
			
			xSemaphoreGive(Mutex1);
			
		}
	
		
		
		

	}
	
	



int main(void)
{
    init();
	
	TaskHandle_t task1_h,task2_h;
	
	Mutex1 = xSemaphoreCreateMutex();
	xTaskCreate(task1,"process",250,NULL,1,&task1_h);
	xTaskCreate(task2,"handler",250,NULL,1,&task2_h);
	
	
	vTaskStartScheduler();
	
	
	
   
}

