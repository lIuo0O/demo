#include "sn8f5702.h"
#include "mspi.h"
/*************************************************************************************************************
Function: SPI Master DemoCode
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

  spi_master_init();

  while (1)
  {
    WDTR = 0x5A; 						 																	// clear watchdog
			
		spi_WrRd_byte(g_cTxData, g_cRxData, sizeof(g_cTxData));		// SPI Send Data
  }
}
