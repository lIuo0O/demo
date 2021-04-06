
#include "PWM.h"


void PWMinit(void)
{
//PWM1初始化 PWM1 rate is Fhosc/1  f_pwm1 = (32M/1)/3200 = 10KHz 占空比50%
//====================================================================================//
	PW1YL = 0x80;														
	PW1YH = 0x0c;
	
	PW1DL = 0x40;																
	PW1DH = 0x06;
	
	PW1BL = PW1DL;
	PW1BH = PW1DH;
	
	PW1A = 0x00;
	           
	PW1CH = L_PWM10_ENABLE | L_PWM11_ENABLE | L_PWM20_ENABLE | L_PWM21_ENABLE;	
	PW1M = L_ENABLE_PWM | L_PWM_CLOCK_32MDIV1; 													
}


