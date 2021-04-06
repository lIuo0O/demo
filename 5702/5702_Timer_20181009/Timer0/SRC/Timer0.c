//  The program is an example of Timer0 to implement it.
//  you can select mode0~3 by "#define MODE Mode0~3" 
//  Timer 0 function List:
//      1. Mode 0 : 13-bit timer
//      2. Mode 1 : 16-bit timer
//      3. Mode 2 : 8 -bit auto-reload Timer
//      4. Mode 3 : Timer 0 acts as two independent 8 bit Timers ¡V TL0, TH0. Timer0 and Timer1

#include "Timer0.h"

//==============================================================================================//
//  Timer0 init
//==============================================================================================//
void Timer0init(void)
{
  TMOD = L_TMOD_VALUE;          // Mode of Timer 0 
	TCON0 = L_TCON0_VALUE;        // T0EXT = Fhosc.
  TH0 = L_TH0_VALUE;            // Initial values
  TL0 = L_TL0_VALUE;						// T0RATE is Fhosc/128 = 250K	
	TR0 = 1;										  // Timer 0 enable
  ET0 = 1;  
#if	 L_MODE == L_MODEL3					//TWO 8BIT-TIME
	ET1 = 1; 											// Timer 1 isr enable
	TR1 = 1;											// enable Timer 1 Run control
#endif                                                   
}

//==============================================================================================//
//  Timer0 ISR
//==============================================================================================//
void Timer0ISR(void) interrupt ISRTimer0   // Vector @  0x0B
{
#if	  L_MODE == L_MODEL3 				// if Timer0 is Mode 3,The timer TL0 is controlled by T0		
	  TL0 = L_TL0_VALUE;	
#elif L_MODE != L_MODEL2				// if Timer0 is Mode 2, the TL0 will auto reload  
	  TH0 = L_TH0_VALUE;          
		TL0 = L_TL0_VALUE;
#endif	
    P14 = ~ P14;                // P1.4 toggle
}

//==============================================================================================//
//  Timer1 ISR
//==============================================================================================//
#if L_MODE == L_MODEL3
void Timer1ISR(void) interrupt ISRTimer1   // Vector @  0x1B
{ 
    TH0 = L_TH0_VALUE;          // timer1 used
    P16 = ~ P16;               	// P1.6 toggle
}
#endif
