void pwm_zk(uchar gao)  
{//������� gaoΪ�ߵ�ƽ����ʱ�����255����С1
	PCA_PWM0=0;
	CCAP0H=(256-gao);
	CR=1;		
}
void pwm_1()  // PWM�˹̶��ߵ�ƽ
{
	PCA_PWM0=0;
	CCAP0H=0;
}
void pwm_0()  //PWM�˹̶��͵�ƽ
{
	PCA_PWM0=0x03;
	CCAP0H=0xff;
}
void checkpv()//����ذ��ѹ
{
	//ʡȥ����ذ����	
}
void checkgz()
{
	float temp_gz;
	if(flag_fz==1)
	{
		temp_gz=Ad_fu(4);
		if(temp_gz>gzdy)    
		{ //�ж��Ƿ���� ע�⣺ֻ����ǰ����̸��ش򿪵������  
          //�����жϸ����Ƿ���أ����򽫲����жϡ�
			P1M0=0x87; //00000111
			P1M1=0x49;
			fz_off;
			didi(1);
			flag_fz=0;
			fzd=1;
			flag_gz=1;
			flag_t1gz=0;		
	 	}
		if(temp_gz>(gzdy-0.02))
		{//�����ǰ�ı�����ʾ
			didi(1);
		}
	}
	//����ʡȥ���ػָ�������	
}
