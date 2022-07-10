/*
 * lab1.c
 *
 * Created: 7/5/2022 4:14:31 AM
 * Author : Nader
 */ 

/*************************************** L A B  5 ********************************************/
/* the main targrt of this lab is to show you how to synchronize your code using semaphores */
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

SemaphoreHandle_t x;

#define  BTN B0
/*
the serial task should work when you press the button by this we achieve synchronization
*/

char* int2str(uint16_t x)
{
	char asci_num[]={'0','1','2','3','4','5','6','7','8','9'};
	
	uint8_t digit1=0,digit2=0;
	
	digit1 = x % 10;
	digit2 = (x %100) / 10;
	
	char tmp[2] ={' '};
	tmp[0] = asci_num[digit1];
	tmp[1] = asci_num[digit2];
	
	return tmp;
	
}
void print( char * msg)
{
	uint8_t i =0;
	while(msg != '\0')
	{
		UATR_SEND(msg[i]);
		i++;
	}
	
}

 
 void init()
  {
	 
	 UART_init();
	 inp(BTN);
	 
 }

void task2(void)//button task
{
	while (1)
	{
		if (read(BTN)==1)
		{
			_delay_ms(250);
			if (xSemaphoreGive( x ) != pdTRUE)
			{
				
			}
			     
					
			
		}

	}
	
   
}
void task1(void)//serial server task
{
	   x = xSemaphoreCreateBinary();
	   xSemaphoreTake( x, (TickType_t)0 ) ;
	   uint16_t i=0;
	   
	while(1)
	{  
		
	     if (xSemaphoreTake( x,(TickType_t)10 )==pdTRUE)
	     {
			   
			   print("Server Respond To Clint : ");
			   char* xt = int2str(x);
			   print(int2str(i));
			   i++;
			   print('\n');
			 
			 
	     }
	   

        	}
	
	

}

int main(void)
{
    init();
	
	TaskHandle_t task1_h,task2_h;
	
	xTaskCreate(task1,"process",150,NULL,1,&task1_h);
	xTaskCreate(task2,"handler",150,NULL,1,&task2_h);
	
	
	vTaskStartScheduler();
	
	
	
   
}

