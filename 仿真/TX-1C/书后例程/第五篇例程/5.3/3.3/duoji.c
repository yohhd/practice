//���ڶ��ʹ֮ת��5���Ƕ� 0 45 90 135 180 PWM�ź�����Ϊ20ms��
//���Ƹߵ�ƽ�ĳ���ʱ�伴�ɿ��ƶ��ֹͣ�ƶ��ĽǶȣ�0.5ms-0�� 1-45 1.5-90 2-135 2.5-180 
//���������ǣ�����ʱ����Ƕ��Զ�תΪ0�ȣ����� P3.7��ת��45�ȣ��Ժ�͸������������İ��¶�ת��
#include "reg52.h"
unsigned char count;      //0.5ms������ʶ
sbit pwm =P3^0 ;          //PWM�ź����
sbit jia =P3^7;           //�Ƕ����Ӱ������IO��
sbit jan =P3^6;           //�Ƕȼ��ٰ������IO��
unsigned char jd;         //�Ƕȱ�ʶ
void delay(unsigned char i)//��ʱ
{
  unsigned char j,k;
  for(j=i;j>0;j--)
    for(k=125;k>0;k--);
}

void Time0_Init()          //��ʱ����ʼ��
{
	TMOD = 0x01;           //��ʱ��0�����ڷ�ʽ1    
	IE 	 = 0x82;
	TH0  = 0xfe;
	TL0  = 0x33;		   //11.0592MZ����0.5ms
    TR0=1;                 //��ʱ����ʼ
}

void Time0_Int() interrupt 1 //�жϳ���
{
	TH0  = 0xfe;             //���¸�ֵ
	TL0  = 0x33;

    if(count<jd)              //�ж�0.5ms�����Ƿ�С�ڽǶȱ�ʶ
      pwm=1;                  //ȷʵС�ڣ�PWM����ߵ�ƽ
    else
      pwm=0;                  //����������͵�ƽ

    count=(count+1);          //0.5ms������1
    count=count%40;			  //����ʼ�ձ���Ϊ40 ����������Ϊ20ms
}


void keyscan()              //����ɨ��
{ 
   if(jia==0)               //�Ƕ����Ӱ����Ƿ���
  {
    delay(10);              //������ʱ������
    if(jia==0)              //ȷʵ����
     {
      jd++;                 //�Ƕȱ�ʶ��1
      count=0;              //�������� ��20ms���ڴ��¿�ʼ
      if(jd==6)
        jd=5;               //�Ѿ���180�ȣ��򱣳�
      while(jia==0);        //�ȴ������ſ�
     }
  }

  if(jan==0)                //�Ƕȼ�С�����Ƿ���
  {
    delay(10);
    if(jan==0)
     {
      jd--;                 //�Ƕȱ�ʶ��1
      count=0;
      if(jd==0)
        jd=1;               //�Ѿ���0�ȣ��򱣳�
      while(jan==0);
     }
  }
}

void main()
{
 jd=1;
 count=0; 
 Time0_Init();              
 while(1)
 {
  keyscan();               //����ɨ��
   
 }
}
