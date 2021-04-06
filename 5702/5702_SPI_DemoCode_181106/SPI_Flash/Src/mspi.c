#include "mspi.h"
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

  SPCON = 0xBE;  		  // Be Master Fcpu/128  CPOL = 1   CPHA = 1 		

  SPCON |= 0x40;		  // Enable SPI
}
/****************************************************************************************
Function:	 	SPI Send byte
input:			None
Output: 		None
Return:  		None
****************************************************************************************/
uint8_t spi_WtRd_Byte (uint8_t cByte)
{
	uint8_t cData;
	uint16_t cRetry = 0;

	SPDAT = cByte;								// Send Data
	while (SPSTA != 0x80)
	{
		cRetry++;
		_nop_();
		_nop_();
		if(cRetry >= WAIT_TIME)
		{
			return 0xFF;						 // Error
		}
	}
	cData = SPDAT;							 // Read Data
	
	return cData;
}