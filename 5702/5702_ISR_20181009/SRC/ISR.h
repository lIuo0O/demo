#ifndef	_ISR_h_
#define _ISR_h_
#include <SN8F5702.H>

/*
中断优先级分6个组(下面每个组里的优先级由高到低)
              Group0： INT0    PWM1           IIC
							Group1:  T0      ADC            SPI
							Group2:  		     PWM3           T2 COM0
							Group3:  T1                     T2 COM1
							Group4:  UART       					  T2 COM2
							Group5:  T2         					  T2 COM3       
常量ISR_priority1,ISR_priority0决定了组与组之间的优先级：
              这两个常量的 BIT0 决定 Group0 的优先级(11优先级最高,10其次,01在低一点,00优先级最低)
							这两个常量的 BIT1 决定 Group1 的优先级(11优先级最高,10其次,01在低一点,00优先级最低)
							这两个常量的 BIT2 决定 Group2 的优先级(11优先级最高,10其次,01在低一点,00优先级最低)
							这两个常量的 BIT3 决定 Group3 的优先级(11优先级最高,10其次,01在低一点,00优先级最低)
							这两个常量的 BIT4 决定 Group4 的优先级(11优先级最高,10其次,01在低一点,00优先级最低)
							这两个常量的 BIT5 决定 Group5 的优先级(11优先级最高,10其次,01在低一点,00优先级最低)
*/

#define 		L_ISR_IP0    0x05        //设置Group0的优先级最高，Group4的优先级其次，Group2的优先级在低一级，Group1/2/5的优先级最低
#define 		L_ISR_IP1    0x11 


void Systeminit(void);
void ISRinit(void);

#endif