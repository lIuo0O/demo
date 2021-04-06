#ifndef _Timer_h_
#define _Timer_h_
#include <SN8F5702.H>
#include "Timer0.h"
//=============================================================================
#define 		L_MODEL0  	 0       				// 13-bit timer
#define 		L_MODEL1  	 1       				// 16-bit timer
#define 		L_MODEL2   	 2       				// 8 -bit auto-reload Timer
#define 		L_MODEL3   	 3       				// Timer 0 acts as two independent 8 bit Timers
#define 		L_MODE    	 L_MODEL3   		// select mode of timer0
//=============================================================================
										
#if		L_MODE == L_MODEL0
#define			L_TMOD_VALUE     0x04					//MODE0 13BIT-TIME,Fhosc						
#define			L_TCON0_VALUE		 0x00					//T0:Fclk = Fhosc/128 = 32M/128
#define			L_TH0_VALUE			 0xf8					//L_T0_VALUE = 8192(0x2000) - Fclk * T = 8192 - 32M/128 * 1MS = 7942(0x1806)  ����λ����1	 
#define			L_TL0_VALUE			 0x06					

#elif	L_MODE == L_MODEL1
#define			L_TMOD_VALUE     0x05					//MODE1 16BIT-TIME,Fhosc		
#define			L_TCON0_VALUE		 0x00				  //T0:Fclk = Fhosc/128 = 32M/128	
#define			L_TH0_VALUE			 0xfe					//L_T0_VALUE = 65536(0x10000) - Fclk * T = 65536 - 32M/128 * 2MS = 65216(0xfe0c)
#define			L_TL0_VALUE			 0x0c					

#elif	L_MODE == L_MODEL2			
#define			L_TMOD_VALUE     0x06					//MODE2 8BIT-TIME,Fhosc Auto-reload 
#define			L_TCON0_VALUE		 0x00         //T0:Fclk = Fhosc/128 = 32M/128					
#define			L_TH0_VALUE			 0x06					//L_T0_VALUE = 256(0x100) - Fclk * T = 256 - 32M/128 * 1MS = 6(0x06)
#define			L_TL0_VALUE			 0x06					

#elif	L_MODE == L_MODEL3
#define			L_TMOD_VALUE     0x07					//MODE3,TWO 8BIT-TIME
#define			L_TCON0_VALUE		 0x00    			//T0:Fclk = Fcpu/12 = 16M/12, T0:Fclk = Fhosc/128 = 32M/128	
#define			L_TH0_VALUE			 0x38					//L_TH0_VALUE =L_TL0_VALUE = 256(0x100) - Fclk * T = 256 - 32M/128 * 150US = 56(0x38) 
#define			L_TL0_VALUE			 0x06         //L_TL0_VALUE = 256(0x100) - Fclk * T = 256 - 32M/128 * 1MS = 6(0x06)

#endif

void Systeminit(void);
void Timer0init(void);
#endif