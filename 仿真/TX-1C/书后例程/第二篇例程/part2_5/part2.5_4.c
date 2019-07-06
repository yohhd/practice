#include <REG52.h> 
#define uint unsigned int 
#define uchar unsigned char
sbit CS=P1^2; 
sbit SID=P1^1; 
sbit SCLK=P1^0;
uchar code disps[]={"Hello everyone!"};
uchar code dispx[]={"��ӭ�����ѧϰ!"};

void delay_1ms(uint x) 
{ 
uint i,j; 
for(j=0;j<x;j++)  
	for(i=0;i<110;i++); 
}
void send_command(uchar command_data) 
{ 
	uchar i; 
	uchar i_data;
	i_data=0xf8; 
	CS=1; 
	SCLK=0; 
	for(i=0;i<8;i++) 
		{ 
			SID=(bit)(i_data&0x80); 
			SCLK=0; 
			SCLK=1; 
			i_data=i_data<<1; 
		} 
	i_data=command_data; 
	i_data&=0xf0;
	for(i=0;i<8;i++) 
		{ 
			SID=(bit)(i_data&0x80); 
			SCLK=0; 
			SCLK=1; 
			i_data=i_data<<1; 
		} 
	i_data=command_data; 
	i_data<<=4;
	for(i=0;i<8;i++) 
		{ 
			SID=(bit)(i_data&0x80); 
			SCLK=0; 
			SCLK=1; 
			i_data=i_data<<1; 
		} 
	CS=0; 
	delay_1ms(1); 
} 
void send_data(uchar command_data) 
{ 
	uchar i; 
	uchar i_data;
	i_data=0xfa;  
	CS=1; 
	for(i=0;i<8;i++) 
		{ 
			SID=(bit)(i_data&0x80); 
			SCLK=0; 
			SCLK=1; 
			i_data=i_data<<1;  
		} 
	i_data=command_data; 
	i_data&=0xf0; 
	for(i=0;i<8;i++) 
		{ 
			SID=(bit)(i_data&0x80); 
			SCLK=0; 
			SCLK=1; 
			i_data=i_data<<1; 
		} 
	i_data=command_data;
	i_data<<=4; 
	for(i=0;i<8;i++) 
		{ 
			SID=(bit)(i_data&0x80); 
			SCLK=0; 
			SCLK=1; 
			i_data=i_data<<1; 
		} 
	CS=0; 
	delay_1ms(1);  
}
void lcd_init() 
{ 
	delay_1ms(100); 
	send_command(0x30); /*����8λ���ݽӿڣ�����ָ��ģʽ��*/ 
	send_command(0x02); /*��DDRAM*/ 
	send_command(0x06); /*�α꼰��ʾ����һλ*/  
	send_command(0x0c); /*������ʾ�����α�أ����׹�*/ 
	send_command(0x01); /*д��ո�����Ļ*/ 
	send_command(0x80); /*�趨�״���ʾλ��*/ 

}
void display_s(uchar num)
{
	uchar a;
	send_command(0x88-num);
	for(a=0;a<15;a++)
	{
		send_data(disps[a]);		
	}
}
void display_x(uchar num) 
{ 
	uchar a;
	send_command(0x98-num);
	for(a=0;a<15;a++)
	{
		send_data(dispx[a]);		
	} 
}
main() 
{ 
	uchar aa;
	lcd_init(); 
	for(aa=0;aa<9;aa++)
	{
		display_s(aa);
		display_x(aa);		 
		delay_1ms(300);
	}
	while(1); 
}