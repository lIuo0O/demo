#include "mspi.h"
//-------------------------------------------------------------------------//
uint8_t g_cTxData [MAX_TX_LEN] = {1, 2, 3, 4, 5, 6, 7, 8};	//for test
uint8_t g_cRxData [MAX_RX_LEN];															//for test
/****************************************************************************************
Function:	 	SPI Slave initialization
input:			None
Output: 		None
Return:  		None
****************************************************************************************/
void spi_master_init (void)
{
  P0 |= 0x80;
  P0M |= 0x80;
  P0UR &= 0x7F;				// Set P0.7 (SSN) as output high 

  P1M &= 0xC7;
  P1M |= 0x18;
  P1UR |= 0x20; 			// Be Master  MISO(P15) Input with pull-up   SCK(P13) & MOSI(P14) Output

  SPCON = 0xBA;  		  // Be Master Fcpu/128  CPOL = 1   CPHA = 0

  SPCON |= 0x40;		  // Enable SPI
}
/****************************************************************************************
Function:	 	spi_write_read_byte
input:			None
Output: 		None
Return:  		None
****************************************************************************************/
void spi_WrRd_byte (uint8_t * p_cSrc, uint8_t * p_cDst, uint8_t cLenth)
{
	uint8_t cCnt;
	
	for(cCnt = 0; cCnt < cLenth;cCnt++)
	{
		spi_send_data(*p_cSrc++);					// Send Data
		*p_cDst++ = spi_read_data();			// Receive Data
	}
}
/****************************************************************************************
Function:	 	spi_send_data
input:			None
Output: 		None
Return:  		None
****************************************************************************************/
void spi_send_data (uint8_t cByte)
{
	uint8_t cTemp;
	uint16_t cRetry = 0;
	
	O_IO_CS = 0;												// Enable Slave
	
	SPDAT = cByte;											// Send Byte
	while ((SPSTA & 0x80) != 0x80)
	{
		cRetry++;
		_nop_();
		_nop_();
		if(cRetry >= WAIT_TIME)
		{
			return;						 							// Error
		}
	}
	cTemp = SPDAT;
	
	O_IO_CS = 1;												// Disable Slave
}
/****************************************************************************************
Function:	 	spi_read_data
input:			None
Output: 		None
Return:  		None
****************************************************************************************/
uint8_t spi_read_data (void)
{
  uint8_t cTemp;
	uint16_t cRetry = 0;
	
	O_IO_CS = 0;											// Enable Slave

	SPDAT = 0xFF;											
	while ((SPSTA & 0x80) != 0x80)
	{
		_nop_();
		_nop_();
		if(cRetry >= WAIT_TIME)
		{
			return 0xFF;						 			// Error
		}
	}
	cTemp = SPDAT;										// Receive Byte				 					

	O_IO_CS = 1;										  // Disable Slave
 
	return cTemp;
}