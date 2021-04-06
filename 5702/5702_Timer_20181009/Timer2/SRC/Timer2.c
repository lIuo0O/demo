
#include "Timer2.h"

//==============================================================================================//
//  Timer2 init
//==============================================================================================//
void Timer2init(void)
{
	T2CON = 0x01;									//Fclk = Fcpu/12 = 16M/12
  TH2 = L_TH2_VALUE;            // Initial values
  TL2 = L_TL2_VALUE;						// T0RATE is Fhosc/128 = 250K										
  ET2 = 1;                                                    
}

//==============================================================================================//
//  Timer1 ISR
//==============================================================================================//
void Timer2ISR(void) interrupt ISRTimer2   // Vector @  0x1B
{ 
    TF2 = 0;                	// Clear Timer2 overflow flag  
	
    TH2 = L_TH2_VALUE;        // Initial values
    TL2 = L_TL2_VALUE;
	
	  P14 = ~ P14;              // P1.4 toggle
}