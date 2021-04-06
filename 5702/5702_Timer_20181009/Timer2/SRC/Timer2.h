#ifndef _Timer2_h_
#define _Timer2_h_
#include <SN8F5702.H>
#include "Timer2.h"
						
#define 		L_TH2_VALUE 		0xf8			//1500US = 2000 * 1/Fclk = 2000 * 12/16M  2000 = 65536(0x10000) - 63536(0xf830) 		
#define 		L_TL2_VALUE 		0x30

void Systeminit(void);
void Timer2init(void);

#endif