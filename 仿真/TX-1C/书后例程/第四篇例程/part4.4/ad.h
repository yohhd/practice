float GetAD(uchar channel)//�û�����
{
	unsigned char AD_finished=0;
	float tad_val;
	tad_val=0;
	ADC_CONTR|=(channel-1); //ѡ��AD�˿ں�
	ADC_DATA=0;
	ADC_LOW2=0;
	ADC_CONTR|=0x08;   //����ADת��
	while(AD_finished==0){
		AD_finished=(ADC_CONTR&0x10);
	}
	tad_val=(ADC_DATA*4+ADC_LOW2);
	ADC_CONTR&=0xe0;
	return (tad_val);
}
float Ad_Av(uchar chan)
{//�����ص�ѹƽ��ֵ
	float Val_Av;
	uchar num;
	Val_Av=0;
	for(num=120;num>0;num--)
	{
		Val_Av+=GetAD(chan);
	}
	Val_Av/=120.0;
	Val_Av=Val_Av*15.0/1024;
	return (Val_Av);
}
float Ad_fu(uchar chan)
{//��������ѹƽ��ֵ
	float Val_Av;
	uchar num;
	Val_Av=0;
	for(num=5;num>0;num--)
	{
		Val_Av+=GetAD(chan);
	}
	Val_Av/=5.0;
	Val_Av=Val_Av*5.0/1024;
	return (Val_Av);
}