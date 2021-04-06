#include "sn8f5702.h"
#include "i2c_master.h"

uint8_t g_cTxDataBuf[MAX_BUF_LEN] = {5,4,3,2,1};  					// for test
uint8_t g_cRxDataBuf[MAX_BUF_LEN] = 0;						  // for test
/*************************************************************************************************************
Function: I2C Master DemoCode
*************************************************************************************************************/
void main(void) 
{
	CLKSEL = 0x07;									// Fcpu = 32M / 4
	CLKCMD = 0x69;
	CKCON = 0x30;										// 4 read cycles
	
	P0 = 0x00;
	P0M = 0x00;
	P0UR = 0xFF;										// set input with pull-up					
					
	P1 = 0x00;
	P1M = 0x00;
	P1UR = 0xFF;										// set input with pull-up					
									
	P2 = 0x00;
	P2M = 0x00;
	P2UR = 0xFF;										// set input with pull-up

	i2c_master_init();    

	while (1) 
	{
		WDTR = 0x5A;        				// clear watchdog 	
		
		i2c_master_read_n_byte(I2C_SLAVE_ADDR, g_cRxDataBuf, sizeof(g_cRxDataBuf));		// Master Receive
		
//		i2c_master_write_n_byte(I2C_SLAVE_ADDR, g_cTxDataBuf, sizeof(g_cTxDataBuf));	// Master Transmit 
		
	}
}
		
	