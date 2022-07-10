#include "CLCD162.h"


void lcd_command_executer(uint8_t a[],int x);
void lcd_write(uint8_t lcd[],unsigned char ch);
//**************** send commands to lcd ****************//
void lcd_command_executer(uint8_t a[],int x)
{
	int r=x;
	for(int i=9;i>=0;i--)
	{
		if ((r&0x01)!=0)
		{
			out(a[i],'h');
		} 
		else
		{
				out(a[i],'l');
		}
		r=r>>1;
	}
	out(a[10],'h');	
	inp(a[3]);     // Reed busy flag 
	while(a[3]==1);
	out(a[10],'l');
	for (int f=0;f<9;f++)
	{
		out(a[f],'l');
	}
	
}
/****************lcd initializing****************/
void lcd_initialize(uint8_t rt[])
{
	lcd_command_executer(rt,Set_function_8bit_2line);
	lcd_command_executer(rt,Clear_Display);
	lcd_command_executer(rt,Return_home);
	lcd_command_executer(rt,Entry_mode_cursorL);
	lcd_command_executer(rt,Display_on_showcursor_Blink);
}
/**************lcd writing character******************/
void lcd_write(uint8_t lcd[],unsigned char ch)
{
	out(lcd[0],'h');out(lcd[1],'l');
	uint8_t x=ch;
	for(int i=9;i>1;i--)
	{
		if ((x&0x01)!=0)
		{
			out(lcd[i],'h');
		}
		else
		{
			out(lcd[i],'l');
		}
		x=x>>1;
	}
	//PORTA=ch;
	out(lcd[10],'h');_delay_ms(50);
	out(lcd[10],'l');	
}
/********************************/
void lcd_write_string(uint8_t lcd2[],unsigned char * ch0)
{
	int i=0;
	while(ch0[i]!='\0')
	{
		lcd_write(lcd2,ch0[i]);i++;
	}
}
