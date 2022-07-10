#include <avr/io.h>
#include "GPIO.h"
#include "avr/delay.h"
#ifndef CLCD162_H_
#define CLCD162_H_
#define Clear_Display 1
#define Return_home 2
#define Entry_mode_cursorL 6
#define Entry_mode_cursorR 4
#define Entry_mode_shiftR 7
#define Entry_mode_shiftL 5
#define Display_on_showcursor_noBlink 14
#define Display_on_showcursor_Blink 15
#define Display_on_hidecursor_noBlink 12
#define Display_off 0
#define Display_shiftR 28
#define Display_shiftl 24
#define Display_cursorR 20
#define Display_cursorl 16
#define Set_function_8bit_1line 48
#define Set_function_4it_1line 32
#define Set_function_8bit_2line 56
#define Set_function_4it_2line 40
void lcd_command_executer(uint8_t a[],int x);
void lcd_initialize(uint8_t rt[]);
void lcd_write(uint8_t lcd[] ,unsigned char ch);
void lcd_write_string(uint8_t lcd2[],unsigned char * ch0);

#endif /* CLCD162_H_ */