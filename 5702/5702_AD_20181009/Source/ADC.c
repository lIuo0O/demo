#include "ADC.h"

//=============================================================================================================//
//						DATA
//=============================================================================================================//
idata uint16_t r_ad_value1 = 0;                           //�˲�֮���ADֵ
idata uint16_t r_ad_value2 = 0;													
idata uint16_t r_ad_value3 = 0;

idata	uint8_t	r_ad1_cnt = 0;															//�����˲��Ĵ���													
idata	uint8_t	r_ad2_cnt = 0;
idata	uint8_t	r_ad3_cnt = 0;

idata	uint16_t r_ad1_fifo[L_AD_SAMPLE_MAX] = 0;					 //AD��fifoֵ
idata	uint16_t r_ad2_fifo[L_AD_SAMPLE_MAX] = 0;
idata	uint16_t r_ad3_fifo[L_AD_SAMPLE_MAX] = 0;

//=============================================================================================================//
//	AD ��ʼ��
//=============================================================================================================//
void ADinit(void)
{
	ADM |= 0x80;																					//ADC Enable
	ADM |= L_AD_CHANNEL1;
	
	ADR = 0x40;																					//AIN channel Enable
	ADR |= L_AD_SPEEDDIV16;
	
	VREFH = L_VREF_INT;							
	VREFH |= L_VERFH_4V;
	
	P1CON |= 0x0c;																				// AD��ʹ����򿪽�P1CON����Ӧ��λ��1,����©��
}

//=============================================================================================================//
//	AD �����˲�
//=============================================================================================================//
void	ADSample(void)
{
//�ⲿADͨ��,
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

//�ڲ�2V/3V/4V����ͨ��, ��ͨ���Ĳο���ѹΪVDD,������ͨ��Ϊ 2V/3V/4V(��VREFH Bit0,Bit1����)
//																																			VREFH   0   0    2V ����ͨ��
//																																			VREFH   0   1    3V	����ͨ��
//																																			VREFH   1   0    4V ����ͨ��
//��ͨ������IC�ڲ���2V/3V/4V�����VDD�ĵ�ѹ,���㹫ʽ��VDD = 4096/r_ad_value3 *(2V/3V/4V) 
//��Denoѡ���ڲ�4V����ͨ��������VDD��ѹ
//===============================================================================//	
	VREFH |= L_VERFH_INTVDD;
	r_ad3_fifo[r_ad3_cnt ++] = GetAD(L_AD_CHANNEL3);
	if(r_ad3_cnt == L_AD_SAMPLE_MAX) 
		r_ad3_cnt = 0;
	r_ad_value3 = ADAverge(r_ad3_fifo);	
	VREFH &= (L_VERFH_INTVDD^0xff);
}

//=============================================================================================================//
//	AD ����ƽ���㷨
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
//	AD ȥ��ֵƽ��
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

