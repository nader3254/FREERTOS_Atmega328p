/*
 * lab1.c
 *
 * Created: 7/5/2022 4:14:31 AM
 * Author : Nader
 */ 

#define __DELAY_BACKWARD_COMPATIBLE__
#include <avr/io.h>
#include <util/delay.h>
/***** FREERTOS *******/
#include "FreeRTOS.h"
#include "task.h"

#define   BUTTON_DDR       PORTB
#define   BUTTON_pin           0x01

typedef enum
{
	red,
	green,
	blue
	
}color;
static struct seven_segment_type
{
	uint8_t * ddr;
	uint8_t * data_port ;
	
	uint8_t * ctrl_ddr;
	uint8_t * ctrl_port;
	
	uint8_t s0;uint8_t s1;
	
	uint8_t data;
	uint8_t digit1 ;
	uint8_t digit2  ;

}sev;


static  struct  RGBled_type
{
	uint8_t* red_ddr ;
	uint8_t* green_ddr ;
	uint8_t* blue_ddr ;
	
	uint8_t* red_data ;
	uint8_t* green_data ;
	uint8_t* blue_data ;
	
	uint8_t red_pin ;
	uint8_t green_pin ;
	uint8_t blue_pin ;
	
	
	uint8_t red  ;
	uint8_t green;
	uint8_t blue ;

	
	
	}l1;
void init_rgb_led()
{
	//static RGBled_type l1;
	l1.red_ddr    = &DDRB; l1.red_data    = &PORTB ;  l1.red_pin    = 0x08 ;
	l1.green_ddr  = &DDRB; l1.green_data  = &PORTB ;  l1.green_pin  = 0x04 ;
	l1.blue_ddr   = &DDRB; l1.blue_data   = &PORTB ;  l1.blue_pin   = 0x02 ;

	l1.red = 0; l1.green = 0; l1.blue = 0;
	
	*(l1.red_ddr)   |= l1.red_pin  ;  
	*(l1.green_ddr) |= l1.green_pin;
	*(l1.blue_ddr)  |= l1.blue_pin ;
	
	*(l1.red_data)   |= l1.red_pin;
	_delay_ms(500);
	*(l1.green_data) |= l1.green_pin;
    _delay_ms(500);
	*(l1.blue_data)  |= l1.blue_pin;
    _delay_ms(500);
	
	*(l1.blue_data)  &=~ l1.blue_pin;
	_delay_ms(500);
	*(l1.green_data) &=~ l1.green_pin;
	_delay_ms(500);
	*(l1.red_data)   &=~ l1.red_pin;
	_delay_ms(500);
	
}


