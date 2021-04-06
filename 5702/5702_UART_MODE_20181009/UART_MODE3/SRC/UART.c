#include "UART.h"    									
#include "Timer0.h"


bit f_rx = 0;																															//正在接收标志位
idata uint8_t r_check_model = L_CHECK_MODEL;															//校验模式
idata uint8_t r_uart_rx_length = 0;																			  //该笔数据接收的长度
idata uint8_t r_uart_rx_lengthbuf = 0;																		//接收数据缓存buf,用于判断是否接收完成
idata uint8_t r_urat_rx_data[L_RX_LENGTH] = {0};													//接收到的数据缓存
idata uint8_t r_urat_tx_data[L_TX_LENGTH] = {0};													//发生数据缓存,该Demo中未使用

//=============================================================================================================//
// UART init
//=============================================================================================================//
void UART3init(void)
{
	P05 = 1;
	P0M |= 0x20; 																	//UTX初始化输出高	
	P0M &= 0xbf; 																	//URX初始化数模模式
	
	SM0 = 1;																			//模式3
	SM1 = 1;
	REN0 = 1;																			//使能接收功能
	switch (L_BRUD_RATE)													//波特率设置
  {
  	case L_BRUD_RATE_4800:
         PCON &= 0x7f;       													
         BD = 1;				
	       S0RELH = L_S0RELH_4800;
         S0RELL = L_S0RELL_4800;      						
  		break;		
  	case L_BRUD_RATE_9600:
         PCON &= 0x7f;       													
         BD = 1;				
	       S0RELH = L_S0RELH_9600;
         S0RELL = L_S0RELL_9600;      						
  		break;
  	case L_BRUD_RATE_19200:
         PCON &= 0x7f;       													
         BD = 1;				
	       S0RELH = L_S0RELH_19200;
         S0RELL = L_S0RELL_19200;      								
  		break;
  	case L_BRUD_RATE_38400:
         PCON &= 0x7f;       													
         BD = 1;				
	       S0RELH = L_S0RELH_38400;
         S0RELL = L_S0RELL_38400;      								
  		break;
  	case L_BRUD_RATE_56000:
			   PCON |= 0x80; 
         BD = 1;		
	       S0RELH = L_S0RELH_56000;
         S0RELL = L_S0RELL_56000;      					      																	
  		break;
  	case L_BRUD_RATE_57600:
         PCON |= 0x80;   
         BD = 1;			
	       S0RELH = L_S0RELH_57600;
         S0RELL = L_S0RELL_57600;      					   															
  		break;
  	case L_BRUD_RATE_115200:
         PCON |= 0x80;  
         BD = 1;			
	       S0RELH = L_S0RELH_115200;
         S0RELL = L_S0RELL_115200;      					    															
  		break;
  	case L_BRUD_RATE_128000:
         PCON |= 0x80;       													
         BD = 1;				
	       S0RELH = L_S0RELH_128000;
         S0RELL = L_S0RELL_128000;      								
  		break;	
  	case L_BRUD_RATE_250000:
         PCON |= 0x80;       													
         BD = 1;			
	       S0RELH = L_S0RELH_250000;
         S0RELL = L_S0RELL_250000;      									
  		break;			
  	default:
  		break;
  }
	ES0 = 1;																						//使能UART中断
}

void UARTwriteonebyte(uint8_t r_txdata)
{
	uint8_t i = 0;
	uint8_t temp_check = 0;
	uint8_t temp_number = 0;
	
	temp_check = r_txdata;
	
	for(i=0;i<8;i++)																		//判读发送数据‘1’的个数
	{
		if(temp_check & 0x01)
			temp_number++;
		temp_check = _crol_(temp_check,1);								//右位判断下一位数据是否为‘1’
	}
	
	if(r_check_model == L_UNEVEN_CHECK)									//奇校验
	{
		if(temp_number & 0x01)														//第9位,奇偶校验的值
			TB80 = 0;
		else
			TB80 = 1;
	}
	else if(r_check_model == L_EVEN_CHECK)              //偶校验
	{
		if(temp_number & 0x01)													  //第9位,奇偶校验的值
			TB80 = 1;
		else
			TB80 = 0;	
	}
	
	S0BUF = r_txdata;
	while(!TI0);																				//等待发送完成
	TI0 = 0;
}

//=============================================================================================================//
// UART respond 若在接收状态,5ms判断一次数据是否接收完成,若接收完数据据后,将接收到的数据数据再发生出去
//=============================================================================================================//
void UARTrespond(void)
{
	uint8_t i = 0;
	if(f_1ms == 1)
	{
		f_1ms = 0;
		if((--r_timer_5ms) == 0)														
		{
			r_timer_5ms = L_TIMER_5MS;
			if(f_rx == 1)																							//5ms判断一次是否在接收数据状态,该时间根据设置的波特率不同进行修改
			{
				if(r_uart_rx_length == r_uart_rx_lengthbuf)     				//判断该帧数据是否接收完,若接收完将接收到的数据再发送出去    
				{
					f_rx = 0;
					
					for(i=0;i<r_uart_rx_length;i++)
					{
						UARTwriteonebyte(r_urat_rx_data[i]);
					}
					
					r_uart_rx_length = 0;
					r_uart_rx_lengthbuf = 0;
				}
				else																										
				{
					r_uart_rx_lengthbuf = r_uart_rx_length;	
				}
			}
		}
	}
}

//=============================================================================================================//
// UART ISR
//=============================================================================================================//
void UARTISR(void) interrupt ISRUart 
{
	uint8_t i = 0;
	uint8_t temp_check = 0;
	uint8_t temp_number = 0;

	if(RI0 == 1)                                      			//RI0软件清零
	{
		RI0 = 0;
		f_rx = 1;																							//置接收标志位
		temp_check = S0BUF;
		
		for(i=0;i<8;i++)																			//判断接收数据‘1’的个数
		{
			if((temp_check & 0x01) == 1)
				temp_number++;
			temp_check = _crol_(temp_check,1);
		}
		
		if(RB80 == 1)																					//第9位奇偶校验
			temp_number++;
		
		if(r_check_model == L_UNEVEN_CHECK)										//奇校验
		{
			if(temp_number & 0x01)
				r_urat_rx_data[r_uart_rx_length++] = temp_check;
		}
		else if(r_check_model == L_EVEN_CHECK)								//偶校验
		{
			if(!(temp_number & 0x01))
				r_urat_rx_data[r_uart_rx_length++] = temp_check;		
		}
		else																									//直接存储接收数据,若选择奇偶校验该else语句可以不需要
		{
			r_urat_rx_data[r_uart_rx_length++] = temp_check;		
		}
		
	}
}



