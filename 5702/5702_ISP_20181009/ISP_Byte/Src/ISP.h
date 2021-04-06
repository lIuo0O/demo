#ifndef _ISP_h_
#define _ISP_h_
#include <SN8F5702.H>

#define		L_ISP_ADDR	0x0ec0                     					//ISP addr page 118 


extern idata uint8_t r_isp_write_data[32];

void Systeminit(void);
void ISPinit(void);
void ISPpagewrite(uint8_t *r_ram_address);
void ISPpageread1(void);
void ISPpageread2(void);
#endif