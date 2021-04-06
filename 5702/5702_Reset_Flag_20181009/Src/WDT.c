//Program Size: data=9.0 xdata=0 code=122
//HexConvertVer = V24
//CheckSum = 0xC596

#include "WDT.h"


/*PFLAG �Ĵ�������
	PFLAG bit7 ����Ƭ���Ѿ���LVD������λ,���λ�Զ���1 
	PFLAG bit6 ����Ƭ���Ѿ��ɿ��Ź�������λ,���λ�Զ���1 
	PFLAG bit5 ����Ƭ���Ѿ����ⲿ��λ���Ŵ�����λ,���λ�Զ���1 
*/
	

void main(void)
{
	Systeminit();
	while(1)
	{	
		WDTR = 0x5A;
	}
}

void Systeminit(void)
{	
//ϵͳʱ�ӼĴ���,From �����8M	
//====================================================================================//
	CLKSEL = 0x06;																				// Fcpu = 32M/2 = 16M
	CLKCMD = 0x69;				
	CKCON = 0x10;		

//�忴�Ź�
//====================================================================================//	
	WDTR = 0x5A;                   												 // clear watchdog 

	if((PFLAG & 0x40)== 0x40)																//Watchdog Reset   P0 put low
	{	
		P0UR = 0x00;
		P0 = 0x00;
		P0M = 0xff;
		
		P1UR = 0x00;
		P1 = 0xff;
		P1M = 0xff;
		
		P2UR = 0x00;
		P2 = 0x00;
		P2M = 0xff;
		
	}
	else if((PFLAG & 0x80)== 0x80)														//LVD Reset P1 put low
	{	
		P0UR = 0x00;
		P0 = 0xff;
		P0M = 0xff;
		
		P1UR = 0x00;
		P1 = 0x00;
		P1M = 0xff;
		
		P2UR = 0x00;
		P2 = 0xff;
		P2M = 0xff;
		
	}	
	else if((PFLAG & 0x20)== 0x20)														//�ⲿ��· Reset P2 put low
	{
		P0UR = 0x00;
		P0 = 0xff;
		P0M = 0xff;
		
		P1UR = 0x00;
		P1 = 0xff;
		P1M = 0xff;
		
		P2UR = 0x00;
		P2 = 0x00;
		P2M = 0xff;
			
	}
	else																									//other Reset P0 P1 low
	{
		P0UR = 0x00;
		P0 = 0x00;
		P0M = 0xff;
		
		P1UR = 0x00;
		P1 = 0x00;
		P1M = 0xff;
		
		P2UR = 0x00;
		P2 = 0xff;
		P2M = 0xff;		
	}
}