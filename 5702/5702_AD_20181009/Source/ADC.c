#include "ADC.h"

//=============================================================================================================//
//						DATA
//=============================================================================================================//
idata uint16_t r_ad_value1 = 0;                           //滤波之后的AD值
idata uint16_t r_ad_value2 = 0;													
idata uint16_t r_ad_value3 = 0;

idata	uint8_t	r_ad1_cnt = 0;															//滑动滤波寄存器													
idata	uint8_t	r_ad2_cnt = 0;
idata	uint8_t	r_ad3_cnt = 0;

idata	uint16_t r_ad1_fifo[L_AD_SAMPLE_MAX] = 0;					 //AD的fifo值
idata	uint16_t r_ad2_fifo[L_AD_SAMPLE_MAX] = 0;
idata	uint16_t r_ad3_fifo[L_AD_SAMPLE_MAX] = 0;

//=============================================================================================================//
//	AD 初始化
//=============================================================================================================//
void ADinit(void)
{
	ADM |= 0x80;																					//ADC Enable
	ADM |= L_AD_CHANNEL1;
	
	ADR = 0x40;																					//AIN channel Enable
	ADR |= L_AD_SPEEDDIV16;
	
	VREFH = L_VREF_INT;							
	VREFH |= L_VERFH_4V;
	
	P1CON |= 0x0c;																				// AD口使用需打开将P1CON的相应的位置1,否则漏电
}

//=============================================================================================================//
//	AD 滑动滤波
//=============================================================================================================//
void	ADSample(void)
{
//外部AD通道,
//===============================================================================//	
	r_ad1_fifo[r_ad1_cnt ++] = GetAD(L_AD_CHANNEL1);
	if(r_ad1_cnt == L_AD_SAMPLE_MAX) 
		r_ad1_cnt = 0;
	r_ad_value1 = ADAverge(r_ad1_fifo);
	
	r_ad2_fifo[r_ad2_cnt ++] = GetAD(L_AD_CHANNEL2);
	if(r_ad2_cnt == L_AD_SAMPLE_MAX) 
		r_ad2_cnt = 0;
	r_ad_value2 = ADAverge(r_ad2_fifo);
//===============================================================================//	

//内部2V/3V/4V输入通道, 该通道的参考电压为VDD,输入检测通道为 2V/3V/4V(由VREFH Bit0,Bit1决定)
//																																			VREFH   0   0    2V 输入通道
//																																			VREFH   0   1    3V	输入通道
//																																			VREFH   1   0    4V 输入通道
//该通道根据IC内部的2V/3V/4V来求出VDD的电压,计算公式：VDD = 4096/r_ad_value3 *(2V/3V/4V) 
//本Deno选择内部4V输入通道来计算VDD电压
//===============================================================================//	
	VREFH |= L_VERFH_INTVDD;
	r_ad3_fifo[r_ad3_cnt ++] = GetAD(L_AD_CHANNEL3);
	if(r_ad3_cnt == L_AD_SAMPLE_MAX) 
		r_ad3_cnt = 0;
	r_ad_value3 = ADAverge(r_ad3_fifo);	
	VREFH &= (L_VERFH_INTVDD^0xff);
}

//=============================================================================================================//
//	AD 滑动平均算法
//=============================================================================================================//
uint16_t ADAverge(uint16_t *ad_array)
{
	uint8_t i = 0;
	uint16_t temp_sum = 0;
	
	for(i = 0;i < L_AD_SAMPLE_MAX;i++)
	{
		temp_sum += *(ad_array+i);
	}
	temp_sum = temp_sum >> L_AD_SHIFT;
	
	return temp_sum;
}
//=======================================================================
//	AD 去极值平均
//=======================================================================
uint16_t GetAD(uint8_t	ad_channel)
{ 	
	uint8_t i = 0;
	uint16_t j = 0;
	uint16_t temp_ad_max = 0;
	uint16_t temp_ad_min = 0xffff;
	uint16_t temp_ad_buf = 0;
	uint16_t temp_ad_data = 0;
	
	ADM = (ADM&0XF0)|ad_channel;
	
	for(i = 0; i < L_AD_SAMPLE_MAX + 2; i++)				
	{
		ADM |= 0x40;													//Start ADC
		while((ADM & 0x20) != 0X20);					//EOC   				
		ADM &= 0xdf;
		
		temp_ad_buf = ADB;
		temp_ad_buf = (temp_ad_buf << 4) + (ADR & 0X0F);
		temp_ad_data += temp_ad_buf; 
		
		if(temp_ad_buf < temp_ad_min)
		{
			temp_ad_min = temp_ad_buf;
		}
		if(temp_ad_buf > temp_ad_max)
		{
			temp_ad_max = temp_ad_buf;
		}	
	}
	
	temp_ad_data = (temp_ad_data - temp_ad_min - temp_ad_max) >> L_AD_SHIFT;					
	return	temp_ad_data;
}

