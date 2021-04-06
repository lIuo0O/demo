#ifndef _T2COM_h_
#define	_T2COM_h_

#include <SN8F5702.H>

#define			L_T2COM_CLK_T2PS				0x01
#define			L_T2COM_CLK_FCPUDIV12		0x7f

#define			L_T2COM_CLK_FCPUDIV24		0x80


#define			L_ENABLE_T2COM0					0x02
#define			L_ENABLE_T2COM1					0x08
#define			L_ENABLE_T2COM2					0x20
#define			L_ENABLE_T2COM3					0x80

#define			L_DISABLE_T2COM0_ISR		0xfb
#define			L_DISABLE_T2COM1_ISR		0xf7
#define			L_DISABLE_T2COM2_ISR		0xef
#define			L_DISABLE_T2COM3_ISR		0xdf

#define			L_ENABLE_T2COM0_ISR			0x04
#define			L_ENABLE_T2COM1_ISR			0x08
#define			L_ENABLE_T2COM2_ISR			0x10
#define			L_ENABLE_T2COM3_ISR			0x20

//=====================================================================================================//
//T2定时器初值 L_T2_VALUE	= 65536(0x10000) - Fcpu/T2clk * T = 65536 - 32M/12 *1MS = 62869(0xf595)
//=====================================================================================================//
//CRC<T2 输出低电平,波形先输出低再输出高,
//=====================================================================================================//
#define			L_T2_VALUE							0xf595
#define			L_TH2_VALUE							((L_T2_VALUE>>8)&0x00ff)			
#define			L_TL2_VALUE							(L_T2_VALUE &0x00ff)

#define			L_CRC_PWM_DUTY					(uint16_t)((65536 -L_T2_VALUE)*(1-0.90))					//DUTY = 90%
#define			L_CRC_VALUE							(L_CRC_PWM_DUTY + L_T2_VALUE)
#define			L_CRCH_VALUE						((L_CRC_VALUE>>8) & 0x00ff)
#define			L_CRCL_VALUE						(L_CRC_VALUE & 0x00ff)

#define			L_CC1_PWM_DUTY					(uint16_t)((65536 -L_T2_VALUE)*(1-0.75))					//DUTY = 75%
#define			L_CC1_VALUE							(L_CC1_PWM_DUTY + L_T2_VALUE)
#define			L_CCH1_VALUE						((L_CC1_VALUE>>8) & 0x00ff)
#define			L_CCL1_VALUE						(L_CC1_VALUE & 0x00ff)

#define			L_CC2_PWM_DUTY					(uint16_t)((65536 -L_T2_VALUE)*(1-0.50))					//DUTY = 50%
#define			L_CC2_VALUE							(L_CC2_PWM_DUTY + L_T2_VALUE)
#define			L_CCH2_VALUE						((L_CC2_VALUE>>8) & 0x00ff)
#define			L_CCL2_VALUE						(L_CC2_VALUE & 0x00ff)

#define			L_CC3_PWM_DUTY					(uint16_t)((65536 -L_T2_VALUE)*(1-0.25))					//DUTY = 25%
#define			L_CC3_VALUE							(L_CC3_PWM_DUTY + L_T2_VALUE)
#define			L_CCH3_VALUE						((L_CC3_VALUE>>8) & 0x00ff)
#define			L_CCL3_VALUE						(L_CC3_VALUE & 0x00ff)


void Systeminit(void);
void T2COMinit(void);

#endif