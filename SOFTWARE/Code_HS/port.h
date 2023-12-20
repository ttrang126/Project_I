#ifndef _PORT_H
#define _PORT_H

#define FREQ_OSC 11059200ul

sfr LCD = 0x80;
sbit RS = P0^1;
sbit RW = P0^2;
sbit EN = P0^3;
sbit LCD_D4 = P0^4;
sbit LCD_D5 = P0^5;
sbit LCD_D6 = P0^6;
sbit LCD_D7 = P0^7;

sfr ADC_Data = 0x90;
sbit ADC_INTR = P3^2;
sbit ADC_WR = P3^3;
sbit ADC_RD = P3^4;

sbit HS1101 = P3^5;

#endif