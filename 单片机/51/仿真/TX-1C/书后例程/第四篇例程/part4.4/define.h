#define uint unsigned int
#define uchar unsigned char
#define qy     	     fcd-2.9//10.8   //Ƿѹ
#define qyhf   	     fcd-0.5//13.2   //Ƿѹ�ָ�
#define fcdy     	 fcd-0.128//13.2	//�����ѹ
#define gddy     	 fcd+0.128//13.456	//�ضϵ�ѹ
#define gyhf    	 fcd+0.9//14.6	//��ѹ�ָ�
#define gygd    	 fcd+1.1//14.8	//��ѹ�ض�
#define pvbt         0.5//��PV���ѹ���ڵ��1V����ʱ�ſ�������
#define jcjg         1200 //����*50ms�ܺ�Ϊ����ذ�����ػָ������ʱ�䵥λ��S��
#define jcgzjg       100  //���غ��⸺�ػָ����
#define fz_on		 czfz=0 //�򿪸���
#define fz_off       czfz=1 //�رո���
#define cd_on		 czcf=1 //��ʼ���
#define cd_off       czcf=0 //�رճ��
sbit czfz=P1^3;            //���Ƹ���
sbit czcf=P3^7;            //���Ƴ��
sbit beep=P1^6;			   //������
sbit rs=P1^7;              //Һ����������
sbit lcden=P1^4;		   // Һ��ʹ��
sbit qyd=P2^2;			   //Ƿѹ��
sbit gyd=P2^3;		       //��ѹ��	
sbit fzd=P2^4;			   //���ص�
sbit cdd=P2^5;			   //����
sbit zcd=P1^5;            //ϵͳ������
sbit key1=P3^2;			 //��������
sbit key2=P3^3;
sbit key3=P3^4;
void delay(uint);
void delayus(uchar);
void didi(uchar);
void init();//����Ϊ��������
uchar a,fz,diqynum,digynum,flag_t1gz,flag_gz;
uchar flag_t1,flag_pv,flag_fz,pwm_num,t1_numgz;
uchar pwm_a,flag_fun;
uint t1_num;
float xdata fcd,ad_val,v_temp,cwfc,dwfc,gwfc,gzdy;
