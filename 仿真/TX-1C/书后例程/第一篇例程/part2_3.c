#include <reg52.h>    //52ϵ�е�Ƭ��ͷ�ļ�
#define uint unsigned int //�궨��
sbit led1=P1^0;	      //������Ƭ��P1�ڵĵ�һλ
uint i,j;
void main()		      //������
{
	while(1)		  //��ѭ��
	{
		led1=0;					/*������һ�����������*/	
		for(i=1;i>0;i--)		//��ʱ
			for(j=110;j>0;j--);
		led1=1;					/*�رյ�һ�����������*/	
		for(i=1000;i>0;i--)		//��ʱ
			for(j=110;j>0;j--);		
	}	
} 