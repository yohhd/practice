#include <reg52.h>    		//52ϵ�е�Ƭ��ͷ�ļ�
#include <intrins.h>
#define uint unsigned int 		//�궨��
#define uchar unsigned char
void delayms(uint);				//�����Ӻ���
uchar aa;
void main()		      		//������
{
	aa=0xfe;					//����ֵ11111110 
	while(1)		 			 //��ѭ��
	{
		P1=aa;
		delayms(500);             //��ʱ500����
		aa=_crol_(aa,1);        //��aaѭ������1λ���ٸ���aa
	}	
}
void delayms(uint xms)				
{
	uint i,j;
	for(i=xms;i>0;i--)		      //i=xms����ʱԼxms����
		for(j=110;j>0;j--);
}
