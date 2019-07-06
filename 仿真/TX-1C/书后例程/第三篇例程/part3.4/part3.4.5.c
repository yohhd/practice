#include <reg52.H>
#include <intrins.H>
// ������ ADC �йص����⹦�ܼĴ���
sfr P1_ADC_EN = 0x97; //A/Dת����������Ĵ���
sfr ADC_CONTR = 0xC5; //A/Dת�����ƼĴ���
sfr ADC_DATA = 0xC6;  //A/Dת������Ĵ���
typedef unsigned char INT8U;
typedef unsigned int INT16U;
void delay(INT8U delay_time) // ��ʱ����
{
	INT8U n;
	INT16U m;
	for (n=0;n<delay_time;n++)
		{
			for(m=0;m<10000;m++);
		}
}
void initiate_RS232(void)  //���ڳ�ʼ��
{
	ES = 0;   	   // ��ֹ�����ж�
	SCON = 0x50;   // 0101,0000 8 λ����λ�� ����żУ��
	T2CON = 0x34;  // 0011��0100�� ��T2 ��Ϊ�����ʷ�����
	RCAP2H = 0xFF; // ʱ��11.0592MHz, 9600 ������
	RCAP2L = 0xDB;
	ES = 1;        // �������ж�
}
void Send_Byte(INT8U one_byte) // ����һ���ֽ�
{
	TI = 0; 	// ���㴮�ڷ����жϱ�־
	SBUF = one_byte;
	while (TI == 0);
	TI = 0; 	// ���㴮�ڷ����жϱ�־
}
INT8U get_AD_result(INT8U channel)
{
	INT8U AD_finished = 0; // �洢 A/D ת����־
	ADC_DATA = 0;
	ADC_CONTR = channel; // ѡ�� A/D ��ǰͨ��
	delay(1); 			//ʹ�����ѹ�ﵽ�ȶ�
	ADC_CONTR |= 0x08; //0000,1000 �� ADC_START = 1, ����A/D ת��
	AD_finished = 0;
	while ( AD_finished == 0 ) // �ȴ�A/D ת������
	{
		AD_finished = (ADC_CONTR & 0x10); //0001,0000, ADC_FLAG ==1 ����A/D ת��������
	}
	ADC_CONTR &= 0xF7; //1111,0111 �� ADC_START = 0, �ر�A/D ת��,
	return (ADC_DATA); // ���� A/D ת�����
}
void main()
{
	initiate_RS232();
	P1 = P1 | 0x63; // 0110,0011,Ҫ����Ϊ A/D ת����P1.x ��,����Ϊ��
	P1_ADC_EN = 0x63; //0110,0011, P1 ��P1.0,P1.1,P1.5,P1.6 ����Ϊ A/D ת�������
	// �Ͽ�P1.0,P1.1,P1.5,P1.6 �ڲ���������
	while(1)
	{
		Send_Byte(get_AD_result(0)); //P1.0 Ϊ A/D ��ǰͨ��, ���������ͽ��
		delay(0x200);
		Send_Byte(get_AD_result(1)); //P1.1 Ϊ A/D ��ǰͨ��, ���������ͽ��
		delay(0x200);
		Send_Byte(get_AD_result(5)); //P1.5 Ϊ A/D ��ǰͨ��, ���������ͽ��
		delay(0x200);
		Send_Byte(get_AD_result(6)); //P1.6 Ϊ A/D ��ǰͨ��, ���������ͽ��
		delay(0x200);
		Send_Byte(0); // �������� 4 �� 00H, ���ڹ۲������ʾ
		Send_Byte(0);
		Send_Byte(0);
		Send_Byte(0);
		delay(0x200); // ��ʱ
		delay(0x200);
		delay(0x200);
		delay(0x200);
		delay(0x200);
		delay(0x200);
	}
}