void init_SevenSegment()
{
	
	//DDRC   =0x0c;
	//PORTC  = 0x0c;
	sev.ddr      =& DDRD ;  sev.data_port =& PORTD ;
	sev.ctrl_ddr =& DDRC ;  sev.ctrl_port =& PORTC ;
	sev.s0 = 0x08  ; sev.s1 = 0x04;     
	
	*(sev.ddr)       = 0xff;
    *(sev.data_port) = 0x00;
	 sev.data=0;
	 
	 
	 *(sev.ctrl_ddr)   |= sev.s0 | sev.s1;
	 *(sev.ctrl_port)  |= sev.s0 | sev.s1;
	 
	  
	 
	*(sev.ctrl_port) = sev.s0  ; 
	 for (int i=0;i<8;i++)
	 {
		 *(sev.data_port) =(1<<i);
		 _delay_ms(100);
	 }
	 _delay_ms(50);
	 //PORTC = 0x00;
	 	 
	*(sev.ctrl_port) = sev.s1  ;  
	 
	
	 for (int i=0;i<8;i++)
	 {
		 *(sev.data_port) =(1<<i);
		 _delay_ms(100);
	 }
	// PORTC = 0x08;
     _delay_ms(50);
	// PORTC = 0x00;
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

void seventask(void)
{
	init_SevenSegment();

	while (1)
	{
		
		
		for (int i=0;i<100;i++)
		{
			for (int j=0;j<50;j++)
			{
				*(sev.ctrl_port) = sev.s0  ; 
				*(sev.data_port) = evaluate(i%10);
				vTaskDelay( pdMS_TO_TICKS(5));
			
				
				*(sev.ctrl_port) = sev.s1  ; 
				*(sev.data_port) = evaluate((i%100)/10);
				vTaskDelay( pdMS_TO_TICKS(5));
				
			}
			
			
			
		}

	}
	
}

void color2pwm(uint8_t color_val,color c,uint16_t frequency)
{
	uint32_t T =  ( (1.0 / frequency) * 1000000);
	
	uint8_t ds=0;
	
	
	ds = (color_val *100)/255;
	uint32_t t_on  = ((ds * T) /100);
	uint32_t t_off = T-t_on;

	switch(c)
	{
		
		case red:
		
		*(l1.red_data)   |= l1.red_pin;
		_delay_us(t_on);
		
		*(l1.blue_data)  &=~ l1.red_pin;
		_delay_us(t_off);
		break;
		
		case green:
		
		*(l1.green_data)   |= l1.green_pin;
		_delay_us(t_on);
		
		*(l1.green_data)  &=~ l1.green_pin;
		_delay_us(t_off);
		break;
		
		case blue:
		
		*(l1.blue_data)   |= l1.blue_pin;
		_delay_us(t_on);
		
		*(l1.blue_data)  &=~ l1.blue_pin;
		_delay_us(t_off);
		break;
	}
	
}

void RGBtask(void)
{
	
	init_rgb_led();
   // TickType_t xLastWakeTime;
   // xLastWakeTime = xTaskGetTickCount(); 

	while (1)
	{
		for (int i=0;i<256;i++)
		{
			 for (int k=0;k<5;k++)
			 {
				color2pwm(i, red,1000);
				//l1.red++;
			 }
		}
		
		for (int i=256;i>0;i--)
		{
			 for (int k=0;k<5;k++)
			 {
			   color2pwm(i, red,1000);
			 }
			//l1.red--;
		}
		//vTaskDelayUntil( &xLastWakeTime, pdMS_TO_TICKS( 1000));
		//  vTaskDelay( pdMS_TO_TICKS(1000));
		_delay_ms(1000);
		  
		  for (int color_v=0;color_v<256;color_v++)
		  {
			   for (int k=0;k<5;k++)
			   {
			     color2pwm(color_v,green ,1000);
			   }
			  
		  }
		  
		  // _delay_ms(100);
		  
		  for (int color_v=255;color_v>0;color_v--)
		  {
			   for (int k=0;k<5;k++)
			   {
			      color2pwm(color_v, green,1000);
			   }
			  
		  }
		  
		  //vTaskDelayUntil( &xLastWakeTime, pdMS_TO_TICKS( 1000));
		 //vTaskDelay( pdMS_TO_TICKS(1000));
			 _delay_ms(1000);
		  for (int color_v=0;color_v<256;color_v++)
		  {
			  for (int k=0;k<5;k++)
			  { 
			    color2pwm(color_v,blue ,1000);
			  }
			  
		  }
		  
		  // _delay_ms(100);
		  
		  for (int color_v=255;color_v>0;color_v--)
		  {
			  for (int k=0;k<5;k++)
			  {
				   color2pwm(color_v, blue,1000);
			  }
			 
			  
		  }
		  
		 //vTaskDelayUntil( &xLastWakeTime, pdMS_TO_TICKS(1000));
	       //vTaskDelay( pdMS_TO_TICKS(1000));
	      _delay_ms(1000);
	}
	
}

int main(void)
{
    //init();
	
	
	
	
	TaskHandle_t seven_task_h;
	TaskHandle_t RGB_task_h;
	
	
	
	xTaskCreate(seventask  , "seven"  , 150 , NULL , 2  , seven_task_h     );
	xTaskCreate(RGBtask    ,"rgbred"  , 300 , NULL , 1  , RGB_task_h       );
	
	
	vTaskStartScheduler();
	
	while(1);
	 
	
   
}

