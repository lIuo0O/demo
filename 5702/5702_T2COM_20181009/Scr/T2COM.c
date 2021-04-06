#include "T2COM.h"

//=================================================================================================//
//T2COM init
//=================================================================================================//
void T2COMinit(void)
{
//	T2CON |= L_T2COM_CLK_FCPUDIV24;        // T2PS��Fcpu/24(Bit:7)
  T2CON &= L_T2COM_CLK_FCPUDIV12;			     // T2PS��Fcpu/12(Bit:7)
	T2CON |= L_T2COM_CLK_T2PS;						   // T2ʱ��Դ����T2PS(Bit:1..0)	
	
	CCEN = L_ENABLE_T2COM0|L_ENABLE_T2COM1|L_ENABLE_T2COM2|L_ENABLE_T2COM3;								//ʹ��T2COM0,T2COM1,T2COM2,T2COM3�ȽϹ���
//	CCEN = L_ENABLE_T2COM0|L_ENABLE_T2COM1|L_ENABLE_T2COM2;															//ʹ��T2COM0,T2COM1,T2COM2�ȽϹ���
//	CCEN = L_ENABLE_T2COM0|L_ENABLE_T2COM1;																							//ʹ��T2COM0,T2COM1�ȽϹ���
//	CCEN = L_ENABLE_T2COM0;																															//ʹ��T2COM0�ȽϹ���
	
	IEN1 &= L_DISABLE_T2COM0_ISR;						//��ֹT2COM0�ж�  Bit2
//	IEN1 |= L_ENABLE_T2COM0_ISR;					//ʹ��T2COM0�ж�
	
	IEN1 &= L_DISABLE_T2COM1_ISR;						//��ֹT2COM1�ж�	Bit3
//	IEN1 |= L_ENABLE_T2COM1_ISR;					//ʹ��T2COM3�ж�
	
	IEN1 &= L_DISABLE_T2COM2_ISR;						//��ֹT2COM2�ж�	Bit4
//	IEN1 |= L_ENABLE_T2COM2_ISR;					//ʹ��T2COM3�ж�
	
	IEN1 &= L_DISABLE_T2COM3_ISR;						//��ֹT2COM3�ж�	Bit5
//	IEN1 |= L_ENABLE_T2COM3_ISR;					//ʹ��T2COM3�ж�	
	
	CRCL = L_CRCL_VALUE;										
	CRCH = L_CRCH_VALUE;
	
	CCL1 = L_CCL1_VALUE;										
	CCH1 = L_CCH1_VALUE;
	
	CCL2 = L_CCL2_VALUE;
	CCH2 = L_CCH2_VALUE;

	CCL3 = L_CCL3_VALUE;
	CCH3 = L_CCH3_VALUE;	
	
	TL2 = L_TL2_VALUE; 									//T2��ʱ1MS(PWM 1KHz)
	TH2 = L_TH2_VALUE; 
	
	TF2 = 0;														// ���ж������־
	ET2 = 1;														// ��T2�ж�
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
//T2COM4 ISR ��TH2/T2L = CRCH/CRCLʱ���ж�,��Demo����δʹ�ܸ��ж�
//=================================================================================================//
void T2COM4ISR() interrupt ISRCom4
{
	P14 = ~ P14;										// test	
}

//=================================================================================================//
//T2COM1 ISR ��TH2/T2L = CCH1/CCL1ʱ���ж�,��Demo����δʹ�ܸ��ж�
//=================================================================================================//
void T2COM1ISR() interrupt ISRCom1	
{
	P15 = ~ P15;										// test	
}

//=================================================================================================//
//T2COM1 ISR ��TH2/T2L = CCH2/CCL2ʱ���ж�,��Demo����δʹ�ܸ��ж�
//=================================================================================================//
void T2COM2ISR() interrupt ISRCom2		
{
	P16 = ~ P16;										// test	
}

//=================================================================================================//
//T2COM1 ISR ��TH2/T2L = CCH3/CCL3ʱ���ж�,��Demo����δʹ�ܸ��ж�
//=================================================================================================//
void T2COM3ISR() interrupt ISRCom3 	
{
	P17 = ~ P17;										// test	
}