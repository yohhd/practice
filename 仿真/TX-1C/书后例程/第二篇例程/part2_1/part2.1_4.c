#include<reg52.h>

#define uint unsigned int 
#define uchar unsigned char

sbit led1=P1^0;
uchar num=0;

void main()
{
	TMOD|=0X01;
	TH0=(65536-45872)/256;
	TL0=(65536-45872)%256;
	EA=1;
	ET0=1;
	TR0=1;
	while(1);
}

void T0_time() interrupt 1
{
	TH0=(65536-45872)/256;
	TL0=(65536-45872)%256;
	num++;
	if(num==20)
	{
		num=0;
		led1=~led1;
	}
}