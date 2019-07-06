#include <intrins.h>
#include <reg52.h>    		//52ϵ�е�Ƭ��ͷ�ļ�
#define uchar unsigned char
#define uint unsigned int 
#define RdCommand 0x01	//����ISP�Ĳ�������
#define PrgCommand 0x02
#define EraseCommand 0x03	
#define Error 1
#define Ok 0
#define WaitTime 0x01 //����CPU�ĵȴ�ʱ��
sfr ISP_DATA=0xe2;  //�Ĵ�������
sfr ISP_ADDRH=0xe3;
sfr ISP_ADDRL=0xe4;
sfr ISP_CMD=0xe5;
sfr ISP_TRIG=0xe6;
sfr ISP_CONTR=0xe7;
sbit dula=P2^6;		//����U1�������������
sbit wela=P2^7;		//����U2�������������
uchar code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};
uchar num;
void delayms(uint xms)				
{
	uint i,j;
	for(i=xms;i>0;i--)		      //i=xms����ʱԼxms����
		for(j=110;j>0;j--);
}
void display(uchar shi,uchar ge)  //��ʾ�Ӻ���
{
    dula=1;
	P0=table[shi];    //��ʮλ��ѡ����
	dula=0;
	P0=0xff;		//��λѡ����ǰ�ر�������ʾ����ֹ��λѡ����ʱ
	wela=1;			//ԭ����ѡ����ͨ��λѡ��������ɻ���
	P0=0xfe;		//��λѡ����
	wela=0;
	delayms(5);	//��ʱ
	dula=1;
	P0=table[ge];  //�͸�λ��ѡ����
	dula=0;
	P0=0xff;
	wela=1;
	P0=0xfd;
	wela=0;
	delayms(5);
}
/* ================ �� ISP,IAP ���� ================= */
void ISP_IAP_enable(void)
{
	EA	=	0;							/* ���ж� 		*/
	ISP_CONTR =	ISP_CONTR & 0x18;       /* 0001,1000	*/
	ISP_CONTR =	ISP_CONTR | WaitTime;	/* д��Ӳ����ʱ	*/
	ISP_CONTR =	ISP_CONTR | 0x80;       /* ISPEN=1		*/
}
/* =============== �ر� ISP,IAP ���� ================== */
void ISP_IAP_disable(void)
{
	ISP_CONTR	=	ISP_CONTR & 0x7f;	/* ISPEN = 0 */
	ISP_TRIG	=	0x00;
	EA			=   1;			/* ���ж� */
}
/* ================ ���õĴ������� ==================== */
void ISPgoon(void)
{
	ISP_IAP_enable();			/* �� ISP,IAP ����	*/
	ISP_TRIG	=	0x46;		/* ����ISP_IAP�����ֽ�1	*/
	ISP_TRIG	=	0xb9;		/* ����ISP_IAP�����ֽ�2	*/
	_nop_();
}
/* ==================== �ֽڶ� ======================== */
unsigned char byte_read(unsigned int byte_addr)
{
	ISP_ADDRH = (unsigned char)(byte_addr >> 8);/* ��ַ��ֵ	*/
	ISP_ADDRL = (unsigned char)(byte_addr & 0x00ff);
	ISP_CMD   = ISP_CMD	& 0xf8;			/* �����3λ 	*/
	ISP_CMD   = ISP_CMD	| RdCommand;	/* д�������	*/
	ISPgoon();							/* ����ִ��		*/
	ISP_IAP_disable();				/* �ر�ISP,IAP����	*/
	return (ISP_DATA);				/* ���ض���������	*/
}
/* ================== �������� ======================== */
void SectorErase(unsigned int sector_addr)
{
	unsigned int iSectorAddr;
	iSectorAddr = (sector_addr & 0xfe00); /* ȡ������ַ */
	ISP_ADDRH = (unsigned char)(iSectorAddr >> 8);
	ISP_ADDRL = 0x00;
	ISP_CMD	= ISP_CMD & 0xf8;			/* ��յ�3λ 	*/
	ISP_CMD	= ISP_CMD | EraseCommand;	/* ��������3 	*/
	ISPgoon();							/* ����ִ��		*/
	ISP_IAP_disable();				/* �ر�ISP,IAP����	*/
}
/* ==================== �ֽ�д ======================== */
void byte_write(unsigned int byte_addr, unsigned char original_data)
{
	ISP_ADDRH =	(unsigned char)(byte_addr >> 8); 	/* ȡ��ַ 	*/
	ISP_ADDRL =	(unsigned char)(byte_addr & 0x00ff);
	ISP_CMD	 = ISP_CMD & 0xf8;				/* ���3λ	*/
	ISP_CMD  = ISP_CMD | PrgCommand;		/* д����2	*/
	ISP_DATA = original_data;			/* д������׼��	*/
	ISPgoon();							/* ����ִ��		*/
	ISP_IAP_disable();					/* �ر�IAP����	*/
}
void main()
{
	uchar a,b,num1;
	TMOD=0x01; //���ö�ʱ��0Ϊ������ʽ1(0000 0001)
	TH0=(65536-50000)/256;     
	TL0=(65536-50000)%256;
	EA=1;
	ET0=1;
	TR0=1;
	num1=byte_read(0x2000);//����ʼʱ��ȡEEPROM������
	if(num1>=60)	//��ֹ�״��ϵ�ʱ��ȡ����
		num1=0;
	while(1) 
	{
		if(num>=20)
		{
			num=0;
			num1++;
			SectorErase(0x2000);//��������
			byte_write(0x2000,num1);//����д������
			if(num1==60)
			{
				num1=0;
			}
			a=num1/10;
			b=num1%10;
		}
		display(a,b);
	}
}
void timer0() interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	num++;	
}
