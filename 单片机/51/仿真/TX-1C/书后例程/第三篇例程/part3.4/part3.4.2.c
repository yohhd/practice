#include <reg52.h>    		//52ϵ�е�Ƭ��ͷ�ļ�
#define uchar unsigned char
#define uint unsigned int 
sfr WDT_CONTR=0xe1;
sbit led1=P1^0;
void delayms(uint xms)				
{
	uint i,j;
	for(i=xms;i>0;i--)		      //i=xms����ʱԼxms����
		for(j=110;j>0;j--);
}
void main()
{
	WDT_CONTR=0x35;
	led1=0;
	delayms(500);
	led1=1;	
	while(1) 
	{
		delayms(1000);
		WDT_CONTR=0x35;		
	}
}
