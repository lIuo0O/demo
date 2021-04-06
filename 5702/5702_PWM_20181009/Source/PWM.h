#ifndef _PWM_h_
#define _PWM_h_

#include <SN8F5702.h>
//================================================================================================//
#define		L_PWM_CLOCK_32MDIV128			0x00												//PWM timer Clock source
#define		L_PWM_CLOCK_32MDIV64			0x10
#define		L_PWM_CLOCK_32MDIV32			0x20
#define		L_PWM_CLOCK_32MDIV16			0x30
#define		L_PWM_CLOCK_32MDIV8				0x40
#define		L_PWM_CLOCK_32MDIV4				0x50
#define		L_PWM_CLOCK_32MDIV2				0x60
#define		L_PWM_CLOCK_32MDIV1				0x70

#define		L_PWM10_ENABLE						0x01												//PWM使能
#define		L_PWM11_ENABLE						0x02
#define		L_PWM20_ENABLE						0x10
#define		L_PWM21_ENABLE						0x20


#define		L_ENABLE_PWM							0x80												//PWM总使能

//================================================================================================//
void Systeminit(void);
void PWMinit(void);
//================================================================================================//
#endif