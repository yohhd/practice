void fcd_z()
{
	if(key1==0)
	{
		delay(20);
		if(key1==0)
		{
			while(!key1);
			switch(flag_fun)
			{
			case 0:
				fcd+=0.01;
				cwfc+=0.01;
				sectorerase(0x2e00);//����ROM�����һ������
				write_eep(cwfc,0x2e00);//�洢�ı�������
				byte_write(0x2e06,1);
				break;
			case 1:
				gzdy=gzdy+0.01;
				sectorerase(0x2c00);//����ROM�ĵ����ڶ�������
				byte_write(0x2c00,gzdy*100);//�洢�ı�������
				byte_write(0x2c06,1);
				break;
			case 2:
				break;
			case 3:  //��������������ƻ�ԭ����Ĭ��
				gzdy=0.13;
				fcd=13.7;
				cwfc=13.7;
				sectorerase(0x2e00);
				sectorerase(0x2c00);
				break;
			}
			didi(1);
		}
	}
}
void fcd_j()
{
	if(key2==0)
	{
		delay(20);
		if(key2==0)
		{
			while(!key2);
			switch(flag_fun)
			{
				case 0:
					fcd-=0.01;
					cwfc-=0.01;
					sectorerase(0x2e00);//����ROM�����һ������
					write_eep(cwfc,0x2e00);//�洢�ı�������
					byte_write(0x2e06,1);
					break;
				case 1:
					gzdy=gzdy-0.01;
					sectorerase(0x2c00);//����ROM�ĵ����ڶ�������
					byte_write(0x2c00,gzdy*100);//�洢�ı�������
					byte_write(0x2c06,1);
					break;
				case 2:
					break;
				case 3:
					break;
			}
			didi(1);	
		}
	}
}
void func()
{
	uchar key_flag=0;
	if(key3==0)
	{
		delay(20);
		if(key3==0)
		{
			while(!key3);
			flag_fun++;
			if(flag_fun==2) //ֱ��������Ϸ����˳�����
			{
				didi(3);
				while(key_flag==0)
				{
					if(key1==0)
					{
						delay(20);
						if(key1==0)
						{
							while(!key1);
							fcd+=0.01;
							cwfc+=0.01;
						}
						didi(1);
					}
					if(key2==0)
					{
						delay(20);
						if(key2==0)
						{
							while(!key2);
							fcd-=0.01;
							cwfc-=0.01;
						}
						didi(1);
					}
					if(key3==0)
					{
						delay(20);
						if(key3==0)
						{
							while(!key3);
							flag_fun++;
							sectorerase(0x2e00);//����ROM�����һ������
							write_eep(cwfc,0x2e00);//�洢�ı�������
							byte_write(0x2e06,1);
							key_flag=1;
						}
					}
					if((Ad_Av(1)>(fcd-0.01))&&(Ad_Av(1)<(fcd+0.01)))
						didi(1);//��ԴУ׼�󱨾���ʾ
				}						
			}
			if(flag_fun==4)
				flag_fun=0;
			switch(flag_fun)
			{
				case 0:didi(1);
					break;
				case 1:didi(2);
					break;
				case 2:didi(3);
					break;
				case 3:beep=1;
					delay(2000);
					beep=0;
					break;
			}
		}
	}	
}
