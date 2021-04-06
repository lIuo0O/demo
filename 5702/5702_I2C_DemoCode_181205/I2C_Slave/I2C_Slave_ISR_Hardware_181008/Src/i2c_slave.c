#include "i2c_slave.h"
/***************************************************************************
													Global Variable
***************************************************************************/
//RX variable
idata uint8_t g_cI2cRxBuf[MAX_BUF_LEN] = 0; 
uint8_t g_cI2cRxLen = 0;
//TX variable
uint8_t g_cI2cTxBuf[MAX_BUF_LEN] = {1,2,3,4,5};		// for test
uint8_t g_cI2cTxLen = 0;

uint8_t g_cDataAddr = 0;
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
	
	SMBSEL = 0x05;												 			// Select the high byte of Tout Register.
	SMBDST = TIME_PERIOD >> 8;
	
	SMBSEL = 0x04;												 			// Select the low byte of Tout Register
	SMBDST = TIME_PERIOD;									 			// 35ms
	
	SMBSEL |= 0x80;												 			// EnablE SMBus extension function 
	
	EI2C = 1;                     							// I2C Interrupt enable
	EAL = 1;                      							// Interrupt enable  1101 1000
	
	I2CADR = I2C_SLAVE_ADDR;     								// init slave addr	
  I2CCON |= 0x04;               						  // AA = 1
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
		{
			g_cI2cTxLen = 0;
			I2CDAT = g_cI2cTxBuf[g_cI2cTxLen++];
			break;
		}
		case I2C_ST_DATA_ACK:
		{
			I2CDAT = g_cI2cTxBuf[g_cI2cTxLen++];
			break;
		}
		
		//Slave Receive
		case I2C_SR_SLA_ACK:
		case I2C_SR_GCALL_ACK:
		{
			g_cI2cRxLen = 0;
			break;
		}
		case I2C_SR_DATA_ACK:
		case I2C_SR_GCALL_DATA_ACK:
		{
			g_cI2cRxBuf[g_cI2cRxLen++] = I2CDAT;
			break;
		}
		
		default:
		{
			g_cI2cRxLen = 0;	
			g_cI2cTxLen = 0;
			
			I2CCON &= 0xCF;											  // Clear STA & STOP			
			break;		
		}		
	}
	
	I2CCON |= 0x04; 													// AA = 1	
	I2CCON &= 0xF7;        										// Clear SI
}
