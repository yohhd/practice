#include <reg52.h>    		//52ϵ�е�Ƭ��ͷ�ļ�
#define uchar unsigned char
#define uint unsigned int 
sbit dula=P2^6;		//����U1�������������
sbit wela=P2^7;		//����U2�������������
uchar code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};
uchar num;
void delayms(uint);
void display(uchar shi,uchar ge)  //��ʾ�Ӻ���
{
    dula=1;
	P0=table[shi];    //��ʮλ��ѡ����
	dula=0;
	P0=0xff;		//��λѡ����ǰ�ر�������ʾ����ֹ��λѡ����ʱ
	wela=1;			//ԭ����ѡ����ͨ��λѡ��������ɻ���
	P0=0xfe;		//��λѡ����
	wela=0;
	delayms(5);	//��ʱ
	dula=1;
	P0=table[ge];  //�͸�λ��ѡ����
	dula=0;
	P0=0xff;
	wela=1;
	P0=0xfd;
	wela=0;
	delayms(5);
}
void delayms(uint xms)				
{
	uint i,j;
	for(i=xms;i>0;i--)		      //i=xms����ʱԼxms����
		for(j=110;j>0;j--);
}
void main()
{
	uchar a,b,num1;
	TMOD=0x01; //���ö�ʱ��0Ϊ������ʽ1(0000 0001)
	TH0=(65536-50000)/256;     
	TL0=(65536-50000)%256;
	EA=1;
	ET0=1;
	EX0=1;
	EX1=1;
	TR0=1;
	while(1) 
	{
		if(num>=20)
		{
			num=0;
			num1++;
			if(num1==6)
			{
				ET0=0;
				PCON=0x03;
			}
			a=num1/10;
			b=num1%10;
		}
		display(a,b);
	}
}
void timer0() interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	num++;	
}
void ex_int0() interrupt 0
{
	PCON=0;
	ET0=1;
}
void ex_int1() interrupt 2
{
	PCON=0;
	ET0=1;
}
