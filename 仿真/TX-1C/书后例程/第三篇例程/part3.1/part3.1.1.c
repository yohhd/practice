#include <reg52.h>    		//52ϵ�е�Ƭ��ͷ�ļ�
#define uchar unsigned char
#define uint unsigned int 
sbit led1=P1^0;
uchar num;
void main()
{
	TMOD=0x00;//���ö�ʱ��0Ϊ������ʽ0(0000 0000)
	TH0=(8192-4607)/32;//װ��ֵ
	TL0=(8192-4607)%32;
	EA=1;  //�����ж�
	ET0=1; //����ʱ��0�ж�
	TR0=1; //������ʱ��0
	while(1) //����ֹͣ������ȴ��жϷ���
	{
		if(num==200)		//�������200�Σ�˵��1��ʱ�䵽
		{
			num=0;		//Ȼ���num��0�����ټ�200��
			led1=~led1;	//�÷����״̬ȡ��
		}
	}
}

void T0_time() interrupt 1
{
	TH0=(8192-4607)/32;//��װ��ֵ
	TL0=(8192-4607)%32;	
	num++;			
}