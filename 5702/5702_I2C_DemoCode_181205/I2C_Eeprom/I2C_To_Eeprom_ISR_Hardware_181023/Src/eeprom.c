#include "eeprom.h"
#include "string.h"
/************************************************************************************************
Function:	 	delay time (ms)
input:			cTemp
Output: 		None
Return:  		None
*************************************************************************************************/
void delay_ms (uint8_t cTemp)
{
	uint8_t cCnt,cK;
	for(;cTemp > 0;cTemp--)
	{
		for(cCnt = 245;cCnt > 0;cCnt--)
		{
			WDTR = 0x5A; 									// Clear Watch Dog
			for(cK = 24;cK > 0;cK--)
			{
				_nop_();
			}
		}
	}
}	
/*****************************************************************************************************************
Function:	 	Eeprom Page Write
input:			cDevAddr,cWrDataAddr,p_cWrDataBuf,cNumByteToWrite
Output: 		None
Return:  		None 
******************************************************************************************************************/
void eeprom_write_page(uint8_t cDevAddr,uint16_t cWrDataAddr, uint8_t * p_cWrDataBuf, uint8_t cNumByteToWrite)
{	
	if(f_bI2cFlag == 0)
	{
		if(cNumByteToWrite == 0)    
		{
		 return ;            											 				// error Size
		}

		f_bI2cRx = 0;																			// Clear Flag
		f_bI2cFlag = 1;																		// get Use Right 
		
		g_cDataAddr = cWrDataAddr;												// Data Address
		g_cDevAddr = (cDevAddr & 0xFE) | EEPROM_WRITE;  	// Device Write Address   
		
		g_cI2cDataLen = cNumByteToWrite;          				// Data Length  
		
		memcpy(g_cI2cDataBuf, p_cWrDataBuf, cNumByteToWrite);
		
		I2CCON &= 0xF7;                     							// Clear I2C flag 
		I2CCON |= 0x20;             											// START (STA) = 1
	}
}
/*******************************************************************************************************************
Function:	 	Eeprom Write N Byte
input:			cDevAddr,cWrDataAddr,p_cWrDataBuf,cNumByteToWrite
Output: 		None
Return:  		None
*******************************************************************************************************************/
void eeprom_write_n_byte(uint8_t cDevAddr,uint16_t cWrDataAddr, uint8_t * p_cWrDataBuf, uint8_t cNumByteToWrite)
{	
	uint8_t cPageRemain;
	uint16_t cPageAdrOff;
	
	if (cNumByteToWrite == 0)    
	{
			return ;   																																	// error size
	}

	cPageAdrOff = cWrDataAddr % PAGE_SIZE;																				// The offset address of the starting address
	cPageRemain = PAGE_SIZE - cPageAdrOff;																				// The remaining capacity of the page
	
	if(cPageRemain > cNumByteToWrite)											
		cPageRemain = cNumByteToWrite;	
	
	while(1)
	{
		eeprom_write_page(cDevAddr, cWrDataAddr, p_cWrDataBuf, cPageRemain);				// write page
		if(wait_finish() == ERR)																										// Wait finish
		{
			return ;
		}				
		
		if(cPageRemain == cNumByteToWrite)																					
		{	
			break;																																		// Over
		}
		else
		{
			delay_ms(5);																															// Self-Timed Write Cycle (5 ms typical)
			p_cWrDataBuf += cPageRemain;																					 		// The remaining capacity 
			cWrDataAddr += cPageRemain;																								// write addr
			cNumByteToWrite -= cPageRemain;																						// write Data Number
			
			if(cNumByteToWrite > PAGE_SIZE)																						// next page can't finish
				cPageRemain = PAGE_SIZE;
			else
				cPageRemain = cNumByteToWrite;																					// next page can finish		
		}
	}           								
}
/***************************************************************************************************************
Function:	 	Eeprom Write N Byte
input:			cDevAddr,cWrDataAddr,p_cWrDataBuf,cNumByteToWrite
Output: 		None
Return:  		None
****************************************************************************************************************/
void eeprom_read_n_byte(uint8_t cDevAddr,uint16_t cRdDataAddr, uint8_t * p_cRdDataBuf, uint8_t cNumByteToRead)
{
	if(f_bI2cFlag == 0)
	{
		if(cNumByteToRead == 0)    
		{
		 return ;            											 			
		}	             																	// error Size
		
		f_bI2cRx = 1;
		f_bI2cFlag = 1;																	// get Use Right
		
		g_cDataAddr = cRdDataAddr;											// Data Address
		g_cDevAddr = (cDevAddr & 0xFE) | EEPROM_WRITE;  // Device Write Address  
		
		g_cI2cDataLen = cNumByteToRead - 1;          		// Data Length 
		
		I2CCON &= 0xF7;                     						// Clear I2C flag 
		I2CCON |= 0x20;             										// START = 1
		
 		if(wait_finish() == ERR)												// Wait finish
		{
			return ;
		}																
		
		memcpy(p_cRdDataBuf, g_cI2cDataBuf, cNumByteToRead); // Read Over	
	}
}