#include <reg51.h>
#include <intrins.h>
#include <stdlib.h>	
#define uchar unsigned char
#define uint  unsigned int
/* �˿ڶ���*/
#define LCD_data  P0             //���ݿ�
sbit LCD_RS  =  P3^5;            //�Ĵ���ѡ������ 
sbit LCD_RW  =  P3^6;            //Һ����/д����
sbit LCD_EN  =  P3^4;            //Һ��ʹ�ܿ���
sbit LCD_PSB =  P3^7;            //��/����ʽ����
sbit wela    =  P2^6;
sbit dula    =  P2^7;
uchar dis1[10]; 
uchar code dis2[] = {"www.txmcu.com"};
uchar code dis3[] = {"�������"};
uchar code dis4[] = {"--------"};
void delay_1ms(uint x) 
{ 
uint i,j; 
for(j=0;j<x;j++)  
	for(i=0;i<110;i++); 
}		
/*******************************************************************/
/*                                                                 */
/*дָ�����ݵ�LCD                                                  */
/*RS=L��RW=L��E=�����壬D0-D7=ָ���롣                             */
/*                                                                 */
/*******************************************************************/
void write_cmd(uchar cmd)
{                          
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_EN = 0;
    P0 = cmd;
	delay_1ms(5);
    LCD_EN = 1;
	delay_1ms(5);
    LCD_EN = 0;  
}
/*******************************************************************/
/*                                                                 */
/*д��ʾ���ݵ�LCD                                                  */
/*RS=H��RW=L��E=�����壬D0-D7=���ݡ�                               */
/*                                                                 */
/*******************************************************************/
void write_dat(uchar dat)
{                          
    LCD_RS = 1;
    LCD_RW = 0;
    LCD_EN = 0;
    P0 = dat;
	delay_1ms(5);
    LCD_EN = 1;
	delay_1ms(5);
    LCD_EN = 0;  
}
/*********************************************************/
/*                                                       */
/* �趨��ʾλ��                                          */
/*                                                       */
/*********************************************************/
void lcd_pos(uchar X,uchar Y)
{                          
   uchar  pos;
   if (X==0)
     {X=0x80;}
   else if (X==1)
     {X=0x90;}
   else if (X==2)
     {X=0x88;}
   else if (X==3)
     {X=0x98;}
   pos = X+Y ;  
   write_cmd(pos);     //��ʾ��ַ
}
void makerand()
{
	uint ran;
	ran=rand();
	dis1[0]=ran/10000+0x30;	
	dis1[1]=ran%10000/1000+0x30;
	dis1[2]=ran%1000/100+0x30;
	dis1[3]=ran%100/10+0x30;
	dis1[4]=ran%10+0x30;
	ran=rand();
	dis1[5]=ran/10000+0x30;	
	dis1[6]=ran%10000/1000+0x30;
	dis1[7]=ran%1000/100+0x30;
	dis1[8]=ran%100/10+0x30;
	dis1[9]=ran%10+0x30;

}
/*******************************************************************/
/*                                                                 */
/*  LCD��ʼ���趨                                                  */
/*                                                                 */
/*******************************************************************/
void lcd_init()
{ 
    LCD_PSB = 1;         //���ڷ�ʽ  
    write_cmd(0x30);      //����ָ�����
    delay_1ms(5);
    write_cmd(0x0C);      //��ʾ�����ع��
    delay_1ms(5);
    write_cmd(0x01);      //���LCD����ʾ����
    delay_1ms(5);
}
/*********************************************************/
/*														 */
/* ������           									 */
/*                                                       */
/*********************************************************/
main()
{
    uchar i;
    wela=0;
	dula=0;
    delay_1ms(10);                 //��ʱ
    lcd_init();                 //��ʼ��LCD             
    lcd_pos(1,0);             //������ʾλ��Ϊ�ڶ��еĵ�1���ַ�
    i = 0;
    while(dis2[i] != '\0')
    {
       write_dat(dis2[i]);      //��ʾ�ַ�
       i++;
    }
 	lcd_pos(2,0);             //������ʾλ��Ϊ�����еĵ�1���ַ�
    i = 0;
    while(dis3[i] != '\0')
    {
       write_dat(dis3[i]);      //��ʾ�ַ�
       i++;
    }
	lcd_pos(3,0);             //������ʾλ��Ϊ�����еĵ�1���ַ�
    i = 0;
    while(dis4[i] != '\0')
    {
       write_dat(dis4[i]);      //��ʾ�ַ�
       i++;
    }
    while(1)
	{
		lcd_pos(0,0);   //������ʾλ��Ϊ��һ�еĵ�1���ַ�
		makerand();
		for(i=0;i<10;i++)
		{
		    write_dat(dis1[i]);
		}
	}
}
