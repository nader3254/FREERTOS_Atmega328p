/*
 * uart.h
 *
 * Created: 3/15/2022 1:42:33 AM
 *  Author: Nader
 */ 
#include <avr/io.h> 


#ifndef UART_H_
#define UART_H_




void UATR_SEND(char x );
void UART_init();
char UART_recieve();

#endif /* UART_H_ */