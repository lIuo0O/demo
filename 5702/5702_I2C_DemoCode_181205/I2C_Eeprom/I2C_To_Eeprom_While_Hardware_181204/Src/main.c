#include "sn8f5702.h"
#include "i2c_master.h"
#include "eeprom.h"

#define DATA_ADDR  0
uint8_t g_cTxDataBuf[5] = {0xAA,0xAB,0xAC,0xAD,0xAE};   			// for test
uint8_t g_cRxDataBuf[5] = 0;																	// for test
	
/*************************************************************************************************************
Function: Eeprom(I2C)  DemoCode
*************************************************************************************************************/	
void main(void) 
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

	i2c_master_init();    

	while (1) 
	{
		WDTR = 0x5A;        				// clear watchdog 
		
//		eeprom_write_page(EEPROM_ADDR,DATA_ADDR, g_cTxDataBuf, sizeof(g_cTxDataBuf));		// Master Transmit Page  (NumByteToWrite must less than The remaining capacity of the page)
		
//		eeprom_write_n_byte(EEPROM_ADDR,DATA_ADDR, g_cTxDataBuf, sizeof(g_cTxDataBuf)); 	// Master Transmit Nbyte 
		
		eeprom_read_n_byte(EEPROM_ADDR,DATA_ADDR, g_cRxDataBuf, sizeof(g_cRxDataBuf));		// Master Receive	 Nbyte
		
		delay_ms(10);
	}
}