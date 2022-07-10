/*
 * uart.c
 *
 * Created: 3/15/2022 1:42:12 AM
 *  Author: Nader
 */ 
#include "uart.h" 


void UART_init()
{
	  uint16_t baud_config = 103;                             //for 16 MHZ => 115200 Baud Rate   
	  UCSR0C |= (1<<UCSZ01)   |  (1<<UCSZ00) ;               //data size 8 bit       
	  UBRR0L  = (uint8_t) baud_config;
	  UBRR0H  = (uint8_t) (baud_config>>8);
	  UCSR0B |= (1<<TXEN0) |  (1<<RXEN0) ;	
	
	//UCSRC0 |= (1 << URSEL);                          //enable writing UCSRC
	//UCSR0C |= ((1<< UCSZ0) | (1<<UCSZ1));           
	//UCSR0C |= (1 << UPM1);                         //even parity check
	//UCSR0C |= (1 << URSEL);                       //disable writing UCSRC
	//UBRR0L |= (uint8_t) x;  
	//UBRR0L |= (uint8_t) (x>>8);    */             //for 16 MHZ => 115200 Baud Rate 
}

void UATR_SEND(char x )
{

	
	
	while (!(UCSR0A & (1<<UDRE0)));
	UDR0 = x;
	
	
	
/*	while ( !(UCSRA & (1<<UDRE)) );
	UDR = x;
	UCSRB |= (1 << TXEN);  
	while (!(UCSRA & (1<<TXC)) );
	//UCSRB &= ~(1 << TXEN);  
	*/
	
}

char UART_recieve()
{
	

	
	while(!(UCSR0A & (1<<RXC0)) );
	
	return  UDR0;
	
	
	
	/*UCSRB |= (1 << RXEN);
	while (!(UCSRA & (1<<RXC)));
	char x = (char) UDR ;
   
   return x;*/
	//return 'a';
}