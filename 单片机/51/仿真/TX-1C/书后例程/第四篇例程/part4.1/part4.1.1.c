//����TX-1Cʵ�����ʵ�ʾ���Ϊ11.0592M��
//����Ϊ�˷������ʱ��,���Ǽ��辧��Ϊ12M.
#include<reg52.h>//����52��Ƭ��ͷ�ļ�
#define uchar unsigned char 
#define uint unsigned int
#include"24c02.h"
sbit dula=P2^6; //���������������
sbit wela=P2^7;
sbit rs=P3^5;  //����1602Һ��RS��
sbit lcden=P3^4;//����1602Һ��LCDEN��
sbit s1=P3^0;   //���尴��--���ܼ�
sbit s2=P3^1;	//���尴��--���Ӽ�
sbit s3=P3^2;	//���尴��--��С��
sbit rd=P3^7;
sbit beep=P2^3; //�����������
uchar count,s1num;
char miao,shi,fen;
uchar code table[]="  2008-9-30 MON";//�����ʼ�ϵ�ʱҺ��Ĭ����ʾ״̬
void delay(uint z)  //��ʱ����
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}
void di()//��������������
{
	beep=0;
	delay(100);
	beep=1;
}
void write_com(uchar com)//Һ��д�����
{
	rs=0;
	lcden=0;
	P0=com;
	delay(5);
	lcden=1;
	delay(5);
	lcden=0;	
}
void write_date(uchar date)//Һ��д���ݺ���
{
	rs=1;
	lcden=0;
	P0=date;
	delay(5);
	lcden=1;
	delay(5);
	lcden=0;	
}
void write_sfm(uchar add,uchar date)//дʱ���뺯��
{
	uchar shi,ge;
	shi=date/10;//�ֽ�һ��2λ����ʮλ�͸�λ
	ge=date%10;
	write_com(0x80+0x40+add);//������ʾλ��
	write_date(0x30+shi);//��ȥҺ����ʾʮλ
	write_date(0x30+ge); //��ȥҺ����ʾ��λ
}
void init()//��ʼ������
{
	uchar num;
	rd=0;  //��������󰴼���4��һ���õ����Էֽ����������
	dula=0;//�ر�������������ˣ���ֹ����Һ��ʱ����ܻ������
	wela=0;
	lcden=0;
	fen=0; //��ʼ���ֱ���ֵ
	miao=0;
	shi=0;
	count=0;
	s1num=0;
	init_24c02();
	write_com(0x38);//��ʼ��1602Һ��
	write_com(0x0c);
	write_com(0x06);
	write_com(0x01);
	write_com(0x80);//������ʾ��ʼ����
	for(num=0;num<15;num++)//��ʾ����������
		{
			write_date(table[num]);
			delay(5);
		}
		write_com(0x80+0x40+6);//д��ʱ����ʾ���ֵ�����ð��
		write_date(':');
		delay(5);
		write_com(0x80+0x40+9);
		write_date(':');
		delay(5);
	miao=read_add(1);//�״��ϵ��AT24C02�ж�ȡ���洢������
	fen=read_add(2);
	shi=read_add(3);
	write_sfm(10,miao);//�ֱ���ȥҺ����ʾ
	write_sfm(7,fen);
	write_sfm(4,shi);
	TMOD=0x01;//���ö�ʱ��0����ģʽ1
	TH0=(65536-50000)/256;//��ʱ��װ��ֵ
	TL0=(65536-50000)%256;
	EA=1;	//�����ж�
	ET0=1;	//����ʱ��0�ж�
	TR0=1;	//������ʱ��0
}
void keyscan()//����ɨ�躯��
{
	if(s1==0)	
	{
		delay(5);
		if(s1==0)//ȷ�Ϲ��ܼ�������
		{	s1num++;//���ܼ����´�����¼
			while(!s1);//�ͷ�ȷ��
			di();//ÿ���а����ͷŷ�������������
			if(s1num==1)//��һ�α�����ʱ
			{
				TR0=0;  //�رն�ʱ��
				write_com(0x80+0x40+10);//��궨λ����λ��
				write_com(0x0f); //��꿪ʼ��˸
			}
			if(s1num==2)//�ڶ��ΰ��¹����˸��λ������λ��
			{
				write_com(0x80+0x40+7);
			}
			if(s1num==3)//�����ΰ��¹����˸��λ��Сʱλ��
			{
				write_com(0x80+0x40+4);
			}
			if(s1num==4)//���Ĵΰ���
			{
				s1num=0;//��¼����������
				write_com(0x0c);//ȡ�������˸
				TR0=1;	//������ʱ��ʹʱ�ӿ�ʼ��
			}		
		}
	}
	if(s1num!=0)//ֻ�й��ܼ������º����Ӻͼ�С������Ч
	{
		if(s2==0)
		{
			delay(5);
			if(s2==0)//���Ӽ�ȷ�ϱ�����
			{
				while(!s2);//�����ͷ�
				di();//ÿ���а����ͷŷ�������������
				if(s1num==1)//�����ܼ���һ�ΰ���
				{
					miao++; //��������1
					if(miao==60)//����60������
						miao=0;
					write_sfm(10,miao);//ÿ����һ����Һ����ʾһ��
					write_com(0x80+0x40+10);//��ʾλ�����»ص����ڴ�
					write_add(1,miao);	//���ݸı���������24C02
				}
				if(s1num==2)//�����ܼ��ڶ��ΰ���
				{
					fen++;//��������Ӽ�1
					if(fen==60)//����60������
						fen=0;
					write_sfm(7,fen);//ÿ����һ����Һ����ʾһ��
					write_com(0x80+0x40+7);//��ʾλ�����»ص����ڴ�
					write_add(2,fen);//���ݸı���������24C02
				}
				if(s1num==3)//�����ܼ������ΰ���
				{
					shi++;//�����Сʱ��1
					if(shi==24)//����24������
						shi=0;
					write_sfm(4,shi);;//ÿ����һ����Һ����ʾһ��
					write_com(0x80+0x40+4);//��ʾλ�����»ص����ڴ�
					write_add(3,shi);//���ݸı���������24C02
				}
			}
		}
		if(s3==0)
		{
			delay(5);
			if(s3==0)//ȷ�ϼ�С��������
			{
				while(!s3);//�����ͷ�
				di();//ÿ���а����ͷŷ�������������
				if(s1num==1)//�����ܼ���һ�ΰ���
				{
					miao--;//��������1
					if(miao==-1)//����������������������Ϊ59
						miao=59;
					write_sfm(10,miao);//ÿ����һ����Һ����ʾһ��
					write_com(0x80+0x40+10);//��ʾλ�����»ص����ڴ�
					write_add(1,miao);//���ݸı���������24C02
				}
				if(s1num==2)//�����ܼ��ڶ��ΰ���
				{
					fen--;//��������Ӽ�1
					if(fen==-1)//����������������������Ϊ59
						fen=59;
					write_sfm(7,fen);//ÿ����һ����Һ����ʾһ��
					write_com(0x80+0x40+7);//��ʾλ�����»ص����ڴ�
					write_add(2,fen);//���ݸı���������24C02
				}
				if(s1num==3)//�����ܼ��ڶ��ΰ���
				{
					shi--;//�����Сʱ��1
					if(shi==-1)//����������������������Ϊ23
						shi=23;
					write_sfm(4,shi);//ÿ����һ����Һ����ʾһ��
					write_com(0x80+0x40+4);//��ʾλ�����»ص����ڴ�
					write_add(3,shi);//���ݸı���������24C02
				}
			}
		}
	}
}
void main()//������
{
	init();//���ȳ�ʼ��������
	while(1)//�����������ѭ��
	{
		keyscan();//��ͣ�ļ�ⰴ���Ƿ񱻰���
	}
}
void timer0() interrupt 1//��ʱ��0�жϷ������
{
	TH0=(65536-50000)/256;//�ٴ�װ��ʱ����ֵ
	TL0=(65536-50000)%256;
	count++;		//�жϴ����ۼ�
	if(count==20) //20��50����Ϊ1��
	{
		count=0;
		miao++;
		if(miao==60)//��ӵ�60���λ����
		{
			miao=0;//ͬʱ��������
			fen++;
			if(fen==60)//���Ӽӵ�60���λСʱ
			{
				fen=0;//ͬʱ����������
				shi++;
				if(shi==24)//Сʱ�ӵ�24��Сʱ����
				{
					shi=0;
				}
				write_sfm(4,shi);//Сʱ���仯������д��
				write_add(3,shi);//���ݸı���������24C02
			}
			write_sfm(7,fen);//�������仯������д��
			write_add(2,fen);//���ݸı���������24C02
		}
		write_sfm(10,miao);//�����仯������д��	
		write_add(1,miao);//���ݸı���������24C02
	}	
}

