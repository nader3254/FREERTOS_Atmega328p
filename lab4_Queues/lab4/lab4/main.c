/*
 * lab1.c
 *
 * Created: 7/5/2022 4:14:31 AM
 * Author : Nader
 */ 

/*********************** L A B  4 *****************************/
/* the main targrt of this lab is to show how to use queues  */
/************************************************************/



#include <avr/io.h>
#include <util/delay.h>
/***** FREERTOS *******/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
/****** drivers ******/
#include "uart.h"
#include "GPIO.h"

#define  BUTTON   B0

typedef enum
{
	green1 = D2,
	white  = D3,
	red    = D4,
	blue   = D5,
	green2 = D6,
	yellow = D7
}leds;

xQueueHandle Qledstr,Qledpin;

void prints(char* msg)
{
	int i = 0 ;
	while(msg[i]!='\0')
	{
		UATR_SEND(msg[i]);
		i++;
	}
	UATR_SEND('\n');
}

 
 void init()
  {
	 inp(B0);
	UART_init();
	 
	 
 }

void task2(void)
{
	leds  pnlds[] ={green1,white,red,blue,green2,yellow};
	char* strld[] ={"green1","white","red","blue","green2","yellow"};
	uint8_t x=0;

  while (1)
  {
	if (read(BUTTON)==1)
	{
		_delay_ms(150);
		
		xQueueSend(Qledstr,&strld[x],(TickType_t )1000);
		xQueueSend(Qledpin,&pnlds[x],(TickType_t )1000);
		x++;
		if (x>5)
		{
			x=0;
		}
  }





	}
  
}
void task1(void)
{
	 leds ll; char* ls ; 
	
	
	while(1)
	{
	   xQueueReceive(Qledpin,&ll,(TickType_t)1);
	if (xQueueReceive(Qledstr,&ls,(TickType_t)1))
	{	
		prints(ls);
	}
	 
	   PORTD = 0 ;
	   out(ll,'h');
	   _delay_ms(500);
	   out(ll,'l');
	   _delay_ms(500);
	}
}

int main(void)
{
    init();
			
	Qledstr =xQueueCreate(5,sizeof(char*));
    Qledpin =xQueueCreate(5,sizeof(uint8_t));
	TaskHandle_t task1_h,task2_h;
	
	xTaskCreate(task1,"process",150,NULL,1,&task1_h);
	xTaskCreate(task2,"handler",150,NULL,1,&task2_h);
	
	
	vTaskStartScheduler();
	
	
	
   
}

