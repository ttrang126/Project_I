#include <REGX52.H>
#include "delay.h"
#include "lcd1602.h"
#include "port.h"
#include "hs1101.h"
#include "stdio.h"
#include "adc0804.h"

unsigned int ADC_Value = 0;
double Temperature = 0;

unsigned int Frequency = 0;
unsigned short Humidity =0;

unsigned char str[20];

void main()
{
	LCD_Init();		/* Initialization of LCD*/
	P1 = 0xFF;
	
	while(1) {
	ADC_Value = ADC0804_Read();
	Temperature = Cal_Temp (ADC_Value);
	setCursor(0, 0);
	LCD_String("TEMP: ");
	sprintf (str, "%4.lf", Temperature);
	LCD_String(str);
	if (Temperature >= 10.0)
	{
		LCD_Char (0xDF); 		//Print degree Celius
		LCD_Char ('C');
	}
	else
	{
	 	setCursor(0,9);
		LCD_Char(0xDF);
		LCD_Char('C');
	}

	setCursor(1,0);
	Frequency = Freq();
	Humidity = Humd(Frequency);
	LCD_String("HUMIDITY: ");
	sprintf(str, "%3d", Humidity);
	LCD_String(str);
	LCD_Char('%');
	delay(50);
	LCD_Clear();	
	} 		/* Infinite loop. */
}
