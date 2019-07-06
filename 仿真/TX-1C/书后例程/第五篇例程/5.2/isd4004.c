#include <reg52.h>
#include <intrins.h> 
sbit cs_4004 = P0^0;
sbit sclk_4004= P0^3;
sbit mosi_4004= P0^1;
sbit miso_4004= P0^2;
sbit rac_4004 = P0^4;
sbit int_4004 = P0^5;
void delay(unsigned int i) //��ʱ����
{
	while(i--);
}
void stopmode() //ֹͣ
{
	unsigned char m,i,j;
	cs_4004=1;
	sclk_4004=0;
	cs_4004=0;
	m=0x30;
	for(i=0;i<8;i++)
	{
		m=_cror_(m,1);
		j=m<<1;
		mosi_4004=CY;
		sclk_4004=0;
		sclk_4004=1;
	}
	cs_4004=1;
}
void powerdown() //�µ�
{
	unsigned char m,i,j;
	cs_4004=1;
	sclk_4004=0;
	cs_4004=0;
	m=0x10;
	for(i=0;i<8;i++)
	{
		m=_cror_(m,1);
		j=m<<1;
		mosi_4004=CY;
		sclk_4004=0;
		sclk_4004=1;
	}
	cs_4004=1;
}
void powerup()// �ϵ�
{
	unsigned char m,i,j;
	cs_4004=1;
	sclk_4004=0;
	cs_4004=0;
	m=0x20;
	for(i=0;i<8;i )
	{
		m=_cror_(m,1);
		j=m<<1;
		mosi_4004=CY;
		sclk_4004=0;
		sclk_4004=1;
	}
	cs_4004=1;
}
void record4004(unsigned int address)
{// ¼�� address--¼����ַ 0---2400
	unsigned char i,m,j;
	unsigned int datasoute=0;	
	powerup();
	delay(5118);//�ϵ���ʱ
	powerup();
	delay(5118);//�ϵ���ʱ
	delay(5118);//�ϵ���ʱ
	cs_4004=1;
	sclk_4004=0;
	m=0xa0;
	cs_4004=0;
	for(i=0;i<16;i++)
	{
		address=_iror_(address,1);
		datasoute=address<<1;
		mosi_4004=CY;
		sclk_4004=0;
		sclk_4004=1;
	}
	for(i=0;i<8;i++)
	{
		m=_cror_(m,1);
		j=m<<1;
		mosi_4004=CY;
		sclk_4004=0;
		sclk_4004=1;
	}
	cs_4004=1;
	sclk_4004=0;
	m=0xb0;
	cs_4004=0;
	for(i=0;i<8;i++)
	{
		m=_cror_(m,1);
		j=m<<1;
		mosi_4004=CY;
		sclk_4004=0;
		sclk_4004=1;
	}
	cs_4004=1;
	P0=0xff;
	datasoute=0;
	while(int_4004==1) //�洢��ַ���б�־
	{
		if(rac_4004)//��¼����¼����ռ������(Ҳ���Ǳ���¼���ж��)
		{
			delay(20000);
			datasoute++; 
		}
// ������Ӧ�ü����Լ��ĳ��򣬾���¼���˳�����
	}
}//while end;
void audioout(unsigned int address) //��������
{
	unsigned char i,m,j;
	unsigned int datasoute;
	powerup();
	cs_4004=1;
	sclk_4004=0;
	cs_4004=0;
	m=0xe0;
	for(i=0;i<16;i++)
	{
		address=_iror_(address,1);
		datasoute=address<<1;
		sclk_4004=0;
		mosi_4004=CY;
		sclk_4004=1;
	}
	for(i=0;i<8;i++)
	{
		m=_cror_(m,1);
		j=m<<1;
		sclk_4004=0;
		mosi_4004=CY;
		sclk_4004=1;
	}
	cs_4004=1;
	sclk_4004=0;
	m=0xf0;
	cs_4004=0;
	for(i=0;i<8;i )
	{
		m=_cror_(m,1);
		j=m<<1;
		sclk_4004=0;
		mosi_4004=CY;
		sclk_4004=1;
	}
	cs_4004=1;
	P0=0xff;
	while(int_4004==1)
	{
	}
}
void main()
{
	record4004(0);
	audioout(0);
	while(1);
}