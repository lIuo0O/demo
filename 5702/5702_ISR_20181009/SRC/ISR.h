#ifndef	_ISR_h_
#define _ISR_h_
#include <SN8F5702.H>

/*
�ж����ȼ���6����(����ÿ����������ȼ��ɸߵ���)
              Group0�� INT0    PWM1           IIC
							Group1:  T0      ADC            SPI
							Group2:  		     PWM3           T2 COM0
							Group3:  T1                     T2 COM1
							Group4:  UART       					  T2 COM2
							Group5:  T2         					  T2 COM3       
����ISR_priority1,ISR_priority0������������֮������ȼ���
              ������������ BIT0 ���� Group0 �����ȼ�(11���ȼ����,10���,01�ڵ�һ��,00���ȼ����)
							������������ BIT1 ���� Group1 �����ȼ�(11���ȼ����,10���,01�ڵ�һ��,00���ȼ����)
							������������ BIT2 ���� Group2 �����ȼ�(11���ȼ����,10���,01�ڵ�һ��,00���ȼ����)
							������������ BIT3 ���� Group3 �����ȼ�(11���ȼ����,10���,01�ڵ�һ��,00���ȼ����)
							������������ BIT4 ���� Group4 �����ȼ�(11���ȼ����,10���,01�ڵ�һ��,00���ȼ����)
							������������ BIT5 ���� Group5 �����ȼ�(11���ȼ����,10���,01�ڵ�һ��,00���ȼ����)
*/

#define 		L_ISR_IP0    0x05        //����Group0�����ȼ���ߣ�Group4�����ȼ���Σ�Group2�����ȼ��ڵ�һ����Group1/2/5�����ȼ����
#define 		L_ISR_IP1    0x11 


void Systeminit(void);
void ISRinit(void);

#endif