#include "sn8f5702.h"
#include "mspi.h"
#include "w25q.h"
/**********************************************************************************/
#define DATA_ADDR		0																	//for test
uint8_t g_cTxData [8] = {1, 2, 3, 4, 5, 6, 7, 8};			//for test
uint8_t g_cRxBuf [8];																	//for test
/*************************************************************************************************************
Function: SPI Master DemoCode
*************************************************************************************************************/
int Main(void)
{
  CLKSEL = 0x07;								// Fcpu = 32M / 1 = 32M
  CLKCMD = 0x69;
  CKCON = 0x30;								  // IROM run at 8 MHz

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
    WDTR = 0x5A; 						  // clear watchdog

//		w25q_read_id();						// Read W25Q ID
		
		w25q_write_256bytes(DATA_ADDR,g_cTxData, sizeof(g_cTxData)); // Write Data
		
		w25q_read_data(DATA_ADDR,g_cRxBuf,sizeof(g_cRxBuf));				 // Read Data
  }
}
