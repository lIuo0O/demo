#include "sn8f5702.h"
#include "i2c_slave.h"

extern uint8_t g_cI2cTxBuf[MAX_BUF_LEN];
extern uint8_t g_cI2cRxBuf[MAX_BUF_LEN];  //for test

/*************************************************************************************************************
Function: I2C Slave DemoCode
*************************************************************************************************************/
int Main(void)
{
	CLKSEL = 0x07;									// Fcpu = 32M/1
	CLKCMD = 0x69;
	CKCON = 0x31;										// 4 read cycles

	P0 = 0x00;
	P0M = 0x00;
	P0UR = 0xFF;										// set input with pull-up					
					
	P1 = 0x00;
	P1M = 0x00;
	P1UR = 0xFF;										// set input with pull-up					
									
	P2 = 0x00;
	P2M = 0x00;
	P2UR = 0xFF;										// set input with pull-up

	i2c_slave_init();

	while(1)
	{
		WDTR = 0x5A; 								// Clear watch dog
	}
}