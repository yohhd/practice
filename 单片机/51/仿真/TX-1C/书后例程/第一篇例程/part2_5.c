#include <reg52.h>    		//52ϵ�е�Ƭ��ͷ�ļ�
#define uint unsigned int 		//�궨��
sbit led1=P1^0;	     		 //������Ƭ��P1�ڵĵ�һλ
void delayms(uint);				//�����Ӻ���
void main()		      		//������
{
	while(1)		 			 //��ѭ��
	{
		led1=0;					/*������һ�����������*/	
		delayms(200);				//��ʱ200����
		led1=1;					/*�رյ�һ�����������*/	
		delayms(800);				//��ʱ800����
	}	
}
void delayms(uint xms)				
{
	uint i,j;
	for(i=xms;i>0;i--)		      //i=xms����ʱԼxms����
		for(j=110;j>0;j--);
}
