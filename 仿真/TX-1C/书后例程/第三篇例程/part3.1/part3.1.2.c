#include <reg52.h>    		//52ϵ�е�Ƭ��ͷ�ļ�
#define uchar unsigned char
#define uint unsigned int 
sbit led1=P1^0;
uint num;
void main()
{
	TMOD=0x02;//���ö�ʱ��0Ϊ������ʽ2(0000 0010)
	TH0=6;    //װ��ֵ
	TL0=6;
	EA=1;  //�����ж�
	ET0=1; //����ʱ��0�ж�
	TR0=1; //������ʱ��0
	while(1) //����ֹͣ������ȴ��жϷ���
	{
		if(num==3686)		//�������3686�Σ�˵��1��ʱ�䵽
		{
			num=0;			//Ȼ���num��0�����ټ�3686��
			led1=~led1;	    //�÷����״̬ȡ��
		}
	}
}

void T0_time() interrupt 1
{
	num++;			
}