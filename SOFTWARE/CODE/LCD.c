#include <REGX51.H>
#include <stdio.h>

sfr LCD = 0x80;
sbit RS = P0^1;
sbit RW = P0^2;
sbit EN = P0^3;
sbit A = P2^1;
sfr ADC0804_Data = 0x90;
sbit ADC0804_RD = P3^4;
sbit ADC0804_WR = P3^3;
sbit ADC0804_INTR = P3^2;
sbit HS = P3^5;

void delay(unsigned int ms)
{
    int i,j;
    for(i = 0; i < ms; i++)
    {
        for(j = 0; j < 123; j++);

    }
}

code int hs1101[101] = {
						7351, 7338, 7325, 7312, 7299, 7286, 7273, 7260, 7247, 7234, 
						7221, 7208, 7195, 7182, 7169, 7156, 7143, 7130, 7117, 7104, 
						7091, 7078, 7065, 7052, 7039, 7026, 7013, 7000, 6987, 6974, 
						6961, 6948, 6935, 6922, 6909, 6896, 6883, 6870, 6857, 6844, 
						6831, 6818, 6805, 6792, 6779, 6766, 6753, 6740, 6727, 6714, 
						6701, 6688, 6675, 6662, 6649, 6636, 6623, 6610, 6597, 6584, 
						6571, 6558, 6545, 6532, 6519, 6506, 6493, 6480, 6467, 6454, 
						6441, 6428, 6415, 6402, 6389, 6376, 6363, 6350, 6337, 6324, 
						6311, 6298, 6285, 6272, 6259, 6246, 6233, 6220, 6207, 6194, 
						6181, 6168, 6155, 6142, 6129, 6116, 6103, 6090, 6077, 6064, 6051
						};

unsigned int Freq(void) 
{

	unsigned int pulses = 0;
	TMOD = 0x51;
	HS = 1;
	TL1 = 0;
	TH1 = 0;
	TR1 = 1;
	delay(100);
	TR1 = 0;
	pulses = (TH1 * (0x100)) + TL1;
	pulses = pulses * 10;
	return pulses;
}
					   

unsigned short Humd(unsigned int Frequency)
{
	int i;
	for (i = 0; i < 101; i++) 
	{
		if((Frequency) > hs1101[i]) return i;
	}	
	return 100;
}

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
	unsigned char a[20];
	unsigned char b[20];
	unsigned int Frequency = 0;
  	unsigned short Humidity =0;
	LCD_Init();
  	P1 = 0xFF;	
  	printString("Temp");
  	delay(1000);
 	LCD_clear();	
	while(1)
	{
                     //Khoi tao LCD
	A = 1;
    ADC_Value = ADC0804_Read();
    Temperature = Cal_Temp(ADC_Value);
	SetCursor(0,0);
    sprintf(b, "%4.1f", Temperature);
    printString("Temp:");
    printString(b);
		if(Temperature >= 10.0)
		{
			printChar(0xDF); // ky hieu d? C
			printChar('C');
		}
		else
		{
			SetCursor(9, 0);
			printChar(0xDF);
			printString("C ");
		}
		SetCursor(0,1);
		Frequency = Freq();
	  	Humidity = Humd(Frequency);
		printString("Humidity:");
		sprintf(a, "%3d", Humidity);
		printString(a);
		printChar('%');
		delay(5000);
		LCD_clear();
	
	}
   


}


