#include <reg52.h>    		//52ϵ�е�Ƭ��ͷ�ļ�
#define uchar unsigned char
#define uint unsigned int 
sbit led1=P1^0;
sbit led2=P1^1;
uint num1,num2;
void main()
{
	TMOD=0x03;//���ö�ʱ��0Ϊ������ʽ3(0000 0011)
	TH0=6;    //װ��ֵ
	TL0=6;
	EA=1;  //�����ж�
	ET0=1; //����ʱ��0�ж�
	ET1=1; //����ʱ��1�ж�
	TR0=1; //������ʱ��0
	TR1=1; //������ʱ��0�ĸ�8λ������
	while(1) //����ֹͣ������ȴ��жϷ���
	{
		if(num1>=3686)		//�������3686�Σ�˵��1��ʱ�䵽
		{
			num1=0;			//Ȼ���num1��0�����ټ�3686��
			led1=~led1;	    //�÷����״̬ȡ��
		}
		if(num2>=1843)		//�������1843�Σ�˵������ʱ�䵽
		{
			num2=0;			//Ȼ���num2��0�����ټ�1843��
			led2=~led2;	    //�÷����״̬ȡ��
		}
	}
}
void TL0_time() interrupt 1
{  
	TL0=6;   //��װ��ֵ
	num1++;			
}void TH0_time() interrupt 3
{
	TH0=6;    //��װ��ֵ
	num2++;			
}
