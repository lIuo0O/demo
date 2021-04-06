#include "i2c_master.h"
/**************************************************************************************
											Global Variables 
***************************************************************************************/
bit f_bI2cFlag ;
bit	f_bI2cRx;
uint8_t g_cI2cDataBuf[MAX_BUF_LEN];
uint8_t g_cDevAddr;
uint8_t g_cDataAddr;
uint8_t g_cI2cDataLen;
uint8_t g_cI2cBufSize;
/**************************************************************************************
Function: set input pin
          Set slave addr
				  I2C & Interrupt enable
***************************************************************************************/
void i2c_master_init(void)
{
	P0M &= 0xE7;
	P0UR |= 0x18;													 						// set  SDA(P04) SCL(P03)  pin's at input mode
	
	I2CCON = 0x40;         												 		// I2C enable (ENS1),Fclk = Fcpu/256
//	I2CCON = 0xC0;         												 		// I2C enable (ENS1),Fclk = Fcpu/960

	SMBSEL = 0x05;																		// Select the high byte of Tout Register.
	SMBDST = TIME_PERIOD >> 8;
	
	SMBSEL = 0x04;																		// Select the low byte of Tout Register
	SMBDST = TIME_PERIOD;															// 35ms
	
	SMBSEL |= 0x80;																		// EnablE SMBus extension function 
	
	EI2C = 1;               													// I2C Interrupt enable
	EAL = 1;                													// Interrupt enable
}
/**************************************************************************************
Function: Wait trasmit
***************************************************************************************/
bit wait_finish (void)
{
	uint16_t iRetry = 0;
	while(f_bI2cFlag)																	// Wait finish
	{
		iRetry++;
		_nop_();
		_nop_();
		WDTR = 0x5A; 																	  // Clear Watch Dog
		if(iRetry >= WAIT_TIME)
		{
			return ERR;
		}
	}
	
	return OK;
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
			I2CDAT = g_cDevAddr;         							  // Device addr
			break;
		}
		
		// Master Transmit
		case I2C_MT_SLA_ACK: 	
		{			
			g_cI2cBufSize = 0;
				
			I2CDAT = g_cDataAddr;	 										  // trasmit Data Address
			break;
		}
		case I2C_MT_DATA_ACK:                      		// write n byte
		{
			if(f_bI2cRx == 1)														// Read Eeprom 
			{	
				f_bI2cRx = 0;															// Clear Flag
				g_cDevAddr = (g_cDevAddr & 0xFE) | EEPROM_READ;	// Device Read Address  
				I2CCON |= 0x20;             										// RESTART = 1
				break;
			}
			
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
			
			I2CCON |= 0x04;        											// AA = 1
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
			
			f_bI2cFlag = 0;															// finish		
			
			break; 
		}
		default: 
		{
			I2CCON |= 0x10;             								// STOP 	

			g_cI2cBufSize = 0;
			f_bI2cRx = 0;
			f_bI2cFlag = 0;															// finish			
			break; 
		}
	}
	I2CCON &= 0xF7;                     						// Clear I2C flag         
}