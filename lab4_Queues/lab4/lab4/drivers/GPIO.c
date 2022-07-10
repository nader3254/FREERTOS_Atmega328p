/*
 * GPIO.c
 *
 * Created: 2/10/2022 4:41:33 PM
 *  Author: ibnha
 */ 
#include "GPIO.h";
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
void out(uint8_t a,char b)
{
	for (int i=10;i<48;i++)
	{
		//if (i>=0&&i<18)//for port A
		//{if (i==a){uint8_t tmp =i-10;DDRA |=(1<<tmp);if (b=='h'||b=='H'){PORTA |=(1<<tmp);break;} else{PORTA &=~(1<<tmp);break;}}}
		if (i>=18&&i<28)//for port B
		{if (i==a){uint8_t tmp =i-20;DDRB |=(1<<tmp);if (b=='h'||b=='H'){PORTB |=(1<<tmp);break;} else{PORTB &=~(1<<tmp);break;}}}
		if (i>=28&&i<38)//for port C
		{if (i==a){uint8_t tmp =i-30;DDRC |=(1<<tmp);if (b=='h'||b=='H'){PORTC |=(1<<tmp);break;} else{PORTC &=~(1<<tmp);break;}}}
		if (i>=38&&i<48)//for port D
		{if (i==a){uint8_t tmp =i-40;DDRD |=(1<<tmp);if (b=='h'||b=='H'){PORTD |=(1<<tmp);break;} else{PORTD &=~(1<<tmp);break;}}}
		
	}

}
void inp(uint8_t a0)
{
	for (int i=10;i<48;i++)
	{
		//if (i>=0&&i<18)//for port A
		//{if (i==a0){uint8_t tmp =i-10;DDRA &=~(1<<tmp);}}
		if (i>=18&&i<28)//for port B
		{if (i==a0){uint8_t tmp =i-20;DDRB &=~(1<<tmp);}}
		if (i>=28&&i<38)//for port C
		{if (i==a0){uint8_t tmp =i-30;DDRC &=~(1<<tmp);}}
		if (i>=38&&i<48)//for port D
		{if (i==a0){uint8_t tmp =i-40;DDRD &=~(1<<tmp);}}	
	}
}
void inp_up(uint8_t a1)
{
	for (int i=10;i<48;i++)
	{
		//if (i>=0&&i<18)//for port A
		//{if (i==a1){uint8_t tmp =i-10;DDRA &=~(1<<tmp);PORTA |=(1<<tmp);}}
		if (i>=18&&i<28)//for port B
		{if (i==a1){uint8_t tmp =i-20;DDRB &=~(1<<tmp);PORTB |=(1<<tmp);}}
		if (i>=28&&i<38)//for port C
		{if (i==a1){uint8_t tmp =i-30;DDRC &=~(1<<tmp);PORTC |=(1<<tmp);}}
		if (i>=38&&i<48)//for port D
		{if (i==a1){uint8_t tmp =i-40;DDRD &=~(1<<tmp);PORTD |=(1<<tmp);}}
	}
}
int read(uint8_t a2)
{
	for (int i=10;i<48;i++)
	{
		//if (i>=0&&i<18)//for port A
		//{if (i==a2){uint8_t tmp =i-10;if ((PINA & (1<<tmp))){return 1;} else{return 0;}}}
		if (i>=18&&i<28)//for port B
		{if (i==a2){uint8_t tmp =i-20;if ((PINB & (1<<tmp))){return 1;} else{return 0;}}}
		if (i>=28&&i<38)//for port C
		{if (i==a2){uint8_t tmp =i-30;if ((PINC & (1<<tmp))){return 1;} else{return 0;}}}
		if (i>=38&&i<48)//for port D
		{if (i==a2){uint8_t tmp =i-40;if ((PIND & (1<<tmp))){return 1;} else{return 0;}}}
	}
}
void toggle(uint8_t a3)
{
	for (int i=10;i<48;i++)
	{
		//if (i>=0&&i<18)//for port A
		//{if (i==a3){uint8_t tmp =i-10;PORTA ^=(1<<tmp);}}
		if (i>=18&&i<28)//for port B
		{if (i==a3){uint8_t tmp =i-20;PORTB ^=(1<<tmp);}}
		if (i>=28&&i<38)//for port C
		{if (i==a3){uint8_t tmp =i-30;PORTC ^=(1<<tmp);}}
		if (i>=38&&i<48)//for port D
		{if (i==a3){uint8_t tmp =i-40;PORTD ^=(1<<tmp);}}
	}
}