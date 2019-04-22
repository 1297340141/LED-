#include "reg52.h"			 //���ļ��ж����˵�Ƭ����һЩ���⹦�ܼĴ���

typedef unsigned int u16;	  //���������ͽ�����������
typedef unsigned char u8;



sbit LSA=P2^0;
sbit LSB=P2^1;
sbit LSC=P2^2;
sbit LSD=P2^3;
sbit LSE=P2^4;
sbit LSF=P2^5;

sbit  p30 = P3^0;
sbit  p31 = P3^1;
sbit  p32 = P3^2;
sbit  p33 = P3^3;
sbit  p34 = P3^4;
sbit  p35 = P3^5;
sbit  p36 = P3^6;
sbit  p37 = P3^7;

sbit k0=P2^6;
sbit k2=P2^7;


u8 code smgduan[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//��ʾ0~F��ֵ

//u8 ssec,sec=55,min=59,hor=23;
u8 ssec,sec=46,min,hor;
u8 DisplayData[6];
int value;

void delay(u16 i)
{
	while(i--);	
}

void Timer0Init()
{
	TMOD|=0X01;//ѡ��Ϊ��ʱ��0ģʽ��������ʽ1������TR0��������
	TH0=0Xd8;	//����ʱ������ֵ����ʱ10ms
	TL0=0Xf0;	
	ET0=1;//�򿪶�ʱ��0�ж�����
	EA=1;//�����ж�
	TR0=1;//�򿪶�ʱ��	
	PT0=0;
}

void DigDisplay()
{
	u8 i;
	for(i=0;i<6;i++)
	{
		switch(i)	 //λѡ��ѡ�����������ܣ�
		{
			case(0):
				LSA=1;LSB=1;LSC=1;LSD=1;LSE=1;LSF=0; break;//��ʾ��0λ
			case(1):
				LSA=1;LSB=1;LSC=1;LSD=1;LSE=0;LSF=1; break;//��ʾ��1λ
			case(2):
				LSA=1;LSB=1;LSC=1;LSD=0;LSE=1;LSF=1; break;//��ʾ��2λ
			case(3):
				LSA=1;LSB=1;LSC=0;LSD=1;LSE=1;LSF=1; break;//��ʾ��3λ
			case(4):
				LSA=1;LSB=0;LSC=1;LSD=1;LSE=1;LSF=1; break;//��ʾ��4λ
			case(5):
				LSA=0;LSB=1;LSC=1;LSD=1;LSE=1;LSF=1; break;//��ʾ��5λ
		}
		P0=DisplayData[i];//���Ͷ���
		delay(200); //���һ��ʱ��ɨ��	
		P0=0x00;//����
	}
}



char	code  LEDshiwei[10][8] = {
				{0x00,0xA0,0x80,0xC0,0x40,0x60,0x20,0xA0},//00
				{0x12,0xBF,0x90,0xC0,0x40,0x60,0x20,0xA0},//10
        {0x1D,0xB5,0x97,0xC0,0x40,0x60,0x20,0xA0},//20       
        {0x15,0xB5,0x9F,0xC0,0x40,0x60,0x20,0xA0},//30
				{0x07,0xA4,0x9F,0xC0,0x40,0x60,0x20,0xA0},//40
        {0x17,0xB5,0x9D,0xC0,0x40,0x60,0x20,0xA0},//50
        {0x1F,0xB5,0x9D,0xC0,0x40,0x60,0x20,0xA0},//60
				{0x01,0xA1,0x9F,0xC0,0x40,0x60,0x20,0xA0},//70
				{0x1F,0xB5,0x9F,0xC0,0x40,0x60,0x20,0xA0},//80
				{0x17,0xB5,0x9F,0xC0,0x40,0x60,0x20,0xA0},//90
				
};
char	code  LEDgewei[10][8] = {
				{0x00,0xA0,0x80,0xC0,0x40,0x7F,0x31,0xBF},//0
				{0x00,0xA0,0x80,0xC0,0x40,0x72,0x3F,0xB0},//1
        {0x00,0xA0,0x80,0xC0,0x40,0x7D,0x35,0xB7},//2      
        {0x00,0xA0,0x80,0xC0,0x40,0x75,0x35,0xBF},//3
        {0x00,0xA0,0x80,0xC0,0x40,0x67,0x24,0xBF},//4
				{0x00,0xA0,0x80,0xC0,0x40,0x77,0x35,0xBD},//5
        {0x00,0xA0,0x80,0xC0,0x40,0x7F,0x35,0xBD},//6
				{0x00,0xA0,0x80,0xC0,0x40,0x61,0x21,0xBF},//7
				{0x00,0xA0,0x80,0xC0,0x40,0x7F,0x35,0xBF},//8
				{0x00,0xA0,0x80,0xC0,0x40,0x77,0x35,0xBF},//9
};
/*char	code  BAIFEN[1][8] = {
				0x80,0x41,0x20,0x10,0x08,0x04,0x82,0x01//%
};*/
void delayMs(int x){		//��ʱ����  500΢��*x ����  12MHZ  1΢��һ����������
	int i;
	while(x--){
		for(i=200;i>0;i--){
		}
	}
}


void datapros(int i,int m)
{
	DisplayData[0]=smgduan[sec%10];
	DisplayData[1]=smgduan[sec/10];

	DisplayData[2]=smgduan[min%10]+0X80;
	DisplayData[3]=smgduan[min/10];

	DisplayData[4]=smgduan[hor%10]+0X80;
	DisplayData[5]=smgduan[hor/10];

	/*P0 = BAIFEN[0];
	p30 = 0;
	delayMs(1);
	p30 = 1;
	
	P0 = BAIFEN[1];
	p31 = 0;
	delayMs(1);
	p31 = 1;
	
	P0 = BAIFEN[2];
	p32 = 0;
	delayMs(1);
	p32 = 1;
	
	P0 = BAIFEN[3];
	p33 = 0;
	delayMs(1);
	p33 = 1;
	
	P0 = BAIFEN[4];
	p34 = 0;
	delayMs(1);
	p34 = 1;
	
	P0 = BAIFEN[5];
	p35 = 0;
	delayMs(1);
	p35 = 1;
	
	P0 = BAIFEN[6];
	p36 = 0;
	delayMs(1);
	p36 = 1;
	
	P0 = BAIFEN[7];
	p37 = 0;
	delayMs(1);
	p37 = 1;	*/

	P1 = LEDshiwei[i][0];
	p30 = 0;
	delayMs(1);
	p30 = 1;
	
	P1 = LEDshiwei[i][1];
	p31 = 0;
	delayMs(1);
	p31 = 1;
	
	P1 = LEDshiwei[i][2];
	p32 = 0;
	delayMs(1);
	p32 = 1;
	
	P1 = LEDshiwei[i][3];
	p33 = 0;
	delayMs(1);
	p33 = 1;
	
	P1 = LEDshiwei[i][4];
	p34 = 0;
	delayMs(1);
	p34 = 1;
	
	P1 = LEDshiwei[i][5];
	p35 = 0;
	delayMs(1);
	p35 = 1;
	
	P1 = LEDshiwei[i][6];
	p36 = 0;
	delayMs(1);
	p36 = 1;
	
	P1 = LEDshiwei[i][7];
	p37 = 0;
	delayMs(1);
	p37 = 1;

	P1 = LEDgewei[m][0];
	p30 = 0;
	delayMs(1);
	p30 = 1;
	
	P1 = LEDgewei[m][1];
	p31 = 0;
	delayMs(1);
	p31 = 1;
	
	P1 = LEDgewei[m][2];
	p32 = 0;
	delayMs(1);
	p32 = 1;
	
	P1 = LEDgewei[m][3];
	p33 = 0;
	delayMs(1);
	p33 = 1;
	
	P1 = LEDgewei[m][4];
	p34 = 0;
	delayMs(1);
	p34 = 1;
	
	P1 = LEDgewei[m][5];
	p35 = 0;
	delayMs(1);
	p35 = 1;
	
	P1 = LEDgewei[m][6];
	p36 = 0;
	delayMs(1);
	p36 = 1;
	
	P1 = LEDgewei[m][7];
	p37 = 0;
	delayMs(1);
	p37 = 1;
}





void time()	
{
		
	while(1)
	{
		if(k2==0)		  //��ⰴ��K2�Ƿ���
		{	
			delay(1000);	//��ʱ����
			if(k2==0)
			{
				while(!k2);	 //��ⰴ���Ƿ��ɿ�
				TR0=1;
				break;
			}
		}
		
		datapros(value/10,value%10);
		DigDisplay();	
	
	}		 
}

void main()
{
	int m,n,team1,team0,record;
		m=0;
		value=0;
		team0=0;
		team1=0;
		record=0;
	Timer0Init();  //��ʱ��0��ʼ��
	while(1)
	{
		
		datapros(value/10,value%10);
		DigDisplay();
		
		if(k2==0)		  //��ⰴ��K2�Ƿ���
		{	
			delay(1000);	//��ʱ����
			if(k2==0)
			{
				while(!k2);	 //��ⰴ���Ƿ��ɿ�
				TR0=0;
				time();	 	 //��ʱ�亯��
				Timer0Init();  //��ʱ��0��ʼ��
			}
		}
			if(k0==0)
			{
				delay(1000);
					if(k0==0)
					{
						while(!k0);	
						m++;
						if(m%2==1)
						{
							team0=team0+sec+min*60+hor*3600-record;
							value=(100*team0)/(sec+min*60+hor*3600);
						}
							if(m%2==0)
					{
						team1=team1+sec+min*60+hor*3600-record;
						value=(100*team0)/(sec+min*60+hor*3600);
					}
						record=sec+min*60+hor*3600;
					}					
			}	
			//if(m==1)
			//	value=99;
				value=17;
				
	}					
} 

void Timer0() interrupt 1
{
	TH0=0Xd8;	//����ʱ������ֵ����ʱ10ms
	TL0=0Xf0;
	ssec++;
	if(ssec>=100)  //1s
	{
		ssec=0;
		sec++;
		if(sec>=60)
		{
			sec=0;
			min++;
			if(min>=60)
			{
				min=0;
				hor++;
				if(hor>23)
				{
					hor=0;		
				}
			}
		}	
	}	
}
