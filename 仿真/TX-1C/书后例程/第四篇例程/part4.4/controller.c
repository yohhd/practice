#include<STC12C5410AD.H>
#include <intrins.h>
#include "define.h"
#include<STC_EEPROM.H>
#include "ad.h"
#include "writeyejing.h"
#include "pvgz.h"
#include "init.h"

void int_t1() interrupt 3
{
	TH1=(65536-50000)/256; //��ʱ����ʼ��
	TL1=(65536-50000)%256;
	t1_num++;
	t1_numgz++;
	if(t1_num==jcjg)//����ذ�����
	{
		t1_num=0;
		flag_t1=1;		
	}
	if(t1_numgz==jcgzjg)//�����ػָ�����
	{
		t1_numgz=0;
		flag_t1gz=1;
	}	
}
void main()
{
	init();
	while(1)
	{    
		if(flag_pv==1)
		{//����̫���ܵ�ذ�ʱ��������
		   v_temp=Ad_Av(1);	
		   if(v_temp<qy)//����Ƿѹ
			{
				qyd=0;   //Ƿѹָʾ
				delay(1000);
				diqynum=3;
				P1M0=0x87; //00000111
				P1M1=0xc9; //00000111
				fz_off; //�����عر�
				fzd=1;
				flag_fz=0;
				while(!(Ad_Av(1)>=qyhf))
				{//һֱ�ȴ�Ƿѹ�ָ�
					checkpv();//����ذ�
					if(flag_pv==1)
					{
						pwm_1();   //�򿪳��
						cdd=0;   //�򿪳��ָʾ
					}
					fcd_z();//�������
					fcd_j();
					func();
					diqynum--;
					if(diqynum>0)//����ָʾ
					{
						didi(3);
						delay(1000);
					 }
					else
						diqynum=1;
					
				}
				didi(1);//Ƿѹ�ָ�ʱ��������
				fz_on;
				delay(1);
				fzd=0;
				P1M0=0x8f; //00000111
				P1M1=0xc1; //00000111
				flag_fz=1;
				delay(1000);
				qyd=1;
				pwm_a=20;
			} 
			if(v_temp>=qy&&v_temp<=gygd)
			{//����������ѹ����
				qyd=1;   //Ƿѹָʾ�ر�
				if(v_temp<fcdy)
				{
					cdd=0;//�����ָʾ��
					//����ʡȥPWM���Ƴ���
				}
				if(v_temp>fcdy&&v_temp<gddy)
				{
					cdd=0;//�����ָʾ��
					//����ʡȥPWM���Ƴ���
				}
				if(v_temp>gddy)
				{
					cdd=0;//�����ָʾ��
					//����ʡȥPWM���Ƴ���
				}			
			} 
			if(v_temp>gygd)    //�ж��Ƿ��ѹ
			{
				pwm_0();//��ѹ��رճ��
				cdd=1;
		 	}
		}
		else//û��̫���ܵ�ذ��ǽ�������
		{
		   v_temp=Ad_Av(1);	
		   if(v_temp<qy)
			{
				qyd=0;   //Ƿѹָʾ
				delay(1000);
				diqynum=3;
				P1M0=0x87; //00000111
				P1M1=0xc9; //00000111
				fz_off;//Ƿѹ��رո���
				fzd=1;
				flag_fz=0;
				while(!(Ad_Av(1)>=qyhf))
				{  //�ȴ�Ƿѹ�ָ�
					checkpv();//����ذ�
					if(flag_pv==1)
					{
						pwm_1();   //�򿪳��
						cdd=0;   //�򿪳��ָʾ
					}
					fcd_z();//��ⰴ��
					fcd_j();
					func();
					diqynum--;
					if(diqynum>0)//����ָʾ
					{
						didi(3);
						delay(1000);
					 }
					else
						diqynum=1;
				}
				didi(1);
				fz_on; //Ƿѹ�ָ�ʱ���¿�������
				delay(1);
				fzd=0;
				P1M0=0x8f; //00000111
				P1M1=0xc1; //00000111
				flag_fz=1;
				delay(1000);
				qyd=1;
			} 
			if(v_temp>gygd)    //�ж��Ƿ��ѹ
			{
				digynum=3;
				gyd=0;
				P1M0=0x87; //00000111
				P1M1=0xc9; //00000111
				fz_off;   //��ѹ��رո���
				fzd=1;
				flag_fz=0;
				while(!(Ad_Av(1)<=gyhf))
				{//�ȴ���ѹ�ָ�
					fcd_z();//�������
					fcd_j();
					func();
					digynum--;
					if(digynum>0)//����ָʾ
					{
						didi(3);
						delay(1000);
					 }
					else
						digynum=1;
				}	
				didi(1);
				fz_on;//��ѹ�ָ�ʱ��������
				delay(1);
				fzd=0;
				P1M0=0x8f; //00000111
				P1M1=0xc1; //00000111
				flag_fz=1;
				delay(1000);
				gyd=1;
		 	}
		} 
		checkpv();//����ذ��ѹ
		checkgz();//������״̬
		fcd_z();//�������
		fcd_j();
		func();
	 };	
}


