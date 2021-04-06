// The system clock frequency is IHRC 32MHz
//Program Size: data=9.0 xdata=0 code=113
//HexConvertVer = V22
//CheckSum = 0xBBB5
//2018.10.09_V3.2

#include "Timer0.h"

//=============================================================================================================//
//main loop
//=============================================================================================================//
void main(void)
{ 
	Systeminit();	
	Timer0init();   
	EAL = 1;  										// Golbal Interrupt enable
  while (1) 
	{
    WDTR = 0x5A;                // clear watchdog if watchdog enable
  }
}

//==============================================================================================//
//  Systeminit
//==============================================================================================//
void Systeminit(void)
{	
//ϵͳʱ�ӼĴ���,From �����8M	
//====================================================================================//
	CLKSEL = 0x06;									// Fcpu = 32M/2 = 16M
	CLKCMD = 0x69;				
	CKCON = 0x10;										// From = 8M
	
//�忴�Ź�
//====================================================================================//	
	WDTR = 0x5A;                    // clear watchdog 

//GPIO��ʼ��,	P24,P26�����,��ⶨʱ�Ƿ���ȷ
//====================================================================================//	
	P0 = 0;
	P0M = 0;
	P0UR = 0xff;

	P1 = 0;
	P1M = 0x50;				 				// P1.4/P1.6 as output low
	P1UR = 0xff;

	P2 = 0;
	P2M = 0;                
	P2UR = 0xaf;
}