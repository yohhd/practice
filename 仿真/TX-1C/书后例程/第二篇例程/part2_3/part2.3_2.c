#include <reg52.h>    	
#define uchar unsigned char
#define uint unsigned int
sbit dula=P2^6;		//����U1�������������
sbit wela=P2^7;		//����U2�������������
sbit dawr=P3^6;		//����DA��WR�˿�
sbit dacs=P3^2;		//����DA��CS�˿�
sbit beep=P2^3;		//����������˿�
void delayms(uint xms)				
{
	uint i,j;
	for(i=xms;i>0;i--)		      //i=xms����ʱԼxms����
		for(j=110;j>0;j--);
}

void main()
{
	uchar val,flag;
	dula=0;
	wela=0;
	dacs=0;
	dawr=0;
	P0=0;
	while(1)
	{
		if(flag==0)
		{
			val+=5;
			P0=val;		//ͨ��P0�ڸ�DA���ݿڸ�ֵ
			if(val==255)
			{
				flag=1;
		  		beep=0;
				delayms(100);
				beep=1;
			}
			delayms(50);
		}
		else
		{
			val-=5;
			P0=val;		//ͨ��P0�ڸ�DA���ݿڸ�ֵ
			if(val==0)
			{
				flag=0;
		  		beep=0;
				delayms(100);
				beep=1;
			}
			delayms(50);
		}		
	}
}
