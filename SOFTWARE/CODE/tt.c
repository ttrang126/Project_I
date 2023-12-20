#include <REGX51.H>
#include<stdio.h>

 sfr LCD = 0x80;
 sbit RS = P0^1;
 sbit RW = P0^2;
 sbit EN = P0^3;
 sbit A = P2^1;
 sfr ADC0804_Data = 0x90;
sbit ADC0804_RD = P3^4;
sbit ADC0804_WR = P3^3;
sbit ADC0804_INTR = P3^2;

unsigned char ADC0804_Read(void)
{
	unsigned char result;
	
	
	ADC0804_WR = 0;
	ADC0804_WR = 1;
	
	while(ADC0804_INTR);
	
	ADC0804_RD = 0;
	result = ADC0804_Data;
	ADC0804_RD = 1;
	
	
	return result;
}

float Cal_Temp(unsigned int ADC_Value)
{
	float Temperature = 0.0;
	unsigned int frac = 0;
	unsigned int temp = 0;
	
	if (ADC_Value < 29)
		Temperature = (ADC_Value - 11) / 1.86982;
	else if ((ADC_Value >= 30) && (ADC_Value < 52))
		Temperature = (ADC_Value - 30) / 2.24137 + 10;
	else if ((ADC_Value >= 52) && (ADC_Value < 78))
		Temperature = (ADC_Value - 52) / 2.59323 + 20;
	else if ((ADC_Value >= 78) && (ADC_Value < 104))
		Temperature = (ADC_Value - 78) / 2.57189 + 30;
	else if ((ADC_Value >= 104) && (ADC_Value < 127))
		Temperature = (ADC_Value - 104) / 2.33659 + 40;
	else if ((ADC_Value >= 127) && (ADC_Value < 156))
		Temperature = (ADC_Value - 127) / 2.91112 + 50;
	else if ((ADC_Value >= 156) && (ADC_Value < 181))
		Temperature = (ADC_Value - 156) / 2.50075 + 60;
	else if ((ADC_Value >= 181) && (ADC_Value < 208))
		Temperature = (ADC_Value - 181) / 2.63397 + 70;
	else if ((ADC_Value >= 208) && (ADC_Value < 231))
		Temperature = (ADC_Value - 208) / 2.35803 + 80;
	
	else if ((ADC_Value >= 231) && (ADC_Value < 255))
		Temperature = (ADC_Value - 231) / 2.31705 + 90;
	
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

void delay(unsigned int ms)
{
    int i,j;
    for(i = 0; i < ms; i++)
    {
        for(j = 0; j < 123; j++);

    }
}
void sendHigh(unsigned char Data){
    LCD = LCD & 0x0F; // XOA 4 BIT CA0 VA GIU LAI 4 BIT THAP
 	LCD |= ( Data & 0xF0 );// LAY 4 BIT CAO
}

void sendLow(unsigned char Data)
{
    LCD = LCD & (0x0F);
    LCD = LCD | (Data << 4); // LAY 4 BIT THAP CUA DATA
}

void LCD_Enable(void)
{
    EN = 0; // LCD NHAN DU LIEU
    delay(3);
    EN = 1; // LCD NGUNG NHAN DU LIEU
    delay(1);

}

void sendCMD(unsigned char cmd)

{
    RW = 0; // LCD O CHE DO WRITE
    RS = 0; //LCD GUI LENH
    
    sendHigh(cmd);
    LCD_Enable();
    sendLow(cmd);
    LCD_Enable();
}

void sendData(unsigned char Data)
{
    RW = 0; // LCD WRITE
    RS = 1; // LCD GUI DATA

    sendHigh(Data);
    LCD_Enable();
    sendLow(Data);
    LCD_Enable();
}

void LCD_Init(void)
{
    delay(50); // LCD ON
    sendCMD(0x01); // xoa toan bo noi dung tren LCD 
    delay(5);
    sendCMD(0x02); // di chuyen con tro ve phia dau man hinh
    delay(5);
    sendCMD(0x28); // Giao tiep 4bit, hien thi 2 dong, kich thuoc 5x7
    delay(5);
    sendCMD(0x06); // Tu dong tanwg Cursoe den vi tri tiep thep
    delay(5);
    sendCMD(0x0C); // LCD ON Cursor OFF
    delay(5);
    sendCMD(0x0E); // LCD ON Cursor ON
    delay(5);
    sendCMD(0x80); // di chuyen Cursor ve dau dong 1
    delay(5);

}

void LCD_clear()
 {
     sendCMD(0x01);
 }

void SetCursor(unsigned short x, unsigned short y)
{
    if(y == 0) 
    {
        sendCMD((x & 0x0F) | 0x80);
    }
    else if(y == 1)
        sendCMD((x & 0x0F) | 0xC0); // cursor xuong dong 2
}

void printChar(char c)
{
    sendData(c);
}

void printString(char *c)
{
    while(*c)
    {
        printChar(*c++);
    }
}

void main()
{
	unsigned int ADC_Value = 0;
	double Temperature = 0;
	unsigned char a[5];
	LCD_Init(); 
  printString("Temp");
delay(1000);
LCD_clear();	
	while(1)
	{
                     //Khoi tao LCD
	  A = 1;
    ADC_Value = ADC0804_Read();
    Temperature = Cal_Temp(ADC_Value);
    sprintf(a, "%3.1f", Temperature);
    printString("Temp:");
    printString(a);
		delay(5000);
		LCD_clear();
	
	}
   


}


