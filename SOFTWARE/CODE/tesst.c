#include <REGX51.H>


 sfr LCD = 0x80;
 sbit RS = P0^1;
 sbit RW = P0^2;
 sbit EN = P0^3;
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
  
	LCD_Init();
	delay(50);
  while(1){
		printString("Xuan_Mai_cute");
  delay(10000);
	}
	
   


}


