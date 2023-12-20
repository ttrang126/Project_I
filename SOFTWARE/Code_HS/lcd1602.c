#include <REGX52.H>
#include "lcd1602.h" 
#include "port.h"
#include "delay.h"

void sendHighNibble (unsigned char Data)  	//Send upper nibble
{
	LCD = (LCD & 0x0F);
	LCD |= (Data & 0xF0);
}

void sendLowNibble (unsigned char Data) 	//Send lower nibble
{
	LCD = (LCD & 0x0F);
	LCD |= (Data << 4);
}

void LCD_Command (char Cmnd)
{
	RS = 0; 			   	//Send Command 
	RW = 0;		   			//Write operation

	sendHighNibble(Cmnd);
	EN = 1;
	delay(1);
	EN = 0; 
	delay(2);

	sendLowNibble(Cmnd);
	EN = 1;
	delay(1);
	EN = 0; 
	delay(5);
}

void LCD_Data (char Data)
{
	RS = 1;		   			  //Send Data
	RW = 0;					  //Write Operation

	sendHighNibble(Data);
	EN = 1;
	delay(1);
	EN = 0;
	delay(2);

	sendLowNibble(Data);
	EN = 1;
	delay(1);
	EN = 0;
	delay(5);
}

void LCD_Clear()  	   			
{
	LCD_Command(0x01);
}

void setCursor(unsigned char row, unsigned char pos)	//Setting up the position of the cursor to LCD1602
{
	if(row == 0) 
		LCD_Command((pos & 0x0F)|0x80);	
	else if(row == 1)
		LCD_Command ((pos & 0x0F|0xC0));
}

void LCD_Char(char c)		  //Print char
{
	LCD_Data(c);
}

void LCD_String(char *str)	  //Print string
{
	while(*str) 
	{
		LCD_Char(*str);
		str++;
	}
}

void LCD_Init()
{
	delay(20);
	LCD_Command(0x02); 			//4bit mode
	delay(10);
	LCD_Command(0x28);			//Initialization of 16x2LCD in 4bit mode
	delay(10);
	LCD_Command(0x0C);			//Display ON Curosr OFF
	delay(10);
	LCD_Command(0x06);			//Auto Increment cursor
	delay(10);
	LCD_Clear();				
	delay(10);
	LCD_Command(0x80); 			//Cursor at home position
	delay(10);
}