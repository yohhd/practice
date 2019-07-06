#include<reg52.h>
#include<define.h>
void delay(uint z)//��ʱ����
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}
void di() //��������������
{
	beep=0;
	delay(100);
	beep=1;
}
void write_com(uchar com)
{//дҺ�������
	rs=0;
	lcden=0;
	P0=com;
	delay(3);
	lcden=1;
	delay(3);
	lcden=0;	
}
void write_date(uchar date)
{//дҺ�����ݺ���
	rs=1;
	lcden=0;
	P0=date;
	delay(3);
	lcden=1;
	delay(3);
	lcden=0;	
}
void init()
{//��ʼ������
	uchar num;
	EA=1;//�����ж�
	EX1=1;//���ⲿ�ж�1
	IT1=1;//���ø������ش����ж�
	flag1=0;//������ʼ��
	t0_num=0;
	s1num=0;
	week=1;
	dula=0;//�ر��������ʾ
	wela=0;
	lcden=0;
	rd=0;
/*���¼������״�����DS12C887ʱʹ�ã��Ժ󲻱���д��
	write_ds(0x0A,0x20);//������
	write_ds(0x0B,0x26);//����24Сʱģʽ�����ݶ����Ƹ�ʽ
						//���������ж�
	set_time();//�����ϵ�Ĭ��ʱ��
-----------------------------------------------------*/
	write_com(0x38);//1602Һ����ʼ��
	write_com(0x0c);
	write_com(0x06);
	write_com(0x01);
	write_com(0x80);
	for(num=0;num<15;num++)//д��Һ���̶�������ʾ
		{
			write_date(table[num]);
			delay(1);
		}
	write_com(0x80+0x40);
	for(num=0;num<11;num++)
		{
			write_date(table1[num]);
			delay(1);
		}
}
void write_sfm(uchar add,char date)
{//1602Һ��ˢ��ʱ���뺯��4Ϊʱ��7Ϊ�֣�10Ϊ��
	char shi,ge;
	shi=date/10;
	ge=date%10;
	write_com(0x80+0x40+add);
	write_date(0x30+shi);
	write_date(0x30+ge);
}
void write_nyr(uchar add,char date)
{//1602Һ��ˢ�������պ���3Ϊ�꣬6Ϊ�֣�9Ϊ��
	char shi,ge;
	shi=date/10;
	ge=date%10;
	write_com(0x80+add);
	write_date(0x30+shi);
	write_date(0x30+ge);
}
void write_week(char we)
{//дҺ��������ʾ����
	write_com(0x80+12);
	switch(we)
	{
		case 1:	write_date('M');delay(5);
				write_date('O');delay(5);
				write_date('N');
				break;
		case 2:	write_date('T');delay(5);
				write_date('U');delay(5);
				write_date('E');
				break;
		case 3:	write_date('W');delay(5);
				write_date('E');delay(5);
				write_date('D');
				break;
		case 4:	write_date('T');delay(5);
				write_date('H');delay(5);
				write_date('U');
				break;
		case 5:	write_date('F');delay(5);
				write_date('R');delay(5);
				write_date('I');
				break;
		case 6:	write_date('S');delay(5);
				write_date('A');delay(5);
				write_date('T');
				break;
		case 7:	write_date('S');delay(5);
				write_date('U');delay(5);
				write_date('N');
				break;
	}
}
void keyscan()
{
	if(flag_ri==1)
	{//��������ȡ�����ӱ�������һ��ȡ������
		if((s1==0)||(s2==0)||(s3==0)||(s4==0))
		{	
			delay(5);
			if((s1==0)||(s2==0)||(s3==0)||(s4==0))
			{
				while(!(s1&&s2&&s3&&s4));
                di();
				flag_ri=0;//���������־
			}	 	
		}
	}	
	if(s1==0)//���S1
	{
		delay(5);
		if(s1==0)
		{	
			s1num++;//��¼���´���
			if(flag1==1)
				if(s1num==4)
					s1num=1;
			flag=1;
			while(!s1);di();
			switch(s1num)
			{//�����˸�㶨λ
				case 1: write_com(0x80+0x40+10);
					    write_com(0x0f);
						break;
				case 2: write_com(0x80+0x40+7);
						break;
				case 3: write_com(0x80+0x40+4);
						break;
				case 4: write_com(0x80+12);
						break;
				case 5: write_com(0x80+9);
						break;
				case 6: write_com(0x80+6);
						break;
				case 7: write_com(0x80+3);
						break;
				case 8: s1num=0;
						write_com(0x0c);
						flag=0;
						write_ds(0,miao);
						write_ds(2,fen);
						write_ds(4,shi);
						write_ds(6,week);
						write_ds(7,day);
						write_ds(8,month);
						write_ds(9,year);
						break;
			}	
		}
	}
	if(s1num!=0)//ֻ�е�S1���º󣬲ż��S2��S3
	{
		if(s2==0)
		{
			delay(1);
			if(s2==0)
			{
				while(!s2);di();
				switch(s1num)
				{//���ݹ��ܼ�����������Ӧ��ֵ
					case 1:	miao++;
							if(miao==60)
								miao=0;
							write_sfm(10,miao);
							write_com(0x80+0x40+10); 
							break;
					case 2:	fen++;
							if(fen==60)
								fen=0;
							write_sfm(7,fen);
							write_com(0x80+0x40+7); 
							break;
					case 3:	shi++;
							if(shi==24)
								shi=0;
							write_sfm(4,shi);
							write_com(0x80+0x40+4); 
							break;
					case 4:	week++;
							if(week==8)
								week=1;
							write_week(week);
							write_com(0x80+12);
							break;
					case 5:	day++;
							if(day==32)
								day=1;
							write_nyr(9,day);
							write_com(0x80+9);
							break;
					case 6:	month++;
							if(month==13)
								month=1;
							write_nyr(6,month);
							write_com(0x80+6);
							break;
					case 7:	year++;
							if(year==100)
								year=0;
							write_nyr(3,year);
							write_com(0x80+3);
							break;
				}
			}
		}
		if(s3==0)
		{
			delay(1);
			if(s3==0)
			{
				while(!s3);di();
				switch(s1num)
				{//���ݹ��ܼ�����������Ӧ��ֵ
					case 1:	miao--;
							if(miao==-1)
								miao=59;
							write_sfm(10,miao);
							write_com(0x80+0x40+10);
							break; 
					case 2:	fen--;
							if(fen==-1)
								fen=59;
							write_sfm(7,fen);
							write_com(0x80+0x40+7);
							break;
					case 3:	shi--;
							if(shi==-1)
								shi=23;
							write_sfm(4,shi);
							write_com(0x80+0x40+4);
							break;
					case 4:	week--;
							if(week==0)
								week=7;
							write_week(week);
							write_com(0x80+12);
							break;
					case 5:	day--;
							if(day==0)
								day=31;
							write_nyr(9,day);
							write_com(0x80+9);
							break;
					case 6:	month--;
							if(month==0)
								month=12;
							write_nyr(6,month);
							write_com(0x80+6);
							break;
					case 7:	year--;
							if(year==-1)
								year=99;
							write_nyr(3,year);
							write_com(0x80+3);
							break;
				}
			}
		}
	}
	if(s4==0)//���S4
	{
		delay(5);
		if(s4==0)
		{	
			flag1=~flag1;
			while(!s4);di();
			if(flag1==0)
			{//�˳���������ʱ������ֵ
				flag=0;
				write_com(0x80+0x40);
				write_date(' ');
				write_date(' ');
				write_com(0x0c);
				write_ds(1,miao);
				write_ds(3,fen);
				write_ds(5,shi);				
			}
			else
			{//������������
				read_alarm();//��ȡԭʼ����
				miao=amiao;//���¸�ֵ���԰�������
				fen=afen;
				shi=ashi;
				write_com(0x80+0x40);
				write_date('R');//��ʾ��־
				write_date('i');
				write_com(0x80+0x40+3);
				write_sfm(4,ashi);//��Һ����ʾ����ʱ��
				write_sfm(7,afen);
				write_sfm(10,amiao);
			}			
		}
	}
}

