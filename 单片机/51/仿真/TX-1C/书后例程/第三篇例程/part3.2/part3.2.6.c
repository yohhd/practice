#include <reg52.h>
#define uchar unsigned char
#define SLAVE  0x02
#define BN  16
uchar trbuf[16];
uchar rebuf[16];
bit tready;
bit rready;
void str(void);
void sre(void);
void main(void)
{ 
	TMOD=0x20;      /*T/C1����Ϊ��ʽ2*/
	TL1=0xfd;      	/*�ó�ֵ*/
	TH1=0xfd;
	PCON=0x00;
	TR1=1;
	SCON=0xf0;     /*���п�Ϊ��ʽ3*/
	ES=1;
	EA=1;         /*�����п��ж�*/
	while(1)
	{
		tready=1;
		rready=1;
	}	/*�ٶ�׼���÷��ͺͽ���*/
}
void ssio(void) interrupt 4
{ 
	uchar a;
	RI=0;
	ES=0;     	/*�ش��п��ж�*/
	if(SBUF!=SLAVE)
	{
		ES=1;
		goto reti;
	}  	/*�Ǳ�����ַ,��������*/
	SM2=0;   /* ȡ������״̬ */
	SBUF=SLAVE;   /* �ӱ���ַ���� */
	while(TI!=1);
		TI=0;
	while(RI!=1);
		RI =0;
	if(RB8==1)
	{
		SM2=1;
		ES=1;
		goto reti;
	}/* �Ǹ�λ�źţ��ָ����� */
	a=SBUF;    /* �������� */
	if(a==0x01)/* ���������յ����� */
	{
		if(rready==1)
			SBUF=0x01;/* ����׼���÷�״̬ */
		else 
			SBUF=0x00;
		while(TI!=1);
			TI=0;
		while(RI!=1);
			RI=0;
		if(RB8==1)
		{
			SM2=1;
			ES=1;
			goto reti;
		} 
		sre();	/* �������� */
	}
	else
	{
		if(a==0x02)	/* �ӻ���������������*/
		{
			if(tready==1)
				SBUF=0x02;	/* ����׼���÷�״̬ */
			else
				SBUF=0x00;
			while(TI!=1);
				TI=0;
			while(RI!=1);
				RI=0;
			if(RB8==1)
			{
				SM2=1;
				ES=1;
				goto reti;
			}
			str();/* �������� */ 
		}
		else       
		{
			SBUF=0x80;  /* ����Ƿ� ����״̬ */
			while(TI!=1);
				TI=0;
			SM2=1;
			ES=1;  /* �ָ����� */
		}
	}
	reti:;
}
void  str(void) 		/* �����ݿ� */
{  
	uchar p,i;
	tready=0 ;
	do
	{
		p=0;/* ��У��� */ 
	 	for(i=0;i<BN;i++) 
	 	{
			SBUF=trbuf[i];	/* ����һ���� */
	    	p+=trbuf[i];
	    	while(TI!=1);
		    TI=0; 
	 	}
		SBUF=p;           			/* ����У��� */
		while(TI!=1);
			TI=0;
		while(RI!=1);
			RI=0;
	}while(SBUF!=0);/* �������ղ���ȷ�����·��� */
	SM2=1;
	ES=1;
} 
void sre(void) /* �������ݿ� */
{  
	uchar p,i;
	rready=0 ;
	while(1) 
	{
		p=0;   		/* ��У��� */ 
	    for(i=0;i<BN;i++) 
	    {
			while(RI!=1);
			RI=0;
	        rebuf[i]=SBUF;        	/* �������� */
            p+=rebuf[i];
	    }
	    while(RI!=1);
		RI=0;
		if(SBUF==p)
		{
			SBUF=0x00;
			break;
		} 	/* У�����ͬ��"00"*/
	  	else
		{
	    	SBUF=0xff;           		/* У��Ͳ�ͬ��"0FF"�����½��� */
	    	while(TI==0);
			TI=0;
	     }
	  }
	SM2=1;
	ES=1;
} 
