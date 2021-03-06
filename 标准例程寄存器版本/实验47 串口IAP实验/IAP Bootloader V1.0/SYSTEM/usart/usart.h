#ifndef __USART_H
#define __USART_H
#include "sys.h"
#include "stdio.h"	 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//串口1初始化（适合STM32F10x系列）		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2010/1/1
//版本：V1.7
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved
//********************************************************************************
//V1.3修改说明 
//支持适应不同频率下的串口波特率设置.
//加入了对printf的支持
//增加了串口接收命令功能.
//修正了printf第一个字符丢失的bug
//V1.4修改说明
//1,修改串口初始化IO的bug
//2,修改了USART_RX_STA,使得串口最大接收字节数为2的14次方
//3,增加了USART_REC_LEN,用于定义串口最大允许接收的字节数(不大于2的14次方)
//4,修改了EN_USART1_RX的使能方式
//V1.5修改说明
//1,增加了对UCOSII的支持
//V1.6修改说明 20150109
//uart_init函数去掉了开启PE中断
//V1.7修改说明 20150322
//修改OS_CRITICAL_METHOD宏判断为：SYSTEM_SUPPORT_OS
//V1.7-IAP修改说明 20150322
//1,此为IAP版本，修改了部分代码，以适应IAP升级。
//2,新增USART_RX_CNT，用于统计接收字节数
//3,修改USART1_IRQHandler函数，不再使用回车作为接收结束符，而是通过间隔查询实现
////////////////////////////////////////////////////////////////////////////////// 	  
 
#define USART_REC_LEN  			55*1024 //定义最大接收字节数 55K
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
	  	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         		//接收状态标记	
extern u16 USART_RX_CNT;				//接收的字节数	  
//如果想串口中断接收，请不要注释以下宏定义
void uart_init(u32 pclk2,u32 bound);

#endif	   
















