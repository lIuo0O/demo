#include "i2c_master.h"
#include "string.h"
/**************************************************************************************
											Global Variables 
***************************************************************************************/
bit		 	f_bI2cFlag = 0;
bit		 	f_bI2cRxOk = 0;
uint8_t g_cI2cDataBuf[MAX_BUF_LEN];
uint8_t g_cI2cAddr = 0;
uint8_t g_cI2cDataLen = 0;
uint8_t g_cI2cBufSize = 0;
/**************************************************************************************
Function: set input pin
          Set slave addr
				  I2C & Interrupt enable
***************************************************************************************/
void i2c_master_init(void)
{
	P0M &= 0xE7;
	P0UR |= 0x18;													 // set  SDA(P04) SCL(P03)  pin's at input mode
	
//	I2CCON = 0x40;         							 // I2C enable (ENS1),Fclk = Fcpu/256
	I2CCON = 0xC0;         								 // I2C enable (ENS1),Fclk = Fcpu/960

	SMBSEL = 0x05;												 // Select the high byte of Tout Register.
	SMBDST = TIME_PERIOD >> 8;
	
	SMBSEL = 0x04;												 // Select the low byte of Tout Register
	SMBDST = TIME_PERIOD;									 // 35ms
	
	SMBSEL |= 0x80;												 // EnablE SMBus extension function 
	
	EI2C = 1;               							 // I2C Interrupt enable
	EAL = 1;                							 // Interrupt enable
}
/****************************************************************************************
Function:	 	I2C Trasmit data
input:			cWrDataAddr,p_cWrDataBuf,cNumByteToWrite
Output: 		None
Return:  		None
****************************************************************************************/
void i2c_master_write_n_byte(uint8_t cWrDataAddr, uint8_t * p_cWrDataBuf, uint8_t cNumByteToWrite)
{
	if(f_bI2cFlag == 0)
	{
		if (cNumByteToWrite > MAX_BUF_LEN)    
				return ;              										 		// over buf Size
		
		if (cNumByteToWrite == 0)    
				return ;              											  // error Size
		
		f_bI2cFlag = 1;																		// get Use Right
		g_cI2cDataLen = cNumByteToWrite;          				// set length           								
		g_cI2cAddr = (cWrDataAddr & 0xFE) | I2C_WRITE;  	// write mode  
		
		memcpy(g_cI2cDataBuf, p_cWrDataBuf, cNumByteToWrite);
		
		I2CCON &= 0xF7;                     							// Clear I2C flag 
		I2CCON |= 0x20;             											// START (STA) = 1
	}
}

/*****************************************************************************************
Function:	 	I2C Receive data
input:			cRdDataAddr,p_cRdDataBuf,cNumByteToWrite
Output: 		None
Return:  		None
******************************************************************************************/
void i2c_master_read_n_byte	(uint8_t cRdDataAddr, uint8_t * p_cRdDataBuf, uint8_t cNumByteToRead)
{
	uint16_t iRetry  = 0;
	if(f_bI2cFlag == 0)
	{
		if (cNumByteToRead > MAX_BUF_LEN)    
			return ;               												// over buf Size
		if (cNumByteToRead == 0)    
			return ;               												// error Size
		
		f_bI2cRxOk = 0;
		f_bI2cFlag = 1;																	// get Use Right
		
		g_cI2cDataLen = cNumByteToRead - 1;          	  // set length
		g_cI2cAddr = (cRdDataAddr & 0xFE) | I2C_READ;	  // read mode
	
		I2CCON &= 0xF7;                     						// Clear I2C flag 
		I2CCON |= 0x20;             										// START = 1

		while(!f_bI2cRxOk)
		{
			iRetry++;
			_nop_();
			WDTR = 0x5A;        													// clear watchdog 
			if(iRetry >= WAIT_TIME)
			{
				return ;
			}
		}
		
		f_bI2cRxOk = 0;
		memcpy(p_cRdDataBuf, g_cI2cDataBuf, cNumByteToRead);
	}
}
/**************************************************************************************
Function: I2C ISR Routine 
***************************************************************************************/
void isr_i2c_master (void) interrupt ISRI2c    								
{
	switch (I2CSTA)
	{
		// Master Transmit  Address
		case I2C_START:
		case I2C_RESTART:
		{
			I2CCON &= 0xCF;											 				// Clear STOP & STA	 
			I2CDAT = g_cI2cAddr;         							  // Tx/Rx addr
			break;
		}
		
		// Master Transmit
		case I2C_MT_SLA_ACK: 	
		{			
			g_cI2cBufSize = 0;
			
			I2CDAT = g_cI2cDataBuf[g_cI2cBufSize++];	  // write first byte
			break;
		}
		case I2C_MT_DATA_ACK:                      		// write n byte
		{
			if(g_cI2cBufSize >= g_cI2cDataLen) 					// Last byte
			{        											
				I2CCON |= 0x10;         								  // STOP 
				f_bI2cFlag = 0;														// finish	
			}
			else
			{
				I2CDAT = g_cI2cDataBuf[g_cI2cBufSize++];
			}
			
			break;
		}
				
		// Master Receive 
		case I2C_MR_SLA_ACK:                      		// get slave addr
		{
			g_cI2cBufSize = 0;
		
			I2CCON |= 0x04;         										// AA = 1
			break;
		}
		case I2C_MR_DATA_ACK:                      		// read n byte
		{
			g_cI2cDataBuf[g_cI2cBufSize++] = I2CDAT; 
			
			I2CCON |= 0x04;        										  // AA = 1
			if (g_cI2cBufSize >= g_cI2cDataLen)
			{
				I2CCON &= 0xFB;         									// AA = 0		
			}
			break;
		}
		case I2C_MR_DATA_NACK:  
		{
			g_cI2cDataBuf[g_cI2cBufSize] = I2CDAT; 
			
			I2CCON |= 0x10;             								// STOP 	
			
			f_bI2cRxOk = 1;
			f_bI2cFlag = 0;															// finish					
			break; 
		}
		default: 
		{
			I2CCON |= 0x10;             								// STOP 	

			g_cI2cBufSize = 0;
			f_bI2cRxOk = 0;
			f_bI2cFlag = 0;															// finish			
			break; 
		}
	}
	I2CCON &= 0xF7;                     						// Clear I2C flag         
}