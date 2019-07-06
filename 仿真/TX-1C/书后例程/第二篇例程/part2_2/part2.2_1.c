#include <reg52.h>    		//52ϵ�е�Ƭ��ͷ�ļ�
#define uchar unsigned char
#define uint unsigned int 
sbit key1=P3^4;
sbit key2=P3^5;
sbit key3=P3^6;
sbit key4=P3^7;
sbit dula=P2^6;		//����U1�������������
sbit wela=P2^7;		//����U2�������������
uchar code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};
void delayms(uint);
uchar numt0,num;
void display(uchar numdis)  //��ʾ�Ӻ���
{
	uchar shi,ge;         //���������ֱ�Ҫ��ʾ����
	shi=numdis/10;
	ge=numdis%10;

  dula=1;
	P0=table[shi];    //��ʮλ��ѡ����
	dula=0;
	wela=1;			//ԭ����ѡ����ͨ��λѡ��������ɻ���
	P0=0xfe;		//��λѡ����
	wela=0;
	delayms(5);	//��ʱ
	P0=0x00;

	dula=1;
	P0=table[ge];  //�͸�λ��ѡ����
	dula=0;
	wela=1;
	P0=0xfd;
	wela=0;
	delayms(5);
	P0=0x00;
}
void delayms(uint xms)				
{
	uint i,j;
	for(i=xms;i>0;i--)		      //i=xms����ʱԼxms����
		for(j=110;j>0;j--);
}
void init()    //��ʼ������
{
	TMOD=0x01;//���ö�ʱ��0Ϊ������ʽ1(0000 0001)
	TH0=(65536-45872)/256;//װ��ֵ50msһ���ж�
	TL0=(65536-45872)%256;
	EA=1;  //�����ж�
	ET0=1; //����ʱ��0�ж�	
}
void keyscan()
{
	if(key1==0)
	{
		delayms(10);
		if(key1==0)
		{
			num++;
			if(num==60)//����60ʱ���¹�0
				num=0;
			while(!key1);//�ȴ������ͷ�	
		}
	}
	if(key2==0)
	{
		delayms(10);
		if(key2==0)
		{
			if(num==0)//����0ʱ���¹�60
				num=60;
			num--;	
			while(!key2);
		}
	}
	if(key3==0)
	{
		delayms(10);
		if(key3==0)
		{
			num=0;  //��0
			while(!key3);	
		}
	}
	if(key4==0)
	{
		delayms(10);
		if(key4==0)
		{
			while(!key4);
			TR0=~TR0;//������ֹͣ��ʱ��0	
		}
	}
}
void main()
{
	init();//��ʼ������
	while(1) 
	{
		keyscan();
		display(num);
	}
}
void T0_time() interrupt 1
{
	TH0=(65536-45872)/256;//��װ��ֵ
	TL0=(65536-45872)%256;	
	numt0++;	
	if(numt0==20)		//�������20�Σ�˵��1��ʱ�䵽
	{
		numt0=0;		//Ȼ���num��0�����ټ�20��
		num++;
		if(num==60)
			num=0;
	}		
}


