//Program Size: data=107.0 xdata=0 code=507
//HexConvertVer = V22
//CheckSum = 0xCFF3
//2018.10.09_V3.2

#include "ISP.h"
#include <intrins.h>                            					 // for _nop_
#include <absacc.h>																				 // for CBYTE

/*ISP操作注意事项：
1.5702 ISP 只支持页写模式,不支持字节写模式,即写一次Flash,写一次Flash不管你设置的数据长度为多大,系统一次都是写32Byte.
2.5702内置4KB的程序存储(IROM),均分为128页(每页32Byte),程序中的前10页与最后一页不可以进行ISP操作,否则会导致上电错误或复位错误.
3.当你需要写10Byte数据到Flash中,那么那么就需要定义10Byte的Ram,且Ram只能定义在idata,不能定义在xdata.
*/

uint16_t code r_rom_data[16] _at_ L_ISP_ADDR;							//定义IROM的首地址
//每次写Flash的长度最多32Byte,

idata uint16_t r_read_rom_addr = L_ISP_ADDR;
idata uint16_t r_isp_write_data[16] = {0};								//需写Flash的数据	
idata uint16_t r_isp_read_data1[16] = {0};								//读出Flash中的数据
idata uint16_t r_isp_read_data2[16] = {0};	



//====================================================================================================//
//初始化写ISP数据
//====================================================================================================//
void ISPinit(void)
{
	uint8_t i = 0;
	for(i=0;i<16;i++)
	{
		r_isp_write_data[i] = i + 1000;
	}
}

//====================================================================================================//
//写ISP
//====================================================================================================//
void ISPpagewrite(uint16_t *r_ram_address)
{
	WDTR = 0x5a;															//清狗
  PERAM = (uint8_t)r_ram_address;						//数据缓存器(IRAM)的第一个地址
	PEROMH = L_ISP_ADDR >> 8;									//页编程(IROM)的第一个地址(15bit-8bit)
	PEROML = (L_ISP_ADDR & 0x00f0);						//页编程(IROM)的第一个地址(7bit-5bit)
	PEROML |= 0x0a;														//开始ISP操作
	PECMD = 0x5a;															//开始ISP操作					
}	

//====================================================================================================//
//读ISP  直接读rom数组名称
//====================================================================================================//
void ISPpageread1(void)
{
	uint8_t i= 0;
	for(i=0;i<16;i++)
	{
		r_isp_read_data1[i] =  r_rom_data[i];
	}
}

//====================================================================================================//
//读ISP  指定地址读rom
//====================================================================================================//
void ISPpageread2(void)
{
	uint8_t i= 0;
	for(i=0;i<16;i++)
	{
		r_isp_read_data2[i] = (CBYTE[r_read_rom_addr++]<<8) +  CBYTE[r_read_rom_addr++];
	}
}
