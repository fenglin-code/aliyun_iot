#include "headfile.h"

uint ms=0;
extern uchar showbuff[];
extern code uchar tab[];
uchar ledval=0x01;
extern bit busy;
uint temp;


int main(void)
{
	system_init();
	Timer0Init();		
	UartInit();	
	temp = rd_temperature();	
    showbuff[4] = tab[temp/1000%10];
	showbuff[5] = tab[temp/100%10] & 0x7f;
	showbuff[6] = tab[temp/10%10];
	showbuff[7] = tab[temp%10];
	EA = 1;
		
	for (;;)
	{
        XBYTE[0x8000] = ledval;
		temp = rd_temperature();
		showbuff[4] = tab[temp/1000%10];
		showbuff[5] = tab[temp/100%10] & 0x7f;
		showbuff[6] = tab[temp/10%10];
		showbuff[7] = tab[temp%10];
        while (ms < 2000);
        ms = 0;
		printf("%d",temp);
	}
}

void isr_timer0(void) interrupt 1
{
	ms++;
	show_xbyte();
}

void isr_uart(void) interrupt 4
{	
    static uchar i;
    static uchar FIFO;
	if (RI)
	{
		FIFO = SBUF;
        showbuff[0] = tab[FIFO/100%10];
        showbuff[1] = tab[FIFO/10%10];
        showbuff[2] = tab[FIFO%10];
		RI = 0;
	}
	if (TI)
	{
        busy = 0;
        if (++i>3) 
		{
            i = 0;
            ledval = _crol_(ledval, 1);
        }
		TI = 0;
	}
}
