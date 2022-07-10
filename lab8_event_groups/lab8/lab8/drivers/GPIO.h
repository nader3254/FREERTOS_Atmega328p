/*
 * GPIO.h
 *
 * Created: 2/10/2022 4:41:50 PM
 *  Author: ibnha
 */ 
#include <avr/io.h>

#ifndef GPIO_H_
#define GPIO_H_
#define A0 10
#define A1 11
#define A2 12
#define A3 13
#define A4 14
#define A5 15
#define A6 16
#define A7 17
#define B0 20
#define B1 21
#define B2 22
#define B3 23
#define B4 24
#define B5 25
#define B6 26
#define B7 27
#define C0 30
#define C1 31
#define C2 32
#define C3 33
#define C4 34
#define C5 35
#define C6 36
#define C7 37
#define D0 40
#define D1 41
#define D2 42
#define D3 43
#define D4 44
#define D5 45
#define D6 46
#define D7 47
void out(uint8_t a,char b);
void inp(uint8_t a0);
void inp_up(uint8_t a1);
int read(uint8_t a2);
void toggle(uint8_t a3);


#endif /* GPIO_H_ */