sfr P1_ADC_EN=0x97;
sfr ADC_CONTR=0xc5;
sfr ADC_DATA=0xc6;


int GetAD(unsigned char channel)		//�û�������channelΪҪȡ��ͨ����(0~7)
{
	unsigned char AD_finished=0;
   // AD_Init(1<<channel);
	ADC_DATA=0;
	ADC_CONTR=channel;
	delay(1000);
	ADC_CONTR|=0x08;
	AD_finished=0;
	while(AD_finished==0){
		AD_finished=(ADC_CONTR&0x10);
	}
	ADC_CONTR&=0xF7;
	return (ADC_DATA);
}


void AD_Init(unsigned char ADin)		// ADC ��ʼ��,ADinΪ��λ2���������ֱ��ӦAD7~0����1����򿪴�·
{
	P1=P1|ADin;
	P1_ADC_EN=0x63;
}