void write_ds(uchar add,uchar date)
{//д12C887����
	dscs=0;
	dsas=1;
	dsds=1;
	dsrw=1;
	P0=add;//��д��ַ
	dsas=0;
	dsrw=0;
	P0=date;//��д����
	dsrw=1;
	dsas=1;
	dscs=1;				
}

uchar read_ds(uchar add)
{//��12C887����
 	uchar ds_date;
	dsas=1;
	dsds=1;
	dsrw=1;
	dscs=0;
	P0=add;//��д��ַ
	dsas=0;
	dsds=0;
	P0=0xff;
	ds_date=P0;//�ٶ�����
	dsds=1;
	dsas=1;
	dscs=1;
	return ds_date;	
}
/*---�״β���12C887ʱ����Ĵ�����ʼ��---
void set_time()
{//�״��ϵ��ʼ��ʱ�亯��
	write_ds(0,0);
	write_ds(1,0);
	write_ds(2,0);
	write_ds(3,0);
	write_ds(4,0);
	write_ds(5,0);
	write_ds(6,0);
	write_ds(7,0);
	write_ds(8,0);
	write_ds(9,0);	
}
----------------------------------------*/
void read_alarm()
{//��ȡ12C887����ֵ
	amiao=read_ds(1);
	afen=read_ds(3);
	ashi=read_ds(5);
}
void main()//������
{
	init();//���ó�ʼ������
	while(1)
	{
		keyscan();//����ɨ��
		if(flag_ri==1)//�������ж�ʱ��������
		{
			di();
			delay(100);
			di();
			delay(500);
		}	
		if(flag==0&&flag1==0)//��������ʱ��������
		{
			keyscan();//����ɨ��
			year=read_ds(9);//��ȡ12C887����
			month=read_ds(8);	
			day=read_ds(7);
			week=read_ds(6);
			shi=read_ds(4);
			fen=read_ds(2);
			miao=read_ds(0);	
			write_sfm(10,miao);//��Һ����ʾ
			write_sfm(7,fen);
			write_sfm(4,shi);
			write_week(week);
			write_nyr(3,year);
			write_nyr(6,month);
			write_nyr(9,day);
		}
	}
}

void exter() interrupt 2//�ⲿ�ж�1�������
{	uchar c; //�����жϱ�ʾ����ʱ�䵽��
	flag_ri=1; //���ñ�־λ�����Դ�����б�����ʾ
	c=read_ds(0x0c);//��ȡ12C887��C�Ĵ�����ʾ��Ӧ���ж�
}



