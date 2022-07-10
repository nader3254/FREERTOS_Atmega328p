/*
 * blnk.c
 *
 * Created: 7/5/2022 12:30:17 AM
 * Author : Nader
 */ 
#define __DELAY_BACKWARD_COMPATIBLE__
#include <avr/io.h>
#include "util/delay.h"

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
typedef enum
{
	red,
	green,
	blue
	
}color;


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
int main(void)
{
	init_rgb_led();

    while (1) 
    {
	
			for (int color_v=0;color_v<256;color_v++)
			{
			    
				 color2pwm(color_v,red ,1000);
				
			}
			
			//_delay_ms(100);
			
			for (int color_v=255;color_v>0;color_v--)
			{
				color2pwm(color_v, red,1000);
				
			}
			
             _delay_ms(100);
			 
			 
			 
             for (int color_v=0;color_v<256;color_v++)
             {
	             
	             color2pwm(color_v,green ,1000);
	             
             }
             
            // _delay_ms(100);
             
             for (int color_v=255;color_v>0;color_v--)
             {
	             color2pwm(color_v, green,1000);
	             
             }
             
             _delay_ms(100);
		
		    for (int color_v=0;color_v<256;color_v++)
		    {
			    
			    color2pwm(color_v,blue ,1000);
			    
		    }
		    
		   // _delay_ms(100);
		    
		    for (int color_v=255;color_v>0;color_v--)
		    {
			    color2pwm(color_v, blue,1000);
			    
		    }
		    
		    _delay_ms(100);
		
		
		
    
     }

}


/*
	for (int i=0;i<frequency;i++)
	{
		
		
		
		*(l1.red_data)   |= l1.red_pin;
		_delay_us(i);
		
		*(l1.blue_data)  &=~ l1.red_pin;
		_delay_us(frequency-i);

	}
	
	for (int i=frequency;i>0;i--)
	{
		
		
		*(l1.red_data)   |= l1.red_pin;
		_delay_us(i);
		
		*(l1.blue_data)  &=~ l1.red_pin;
		_delay_us(frequency-i);

	}
	
	*/