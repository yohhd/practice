#include"STC12C5410AD.H"   	//STC12C54ϵ�е�Ƭ��ͷ�ļ�
#define uchar unsigned char
#define uint unsigned int 
void delayms(uint xms)				
{
	uint i,j;
	for(i=xms;i>0;i--)		      //i=xms����ʱԼxms����
		for(j=110;j>0;j--);
}
void AD_Init()
{
	P1M0=0x0f;//0000 1111 ����P1�ڵ�4λΪ��©ģʽ������AD�ɼ�
	P1M1=0x0f;//0000 1111
	ADC_CONTR=0xe0;//1110 0000 ����ADת������Դ���������ת���ٶ�
	delayms(100);
}
int GetAD(unsigned char channel) //channelΪҪȡ��ͨ����(0~7)
{
	unsigned char AD_finished=0;
	int result;
	ADC_CONTR|=channel;   //ѡ��ADͨ����
	ADC_CONTR|=0x08;      //����ADת��
	while(AD_finished==0) //�ȴ�ADת������
	{
		AD_finished=(ADC_CONTR&0x10);//��ѯADC_FLAGλ�Ƿ���1
	}
	result=ADC_DATA*4+ADC_LOW2;//����ADת�����������ADC_DATA�д洢12λ�е�
	//��8λ����Ҫת����10����ʱ���轫ADC_DATA�е�������2λ�����൱��*4
	ADC_CONTR&=0xf7;     //���ת��������־
	return (result);    //���ؽ��������
}
float Ad_Av(uchar channel)    //��100�βɼ���ѹ��ƽ��ֵ
{
	float Val_Av=0;
	uchar num;
	for(num=100;num>0;num--)
	{
		Val_Av+=GetAD(channel);//100�βɼ����
	}
	Val_Av/=100.0;            //��ƽ��ֵ
	Val_Av=Val_Av*5.0/1024;  //��Ƭ����ԴΪ5V�������ʵ��ѹֵ
	return (Val_Av);          //���ظ�����
}
void main()
{
	float ad1,ad2,ad3,ad4;
	AD_Init();
	ad1=Ad_Av(1);
	ad2=Ad_Av(2);
	ad3=Ad_Av(3);
	ad4=Ad_Av(4);
	while(1);
}
