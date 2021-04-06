#include "sn8f5702.h"
#include "sspi.h"
/*************************************************************************************************************
Function: SPI slave DemoCode
*************************************************************************************************************/
int Main(void)
{
	CLKSEL = 0x05;								// Fcpu = 32M / 4 = 8M
  CLKCMD = 0x69;
  CKCON = 0x00;								  // IROM run at 8 MHz

	P0 = 0x00;
  P0M = 0x00;
  P0UR = 0xFF;									

  P1 = 0x00;
  P1M = 0x00;
  P1UR = 0xFF; 									

  P2 = 0x00;
  P2M = 0x00;
  P2UR = 0xFF;

	spi_slave_init();					// SPI Slave initialization
	
	while(1)
	{
		WDTR = 0x5A; 						// clear watchdog				
	}
}





