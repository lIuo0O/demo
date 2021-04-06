
#include "Timer0.h"

bit f_1ms = 0;																						//1ms��־λ
idata uint8_t r_timer_5ms = L_TIMER_5MS;								  //5ms��׼ʱ��,�����жϸ�֡�����Ƿ������
//==============================================================================================//
//  Timer0 init ��ʱ1ms
//==============================================================================================//
void Timer0init(void)
{
  TMOD = 0x06;          
	TCON0 = 0x00;        
  TH0 = 0x06;           
  TL0 = 0x06;						
	TR0 = 1;							
  ET0 = 1;                                                   
}

//==============================================================================================//
//  Timer0 ISR
//==============================================================================================//
void Timer0ISR(void) interrupt ISRTimer0   // Vector @  0x0B
{
	f_1ms = 1;    
}
