#include "headfile.h"

bit busy = 0;

void UART1_SendData(uchar dat)
{
    while (busy);
    busy = 1;
    SBUF = dat;    
}

char putchar(char c)
{
	UART1_SendData(c);
	return c;
}