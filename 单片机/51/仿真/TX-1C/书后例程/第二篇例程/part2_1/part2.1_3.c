#include<reg52.h>

#define uint unsigned int
#define uchar unsigned char

sbit wela=P2^7;
sbit dula=P2^6;

uchar num;

uchar code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};

void delayms(uint xms);

void main()
{
	while(1)
	{
		dula=1;
		P0=table[1];
		dula=0;
	 	wela=1;
		P0=0xfe;
		wela=0;
		delayms(5);
		P0=0x00;
		
		dula=1;
		P0=table[2];
		dula=0;
	 	wela=1;
		P0=0xfd;
		wela=0;
		delayms(5);
		P0=0x00;
		
		dula=1;
		P0=table[3];
		dula=0;
	 	wela=1;
		P0=0xfb;
		wela=0;
		delayms(5);
		P0=0x00;

		dula=1;
		P0=table[4];
		dula=0;
	 	wela=1;
		P0=0xf7;
		wela=0;
		delayms(5);
		P0=0x00;

		dula=1;
		P0=table[5];
		dula=0;
	 	wela=1;
		P0=0xef;
		wela=0;
		delayms(5);
		P0=0x00;

		dula=1;
		P0=table[6];
		dula=0;
	 	wela=1;
		P0=0xdf;
		wela=0;
		delayms(5);
		P0=0x00;
	}
}
void delayms(uint xms)
{
	uint i,j;
	for(i=xms;i>0;i--)
		for(j=110;j>0;j--);
				
}