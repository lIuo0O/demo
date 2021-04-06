#ifndef _Timer1_h_
#define _Timer1_h_
#include <SN8F5702.H>
#include "Timer1.h"
//=============================================================================
#define 		L_MODEL0  	 0       				// 13-bit timer
#define 		L_MODEL1  	 1       				// 16-bit timer
#define 		L_MODEL2   	 2       				// 8 -bit auto-reload Timer
#define 		L_MODE    	 L_MODEL2   		// select mode of timer0
//=============================================================================
										
#if		L_MODE == L_MODEL0
#define			L_TMOD_VALUE     0x40					//MODE0 13BIT-TIME,Fhosc						
#define			L_TCON0_VALUE		 0x00					//T0:Fclk = Fhosc/128 = 32M/128
#define			L_TH1_VALUE			 0xf8					//1MS = 1/Fclk * 250= 128/32M * 250     250 =  8192(0x2000) - 7942(0x1806)   高三位需置1
#define			L_TL1_VALUE			 0x06

#elif	L_MODE == L_MODEL1
#define			L_TMOD_VALUE     0x50					//MODE1 16BIT-TIME,Fhosc		
#define			L_TCON0_VALUE		 0x00				  //T0:Fclk = Fhosc/128 = 32M/128	
#define			L_TH1_VALUE			 0xfe					//2MS = 1/Fclk * 500 = 128/32M * 500    500 = 65536(0x10000) - 65036(0xfe0c) 
#define			L_TL1_VALUE			 0x0c

#elif	L_MODE == L_MODEL2			
#define			L_TMOD_VALUE     0x60					//MODE2 8BIT-TIME,Fhosc Auto-reload 
#define			L_TCON0_VALUE		 0x00         //T0:Fclk = Fhosc/128 = 32M/128					
#define			L_TH1_VALUE			 0x06					//1MS = 1/Fclk * 250 = 128/32M * 250     250 = 256(0x100) - 6(0x06)
#define			L_TL1_VALUE			 0x06

#endif

void Systeminit(void);
void Timer1init(void);
#endif