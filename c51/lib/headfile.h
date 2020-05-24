#ifndef __HEADFILE_H
#define __HEADFILE_H

#define CHLED();	P2 &= 0x1f; P2 |= 0x80;
#define CHULN(); 	P2 &= 0x1f; P2 |= 0xa0;
#define CHWEI(); 	P2 &= 0x1f; P2 |= 0xc0;
#define CHDUAN(); 	P2 &= 0x1f; P2 |= 0xe0;
#define CHNONE();	P2 &= 0x1f;

#define uchar unsigned char
#define uint unsigned int

#include <STC15F2K60S2.H>
#include <intrins.h>
#include "onewire.h"
#include "display.h"
#include "system.h"
#include <absacc.h>
#include <stdio.h>
#include "uart.h"

#endif