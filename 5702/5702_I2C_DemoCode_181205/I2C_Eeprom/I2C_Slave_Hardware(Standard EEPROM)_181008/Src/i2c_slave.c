#include "i2c_slave.h"
/***************************************************************************
													Global Variable
***************************************************************************/
bit f_bRxFlag = 0;
bit f_bAddrFlag = 0;

uint8_t g_cDataAddr = 0;
uint8_t g_cI2cRamBuf[MAX_BUF_LEN]; 						// EEPROM ÄÚ´æ
/**************************************************************************************
Function: set input pin
          Set slave addr
				  Interrupt enable
***************************************************************************************/
void i2c_slave_init (void)
{	
	P0M &= 0xE7;
	P0UR |= 0x18;													 			// set  SDA(P04) SCL(P03)  pin's at input mode
	
//	I2CCON = 0x40;         								 		// I2C enable (ENS1),Fclk = Fcpu/256
	I2CCON = 0xC0;         											// I2C enable (ENS1),Fclk = Fcpu/960
	
	SMBSEL = 0x05;														  // Select the high byte of Tout Register.
	SMBDST = TIME_PERIOD >> 8;
	
	SMBSEL = 0x04;												 		  // Select the low byte of Tout Register
	SMBDST = TIME_PERIOD;									 		  // 35ms
	
	SMBSEL |= 0x80;												      // EnablE SMBus extension function 
	
	EI2C = 1;                     							// I2C Interrupt enable
	EAL = 1;                      							// Interrupt enable
	
	I2CADR = I2C_SLAVE_ADDR;     								// init slave addr
	I2CCON |= 0x04; 														// AA = 1			
}
/**************************************************************************************
Function: i2c_slave isr service
***************************************************************************************/
void isr_i2c_slave (void) interrupt ISRI2c
{
	switch(I2CSTA)
	{      
		//Slave Transmit
		case I2C_ST_SLA_ACK:
		case I2C_ST_DATA_ACK:		
		{
			I2CDAT = g_cI2cRamBuf[g_cDataAddr++];
			break;
		}
		
		//Slave Receive
		case I2C_SR_SLA_ACK:
		case I2C_SR_GCALL_ACK:
		{
			I2CCON |= 0x04; 											// AA = 1	
			break;
		}
		case I2C_SR_DATA_ACK:
		case I2C_SR_GCALL_DATA_ACK:	
		{
			if(f_bAddrFlag == 0)
			{
				f_bAddrFlag	= 1;										// Set Data Address Flag			
				g_cDataAddr = I2CDAT;								// Receive Data Address
			}
			else
			{
				g_cI2cRamBuf[g_cDataAddr++] = I2CDAT;
			}
			break;			
		}

		default:
		{
			f_bAddrFlag = 0;											// Clear
			I2CCON &= 0xCF;											  // Clear STA & STOP			
			break;		
		}			
	}
	
	I2CCON |= 0x04; 													// AA = 1	
	I2CCON &= 0xF7;        										// Clear I2C flag 
	
	if(g_cDataAddr >= MAX_BUF_LEN)
	{
		g_cDataAddr = 0;												// Over Size
	}
}
