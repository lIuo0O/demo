#include "sspi.h"
/****************************************************************************************
Function:	 	SPI Slave initialization
input:			None
Output: 		None
Return:  		None
****************************************************************************************/
void spi_slave_init (void)
{
  P0M &= 0xFB;
  P0UR |= 0x04;							// Be Slave Set SSN(P02) Input with pull-up 

  P1M &= 0xC7;
  P1M |= 0x20;
  P1UR |= 0x18; 						// Be Slave Set MISO(P15) Output   SCK(P13) & MOSI(P14) Input with pull-up 

  SPCON = 0x8A; 						// Be Slave Fcpu/128  CPOL = 1   CPHA = 0

  SPCON |= 0x40;						// Enable SPI

  IEN1 |= 0x02;							// Enable SPI Interrupt
  EAL = 1;							 	  // Enable Global Interrupts
}
/****************************************************************************************
Function:	 	SPi  ISR Routine
input:			None
Output: 		None
Return:  		None
****************************************************************************************/
void isr_spi (void) interrupt ISRSpi
{
	uint8_t cTemp;
	
	cTemp = SPDAT;
	switch(SPSTA)
	{
		case 0x80 :
		{	
			switch(cTemp)
			{
				case 1 : SPDAT = 8; break;
				case 2 : SPDAT = 7; break;
				case 3 : SPDAT = 6; break;
				case 4 : SPDAT = 5; break;
				case 5 : SPDAT = 4; break;
				case 6 : SPDAT = 3; break;
				case 7 : SPDAT = 2; break;
				case 8 : SPDAT = 1; break;
				default : SPDAT = 0xFF; break;
			}
			break;
		}
		default : break;
	}
}