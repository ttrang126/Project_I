#include <REGX52.H>
#include "adc0804.h"
#include "delay.h"
#include "port.h"

unsigned char ADC0804_Read(void) 
{
 	unsigned char result;

	ADC_WR = 0;
	ADC_WR = 1;

	while(ADC_INTR);

	ADC_RD = 0;
	result = ADC_Data;
	ADC_RD = 1;

	return result;
}

float Cal_Temp(unsigned int ADC_Value)
{
	float Temperature = 0.0;
	unsigned int frac = 0;
	unsigned int temp = 0;
  if (ADC_Value < 31)
		Temperature = (ADC_Value - 11) / 1.86982;
	else if ((ADC_Value >= 31) && (ADC_Value < 54))
		Temperature = (ADC_Value - 31) * 0.4299966 + 5;
	else if ((ADC_Value >= 54) && (ADC_Value < 74))
		Temperature = (ADC_Value - 54) * 0.49640 + 15;
	else if ((ADC_Value >= 74) && (ADC_Value < 85))
		Temperature = (ADC_Value - 74) * 0.48857 + 25;
	else if ((ADC_Value >= 85) && (ADC_Value < 97))
		Temperature = (ADC_Value - 85) * 0.416667 + 30;
	else if ((ADC_Value >= 97) && (ADC_Value < 110))
		Temperature = (ADC_Value - 97) * 0.38461 + 35;
	else if ((ADC_Value >= 110) && (ADC_Value < 116))
		Temperature = (ADC_Value - 110) * 1.5669 + 40;
	else if ((ADC_Value >= 116) && (ADC_Value < 125))
		Temperature = (ADC_Value - 116) * 1.11408 + 50;
	else if ((ADC_Value >= 125) && (ADC_Value < 165))
		Temperature = (ADC_Value - 125) * 0.37136 + 60;
	else if ((ADC_Value >= 165) && (ADC_Value < 173))
		Temperature = (ADC_Value - 165) * 0.632511 + 75;
	else if ((ADC_Value >= 173) && (ADC_Value < 186))
		Temperature = (ADC_Value - 173) * 0.80032 + 80;
	else if ((ADC_Value >= 186) && (ADC_Value < 190))
		Temperature = (ADC_Value - 186) * 0.39215 + 90;
	else if ((ADC_Value >= 190) && (ADC_Value < 255))
		Temperature = (ADC_Value - 190) * 0.424886 + 91.6;
	temp = (unsigned int)(Temperature * 10);
	Temperature = (double)temp / 10;
	frac = temp % 10;

	if (frac < 3)
	{
		Temperature -= (double)(frac) / 10;
	}
	else if ((frac >= 3) && (frac <= 7))
	{
		Temperature += (5 - (double)frac) / 10;
	}
	else
	{
		Temperature += (double)(10 - frac) / 10;
	}
	
	
  return Temperature;
}