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
void display(uchar num)
{
	P0=table[num]; //��ʾ����ֻ�Ͷ�ѡ����
	dula=1;
	dula=0;
}
void main()
{
	TMOD=0x20;
	TH1=0xfd;
	TL1=0xfd;
	TR1=1;
	REN=1;
	SM0=0;
	SM1=1;	
	EA=1;
	ES=1;
	P0=0xc0;//λѡ�����������
	wela=1;
	wela=0;
	while(1);//�ȴ������жϲ�����Ȼ�������ʾ
}
void ser() interrupt 4
{
	uchar a;
	RI=0;
	a=SBUF;
	display(a);
}