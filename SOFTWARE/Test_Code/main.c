#include <REGX52.H>
#include "delay.h"
#include "lcd1602.h"
#include "port.h"
#include "hs1101.h"
#include "stdio.h"

unsigned int Frequency = 0;
unsigned short Humidity =0;

unsigned char str[20];


void send_data(void);


void main()
{
	LCD_Init();		/* Initialization of LCD*/
	setCursor(0, 1);
	Frequency = Freq();
	Humidity = Humd(Frequency);
	LCD_String("Humidity: ");
	//sprintf(str, "%3d", Humidity);
	sprintf(str, "%5d", Frequency);
	LCD_String(str);
	LCD_Char('%'); 
	delay(50);		
	while (1); 		/* Infinite loop. */
}
