#define uchar unsigned char 
#define uint unsigned int
sbit dula=P2^6;
sbit wela=P2^7;
sbit rs=P3^5;
sbit lcden=P3^4;
sbit s1=P3^0;//���ܼ�
sbit s2=P3^1;//���Ӽ�
sbit s3=P3^2;//��С��
sbit s4=P3^6;//���Ӳ鿴��
sbit rd=P3^7;
sbit beep=P2^3;//������
sbit dscs=P1^4;
sbit dsas=P1^5;
sbit dsrw=P1^6;
sbit dsds=P1^7;
sbit dsirq=P3^3;
bit flag1,flag_ri;//��������λ����
uchar count,s1num,flag,t0_num;//������������
char miao,shi,fen,year,month,day,week,amiao,afen,ashi;
uchar code table[]=" 20  -  -      ";//Һ���̶���ʾ����
uchar code table1[]="      :  :  ";
void write_ds(uchar,uchar);//��������
void set_alarm(uchar,uchar,uchar);void read_alarm();
uchar read_ds(uchar);void set_time();
