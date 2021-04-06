#include "T2COM.h"

//=================================================================================================//
//T2COM init
//=================================================================================================//
void T2COMinit(void)
{
//	T2CON |= L_T2COM_CLK_FCPUDIV24;        // T2PS：Fcpu/24(Bit:7)
  T2CON &= L_T2COM_CLK_FCPUDIV12;			     // T2PS：Fcpu/12(Bit:7)
	T2CON |= L_T2COM_CLK_T2PS;						   // T2时钟源来自T2PS(Bit:1..0)	
	
	CCEN = L_ENABLE_T2COM0|L_ENABLE_T2COM1|L_ENABLE_T2COM2|L_ENABLE_T2COM3;								//使能T2COM0,T2COM1,T2COM2,T2COM3比较功能
//	CCEN = L_ENABLE_T2COM0|L_ENABLE_T2COM1|L_ENABLE_T2COM2;															//使能T2COM0,T2COM1,T2COM2比较功能
//	CCEN = L_ENABLE_T2COM0|L_ENABLE_T2COM1;																							//使能T2COM0,T2COM1比较功能
//	CCEN = L_ENABLE_T2COM0;																															//使能T2COM0比较功能
	
	IEN1 &= L_DISABLE_T2COM0_ISR;						//禁止T2COM0中断  Bit2
//	IEN1 |= L_ENABLE_T2COM0_ISR;					//使能T2COM0中断
	
	IEN1 &= L_DISABLE_T2COM1_ISR;						//禁止T2COM1中断	Bit3
//	IEN1 |= L_ENABLE_T2COM1_ISR;					//使能T2COM3中断
	
	IEN1 &= L_DISABLE_T2COM2_ISR;						//禁止T2COM2中断	Bit4
//	IEN1 |= L_ENABLE_T2COM2_ISR;					//使能T2COM3中断
	
	IEN1 &= L_DISABLE_T2COM3_ISR;						//禁止T2COM3中断	Bit5
//	IEN1 |= L_ENABLE_T2COM3_ISR;					//使能T2COM3中断	
	
	CRCL = L_CRCL_VALUE;										
	CRCH = L_CRCH_VALUE;
	
	CCL1 = L_CCL1_VALUE;										
	CCH1 = L_CCH1_VALUE;
	
	CCL2 = L_CCL2_VALUE;
	CCH2 = L_CCH2_VALUE;

	CCL3 = L_CCL3_VALUE;
	CCH3 = L_CCH3_VALUE;	
	
	TL2 = L_TL2_VALUE; 									//T2定时1MS(PWM 1KHz)
	TH2 = L_TH2_VALUE; 
	
	TF2 = 0;														// 清中断请求标志
	ET2 = 1;														// 开T2中断
}

//=================================================================================================//
//Timer2 ISR
//=================================================================================================//
void Timer2ISR(void) interrupt ISRTimer2   
{
	if(TF2 == 1)												// clear by software
	{
		TF2 = 0;
		TL2 = L_TL2_VALUE; 
		TH2 = L_TH2_VALUE; 
		P00 = ~P00;											//test
	}
}


//=================================================================================================//
//T2COM4 ISR 当TH2/T2L = CRCH/CRCL时进中断,本Demo程序未使能该中断
//=================================================================================================//
void T2COM4ISR() interrupt ISRCom4
{
	P14 = ~ P14;										// test	
}

//=================================================================================================//
//T2COM1 ISR 当TH2/T2L = CCH1/CCL1时进中断,本Demo程序未使能该中断
//=================================================================================================//
void T2COM1ISR() interrupt ISRCom1	
{
	P15 = ~ P15;										// test	
}

//=================================================================================================//
//T2COM1 ISR 当TH2/T2L = CCH2/CCL2时进中断,本Demo程序未使能该中断
//=================================================================================================//
void T2COM2ISR() interrupt ISRCom2		
{
	P16 = ~ P16;										// test	
}

//=================================================================================================//
//T2COM1 ISR 当TH2/T2L = CCH3/CCL3时进中断,本Demo程序未使能该中断
//=================================================================================================//
void T2COM3ISR() interrupt ISRCom3 	
{
	P17 = ~ P17;										// test	
}