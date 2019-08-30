#include <reg52.h>    	
#define uchar unsigned char
#define uint unsigned int
unsigned char flag,a,i;
uchar code table[]="I get ";
//uchar code table[]={'I',' ','g','e','t',' '};
void init()
{
	  TMOD = 0x20;
    SCON = 0x50;
    TH1 = 0xFD;
    TL1 = TH1;
    PCON = 0x00;
    EA = 1;
    ES = 1;
    TR1 = 1;
}
void main()
{
	init();
	while(1)
	{
		if(flag==1)
		{
			ES=0;
			for(i=0;i<6;i++)
			{
				SBUF=table[i];
				while(!TI);
				TI=0;
			}
			SBUF=a;
			while(!TI);
			TI=0;
			ES=1;
			flag=0;
		}
	}
}

void ser() interrupt 4
{
	RI=0;
	a=SBUF;
	flag=1;
}

