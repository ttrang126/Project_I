#ifndef _PORT_H_
#define _PORT_H_

#include "reg52.h"
#define FREQ_OSC 11059200ul

 sfr LCD = 0x80;
 sbit RS = P0^1;
 sbit RW = P0^2;
 sbit EN = P0^3;
 sbit A = P2^1;

#endif