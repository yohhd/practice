#include <reg52.h>    		//52ϵ�е�Ƭ��ͷ�ļ�
#define uchar unsigned char
#define uint unsigned int
#define SLAVE 0x02   		   /*�ӻ���ַ*/
#define BN 16
uchar rbuf[16];
uchar code tbuf[16]={"master transmit"};

void err(void)
{ 
	SBUF=0xff;
	while(TI!=1);
	TI=0;
}
uchar master(uchar addr,uchar command)
{
	uchar aa,i,p;
	while(1)
  	{
		SBUF=SLAVE;  /* �����е�ַ */
   		while(TI!=1);
			TI=0;
   		while(RI!=1);
			RI=0;      	/* �ȴ��ӻ��ش� */
   		if(SBUF!=addr)
			err();    	/* ����ַ������λ�ź� */
     	else
		{                /* ��ַ��� */
   			TB8=0;        /* ���ַ��־ */
   			SBUF=command;     /* ������ */
  			while(TI!=1);
				TI=0;
  			while(RI!=1);
				RI=0;
			aa=SBUF;          /* ����״̬ */
  			if((aa&0x08)==0x08) /* ������δ������,����λ�ź� */
			{
				TB8=1;
				err();
			} 
  			else
			{
      			if(command==0x01) 	    /* �Ƿ������� */
         		{
					if((aa&0x01)==0x01)  /* �ӻ�׼���ý��� */
            		{
						do
						{
                  			p=0;            /* ��У��� */
                 			for(i=0;i<BN;i++)
                    		{
								SBUF=tbuf[i];   /* ����һ���� */
                       			p+=tbuf[i];
								while(TI!=1);
								TI=0;
                       		}
                       		SBUF=p;      /* ����У��� */
                       		while(TI!=1);
								TI=0;
                       		while(RI!=1);
								RI=0;
                   		}while(SBUF!=0); /* ���ղ���ȷ�����·��� */
                     	TB8=1;         /* �õ�ַ��־ */
						return(0);
         			}
       				else
					{
            			if((aa&0x02)==0x02)   /* �ǽ�������,�ӻ�׼���÷��� */
 						{
							while(1) 
            				{
								p=0;              	/* ��У��� */
				                for(i=0;i<BN;i++)
             					{
									while(RI!=1);
										RI=0;
				           			rbuf[i]=SBUF;  /* ����һ���� */
					                p+=rbuf[i];
               					}
               					while(RI!=1);
									RI=0;
			                    if(SBUF==p) 
                   				{
									SBUF=0X00;   /* У�����ͬ��"00" */
					                while(TI!=1);
										TI=0;
					                break;
        						}
         						else
             					{
									SBUF=0xff; 	/* У��Ͳ�ͬ��"0FF"�����½��� */
					 	            while(TI!=1);
										TI=0;
         						}
       						} 
       						TB8=1;     	/* �õ�ַ��־ */
							return(0);
     					}
    				}
   				}
  			}
 		}
	}
}		
void main()
{
	TMOD=0x20;                   /* T/C1����Ϊ��ʽ2 */
	TL1=0xfd;
	TH1=0xfd;                	/* �ó�ֵ */
	PCON=0x00;
	TR1=1;
	SCON=0xf0;                  /* ���п�Ϊ��ʽ3 */
	master(SLAVE,0x01);
	master(SLAVE,0x02);
	while(1);
}
