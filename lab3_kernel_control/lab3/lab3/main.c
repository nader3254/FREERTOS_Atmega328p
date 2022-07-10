/*
 * lab1.c
 *
 * Created: 7/5/2022 4:14:31 AM
 * Author : Nader
 */ 

/******************* L A B  3 *************************/
/* the main targrt of this lab is to solve 
shared data problem */




#include <avr/io.h>
#include <util/delay.h>
/***** FREERTOS *******/
#include "FreeRTOS.h"
#include "task.h"
/****** drivers ******/
#include "uart.h"


uint32_t x=0 , y=0;
 
 void init()
  {
	 
	 UART_init();
	/* DDRB  = 0xff;
	 PORTB = 0x00;*/
	 
 }

void task2(void)
{
    char* a= "shared data problem here " ;
	while(1)
	{

	 int i=0;
	 if (y != x)
	 {
		 while(a[i] != '\0')
		 {
			 UATR_SEND(a[i]);
			 i++;
		 }
		 UATR_SEND('\n');
		 i=0;
		 
	  }
	vTaskDelay(27); 	
	   
	}
}
void task1(void)
{
	//taskENTER_CRITICAL();
	x++;
	//if task is leaved here shared data problem may occur here
	//to solve this uncomment x_critical(); 
	y++;
	//taskEXIT_CRITICAL();

}

int main(void)
{
    init();
	
	TaskHandle_t task1_h,task2_h;
	
	xTaskCreate(task1,"process",150,NULL,1,&task1_h);
	xTaskCreate(task2,"handler",150,NULL,2,&task2_h);
	
	
	vTaskStartScheduler();
	
	
	
   
}

