#include <reg52.h>    		//52ϵ�е�Ƭ��ͷ�ļ�
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int 
sbit dula=P2^6;		//����U1�������������
sbit wela=P2^7;		//����U2�������������
sbit adwr=P3^6;		//����AD��WR�˿�
sbit adrd=P3^7;		//����AD��RD�˿�
uchar code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};
void delayms(uint xms)				
{
	uint i,j;
	for(i=xms;i>0;i--)		      //i=xms����ʱԼxms����
		for(j=110;j>0;j--);
}

void display(uchar bai,uchar shi,uchar ge)  //��ʾ�Ӻ���
{
  dula=1;
	P0=table[bai];    //�Ͷ�ѡ����
	dula=0;
	wela=1;			//ԭ����ѡ����ͨ��λѡ��������ɻ���
	P0=0x7e;		//��λѡ����
	wela=0;
	delayms(5);	    //��ʱ
	P0=0x00;

	dula=1;
	P0=table[shi];
	dula=0;
	wela=1;
	P0=0x7d;
	wela=0;
	delayms(5);
	P0=0x00;

	dula=1;
	P0=table[ge];
	dula=0;
	wela=1;
	P0=0x7b;
	wela=0;
	delayms(5);
	P0=0x00;
}


void main()		//	������
{

 	uchar a,A1,A2,A3,adval;
	wela=1;
	P0=0x7f;           //��CSADΪ0��ѡͨADCS �Ժ󲻱��ٹ�ADCS
	wela=0;
    while(1)
	{
		adwr=1;
		_nop_();
		adwr=0;			//����ADת��
		_nop_();
		adwr=1;
		for(a=10;a>0;a--)        //TX-1Cʵ���AD����Ƶ�ʽϵͣ���������ת����Ҫ������ʱ������ת��
		{                        //�������ʾ���ַ������ԭ��Ҳ��Ϊ���ӳ�ת��ʱ��                                                                                                                                                                                                                           
			display(A1,A2,A3);
		}
		P1=0xff;                    //��ȡP1��֮ǰ�ȸ���дȫ1 
		adrd=1;                    //ѡͨADCS
		_nop_();	
		adrd=0;                     //AD��ʹ��
		_nop_();
		adval=P1;			//AD���ݶ�ȡ����P1��
		adrd=1;
		A1=adval/100;		//�ֳ��٣�ʮ���͸�λ
		A2=adval%100/10;
		A3=adval%10;
	 }
}