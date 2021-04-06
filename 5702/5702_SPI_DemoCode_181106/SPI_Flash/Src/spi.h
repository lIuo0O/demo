#ifndef __SPI_H_
#define __SPI_H_

#include "hwf.h"

extern GPIO_InitTypeDef GPIO_InitStructure;//定义GPIO配置的结构体变量	
extern NVIC_InitTypeDef NVIC_InitStructure;//定义嵌套向量中断初始化向量结构体
extern SPI_InitTypeDef SPI_InitStructure;//定义SPI配置的结构体变量

void SPI2_Int (void);

void SPI2_SetSpeed(u8 SpeedSet);

u8 SPI2_ReadWriteByte(u8 dat);

#endif 



