//  The program is an example of Timer0 to implement it.
//  you can select mode0~3 by "#define MODE Mode0~3"      
//  Timer 1 function List:
//      1. Mode 0 : 13-bit timer
//      2. Mode 1 : 16-bit timer
//      3. Mode 2 : 8 -bit auto-reload Timer

#include "Timer1.h"

//==============================================================================================//
//  Timer1 init
//==============================================================================================//
void Timer1init(void)
{
  TMOD = L_TMOD_VALUE;          // Mode of Timer 0 
	TCON0 = L_TCON0_VALUE;        // T0EXT = Fhosc.
  TH1 = L_TH1_VALUE;            // Initial values
  TL1 = L_TL1_VALUE;						// T0RATE is Fhosc/128 = 250K	
	TR1 = 1;										  // Timer 0 enable
  ET1 = 1;                                                    
}

//==============================================================================================//
//  Timer1 ISR
//==============================================================================================//
void Timer1ISR(void) interrupt ISRTimer1   
{ 
#if L_MODE != L_MODEL2
    TL1 = L_TL1_VALUE;          // timer1 used
		TH1 = L_TH1_VALUE;  
#endif	
	  P14 = ~ P14;               	// P1.4 toggle
}


