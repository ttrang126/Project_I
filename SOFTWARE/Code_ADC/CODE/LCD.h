#ifndef _LCD_H_
#define _LCD_H_

#include "delay.h"

void sendHigh(unsigned char Data);

void sendLow(unsigned char Data);

void LCD_Enable(void);

void sendCMD(unsigned char cmd);

void sendData(unsigned char Data);

void LCD_Init(void);

void LCD_clear();

void SetCursor(unsigned short x, unsigned short y);

void printChar(char c);

void printString(char *c);


#endif