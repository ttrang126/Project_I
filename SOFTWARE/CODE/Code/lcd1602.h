#ifndef _LCD_1602_H_
#define _LCD_1602_H_

void sendHighNibble (unsigned char Data);
void sendLowNibble (unsigned char Data);
void LCD_Command (char Cmnd);
void LCD_Data (char Data);
void LCD_Clear();
void setCursor(unsigned char row, unsigned char pos);
void LCD_Char(char c);
void LCD_String(char *str);
void LCD_Init();

#endif