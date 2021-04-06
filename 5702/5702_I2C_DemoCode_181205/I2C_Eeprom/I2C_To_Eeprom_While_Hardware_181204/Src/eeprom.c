#include "eeprom.h"
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
	 if (cNumByteToWrite == 0)    
		 return ;                											  						// error size
	
	else 
	{
		i2c_master_start();																					// trasmit start signal
		
		i2c_master_write_addr((cDevAddr & 0xFE) | EEPROM_WRITE); 		// trasmit device Address 
		
		#if (EEPROM_WORD_ADDR_SIZE == 8)
		i2c_master_write_data(((uint8_t) (cWrDataAddr & 0xFF)));  	// trasmit Data Address(8bit)
		#else
		i2c_master_write_data(((uint8_t) (cWrDataAddr >> 8)));      // trasmit Data Address(16bit)
		i2c_master_write_data(((uint8_t) (cWrDataAddr & 0xFF)));
		#endif
		
		while(cNumByteToWrite--)
		{
			i2c_master_write_data(*p_cWrDataBuf++);										// trasmit Data 
		}
		
		i2c_master_stop();																					// trasmit stop signal         										
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
	uint16_t cPageAdrOff = 0;
	uint8_t cPageRemain=0;	
	
	if (cNumByteToWrite == 0)    
			return ;   																																	// error size
	
	else
	{	
		cPageAdrOff = cWrDataAddr % PAGE_SIZE;																				// The offset address of the starting address
		cPageRemain = PAGE_SIZE - cPageAdrOff;																				// The remaining capacity of the page
		
		if(cPageRemain > cNumByteToWrite)											
			cPageRemain = cNumByteToWrite;	
		
		while(1)
		{
			eeprom_write_page(cDevAddr, cWrDataAddr, p_cWrDataBuf, cPageRemain);				// write page
			if(cPageRemain == cNumByteToWrite)																					// finish
				break;
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
}
/***************************************************************************************************************
Function:	 	Eeprom Write N Byte
input:			cDevAddr,cWrDataAddr,p_cWrDataBuf,cNumByteToWrite
Output: 		None
Return:  		None
****************************************************************************************************************/
void eeprom_read_n_byte(uint8_t cDevAddr,uint16_t cRdDataAddr, uint8_t * p_cRdDataBuf, uint8_t cNumByteToRead)
{
	if (cNumByteToRead == 0)    
		return ;               																			// error size
	
	else 
	{
		i2c_master_start();																					// trasmit start signal
		
		i2c_master_write_addr((cDevAddr & 0xFE) | EEPROM_WRITE); 		// trasmit device Write Address 
		
		#if (EEPROM_WORD_ADDR_SIZE == 8)
		i2c_master_write_data(((uint8_t) (cRdDataAddr & 0xFF))); 		// trasmit Data Address(8bit)
		#else
		i2c_master_write_data(((uint8_t) (cRdDataAddr >> 8)));     	// trasmit Data Address(16bit)
		i2c_master_write_data(((uint8_t) (cRdDataAddr & 0xFF)));
		#endif

		i2c_master_restart();																			 	// trasmit restart signal
		
		i2c_master_write_addr((cDevAddr & 0xFE) | EEPROM_READ);    	// trasmit device Read Address 
		
		while(--cNumByteToRead)
		{
			i2c_master_response(ACK); 																// send ACK
			*p_cRdDataBuf++ = i2c_master_read_data();									// receive Data 
		}
		
		i2c_master_response(NACK); 																	// Send NACK
		*p_cRdDataBuf = i2c_master_read_data();											// Read last byte
	
		i2c_master_stop();																					// trasmit stop signal         						
	}
}