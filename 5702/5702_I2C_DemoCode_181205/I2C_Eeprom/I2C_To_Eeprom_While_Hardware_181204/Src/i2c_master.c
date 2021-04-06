#include "i2c_master.h"
/**************************************************************************************
Function:	 	I2C Initialize
input:			None
Output: 		None
Return:  		None
***************************************************************************************/
void i2c_master_init(void)
{
	P0M &= 0xE7;
	P0UR |= 0x18;													 // set  SDA(P04) SCL(P03)  pin's at input mode										
	
//	I2CCON = 0x40;         							 // I2C enable (ENS1),Fclk = Fcpu/256
//	I2CCON = 0x42;         							 // I2C enable (ENS1),Fclk = Fcpu/60
	I2CCON = 0xC0;         								 // I2C enable (ENS1),Fclk = Fcpu/960
	
	SMBSEL = 0x05;												 // Select the high byte of Tout Register.
	SMBDST = TIME_PERIOD >> 8;
	
	SMBSEL = 0x04;												 // Select the low byte of Tout Register
	SMBDST = TIME_PERIOD;									 // 35ms
	
	SMBSEL |= 0x80;												 // EnablE SMBus extension function 
}
/**************************************************************************************
Function:	 	I2C Stop
input:			None
Output: 		None
Return:  		None
***************************************************************************************/
void i2c_master_stop(void)
{
	I2CCON |= 0x10;   	      						 // set STOP (STO) = 1   
	I2CCON &= 0xF7;												 // clear I2C flag (SI) = 0 
}
/**************************************************************************************
Function:	 	I2C Start
input:			None
Output: 		None
Return:  		None
***************************************************************************************/
void i2c_master_start(void)
{
	I2CCON &= 0xF7;  											  // clear I2C flag (SI) = 0	
	I2CCON |= 0x20;  												// set  START (STA) = 1   
//-------------------------------------------------------------------------------//	
	if((wait_finish()) == I2C_ERR)
	{
		i2c_master_stop();									  // trasmit stop signal       
		return ;
	}		
//-------------------------------------------------------------------------------//	
	if(I2CSTA != I2C_START)	 								// wait	START condition transmitted	
	{
		i2c_master_stop();										// trasmit stop signal       
		return ;
	}
//-------------------------------------------------------------------------------//	
	I2CCON &= 0xDF;													// clear START (STA) = 0 	 
}
/**************************************************************************************
Function:	 	I2C ReStart
input:			None
Output: 		None
Return:  		None
***************************************************************************************/
void i2c_master_restart(void)
{	
	I2CCON |= 0x20;  												// set  START (STA) = 1 
	I2CCON &= 0xF7;  											  // clear I2C flag (SI) = 0	
//-------------------------------------------------------------------------------//	
	if((wait_finish()) == I2C_ERR)
	{
		i2c_master_stop();									  // trasmit stop signal       
		return ;
	}		
//-------------------------------------------------------------------------------//	
	if(I2CSTA != I2C_RESTART)	 							// wait	START condition transmitted	
	{
		i2c_master_stop();										// trasmit stop signal       
		return ;
	}	
//-------------------------------------------------------------------------------//	
	I2CCON &= 0xDF;   											// clear START (STA) = 0        
}
/**************************************************************************************
Function:	 	I2C Trasmit Address
input:			cAddr
Output: 		None
Return:  		None
***************************************************************************************/
void i2c_master_write_addr(uint8_t	cAddr)
{
	I2CDAT = cAddr;													// transmit Address			
	I2CCON &= 0xF7;   											// clear START (STA) = 0   
//-------------------------------------------------------------------------------//	
	if((wait_finish()) == I2C_ERR)
	{
		i2c_master_stop();									  // trasmit stop signal       
		return ;
	}		
//-------------------------------------------------------------------------------//	
	if(I2CSTA == I2C_MR_SLA_ACK)
	{
		return ;										 				  // I2C Read  device Address 
	}
//-------------------------------------------------------------------------------//	
	if(I2CSTA == I2C_MT_SLA_ACK)
	{
		return ;														 // I2C Write device Address 
	}
//-------------------------------------------------------------------------------//	
	i2c_master_stop();									   // trasmit stop signal       
}
/**************************************************************************************
Function:	 	I2C Trasmit one byte
input:			cWrData
Output: 		None
Return:  		None
***************************************************************************************/
void i2c_master_write_data(uint8_t	cWrData)
{
	I2CDAT = cWrData;												// transmit Data
	I2CCON &= 0xF7;                    			// Clear I2C flag  
//-------------------------------------------------------------------------------//	
	if((wait_finish()) == I2C_ERR)
	{
		i2c_master_stop();									 // trasmit stop signal       
		return ;
	}		
//-------------------------------------------------------------------------------//	
	if(I2CSTA != I2C_MT_DATA_ACK)  				 // wait	Data transmitted
	{
		i2c_master_stop();									 // trasmit stop signal       
		return ;
	}
}
/**************************************************************************************
Function:	 	I2C send ACK or NACK
input:			cMode
Output: 		None
Return:  		None
***************************************************************************************/
void i2c_master_response(bit cMode)
{
	I2CCON |= 0x04;													// send ACK AA = 1
	if(cMode == NACK)
		I2CCON &= 0xFB;												// send NACK AA = 0
//-------------------------------------------------------------------------------//	
	I2CCON &= 0xF7;  											  // clear I2C flag (SI) = 0	
//-------------------------------------------------------------------------------//
	if((wait_finish()) == I2C_ERR)
	{
		i2c_master_stop();									  // trasmit stop signal       
		return ;
	}	
//-------------------------------------------------------------------------------//	
	if(I2CSTA == I2C_MR_DATA_ACK)  				  // wait	Data receive finish	
	{ 
		return ;
	}			
//-------------------------------------------------------------------------------//	
	if(I2CSTA == I2C_MR_DATA_NACK)  			  // wait	Data receive finish	
	{       
		if(cMode == ACK)
		{
			i2c_master_stop();								  // trasmit stop signal       
			return ;
		}			
		
		return ;								
	}			
//-------------------------------------------------------------------------------//	
	i2c_master_stop();										  // trasmit stop signal          
}
/**************************************************************************************
Function:	 	I2C Receive one byte
input:			None
Output: 		None
Return:  		cRdData
***************************************************************************************/
uint8_t i2c_master_read_data(void)
{
	return I2CDAT;
}
/**************************************************************************************
Function:	 	Wait Finish
input:			None
Output: 		None
Return:  		cRdData
***************************************************************************************/
bit wait_finish (void)
{
	uint16_t iRetry = 0;
//-------------------------------------------------------------------------------//
	while(!(I2CCON & 0x08))
	{
		iRetry++;
		_nop_();
		WDTR = 0x5A;        									 // clear watchdog 
		if(iRetry >= WAIT_TIME)
		{
			return I2C_ERR;
		}
	}	
//-------------------------------------------------------------------------------//
	return I2C_OK;
}
