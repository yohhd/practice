#include <reg52.h>    		//52ϵ�е�Ƭ��ͷ�ļ�
#define uint unsigned int 		//�궨��
sbit led1=P1^0;	     		 //������Ƭ��P1�ڵĵ�һλ
void delay1s();				//�����Ӻ���
void main()		      		//������
{
	while(1)		 			 //��ѭ��
	{
		led1=0;					/*������һ�����������*/	
		delay1s();				//������ʱ�Ӻ���
		led1=1;					/*�رյ�һ�����������*/	
		delay1s();				//������ʱ�Ӻ���
	}	
}
void delay1s()						//�Ӻ�����
{
	uint i,j;
	for(i=500;i>0;i--)		
		for(j=110;j>0;j--);
}

