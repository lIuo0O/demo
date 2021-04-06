#ifndef _Timer_h_
#define _Timer_h_
#include <SN8F5702.H>
#include "Timer0.h"				

#define			L_TIMER_5MS			5			

extern bit f_1ms;
extern idata uint8_t r_timer_5ms;

void Systeminit(void);
void Timer0init(void);
#endif