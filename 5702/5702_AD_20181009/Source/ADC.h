#ifndef _ADC_h_
#define _ADC_h_
#include <SN8F5702.h>
//===========================================================================================================//
//						CONST
//===========================================================================================================//
#define	L_AD_CHANNEL1			0x03				//AIN3	P13								
#define	L_AD_CHANNEL2			0x02				//AIN2	P12
#define	L_AD_CHANNEL3			0x0a				//AINa	�ڲ��ο���ѹ���ͨ��,���Է������VDD�Ĵ�С

#define L_AD_SPEEDDIV16		0x00				//fosc/16
#define L_AD_SPEEDDIV8		0x10				//fosc/8
#define L_AD_SPEEDDIV1		0x20				//fosc/1
#define L_AD_SPEEDDIV2		0x30				//fosc/2

#define	L_VREF_INT				0x00				//�ڲ��ο�,P54ΪGPIO
#define	L_VREF_EXT				0X80				//�ⲿ�ο�,FROM P54

#define	L_VERFH_2V				0x00				//2V
#define	L_VERFH_3V				0x01				//3V
#define	L_VERFH_4V				0x02				//4V
#define	L_VERFH_VDD				0x03				//VDD
#define	L_VERFH_INTVDD		0x04				//�ڲ�vdd������				

#define	L_AD_SAMPLE_MAX			8					//����8�Σ�����������øĶ�����ֹADֵ�ۼ�ƽ������
#define	L_AD_SHIFT					3					//����3��ƽ��
//===========================================================================================================//
void Systeminit(void);
void ADinit(void);
void ADSample(void);
uint16_t GetAD(uint8_t adchannel);
uint16_t ADAverge(uint16_t *adarray);
//===========================================================================================================//
#endif