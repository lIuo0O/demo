#ifndef __SPI_H_
#define __SPI_H_

#include "hwf.h"

extern GPIO_InitTypeDef GPIO_InitStructure;//����GPIO���õĽṹ�����	
extern NVIC_InitTypeDef NVIC_InitStructure;//����Ƕ�������жϳ�ʼ�������ṹ��
extern SPI_InitTypeDef SPI_InitStructure;//����SPI���õĽṹ�����

void SPI2_Int (void);

void SPI2_SetSpeed(u8 SpeedSet);

u8 SPI2_ReadWriteByte(u8 dat);

#endif 



