#ifndef __MSPI_H_
#define __MSPI_H_
//----------------------------------------------------------------------------//
#include "sn8f5702.h"
//----------------------------------------------------------------------------//
#define O_IO_CS					P07     	// 片选口
#define MAX_TX_LEN			8					// Maximum Tx Data Length
#define MAX_RX_LEN			8					// Maximum Rx Data Length
#define WAIT_TIME				1000			// 最大死等时长 
//----------------------------------------------------------------------------//
extern uint8_t g_cTxData[MAX_TX_LEN];
extern uint8_t g_cRxData[MAX_RX_LEN];
//----------------------------------------------------------------------------//
void spi_master_init (void);
void spi_send_data (uint8_t cByte);
uint8_t spi_read_data (void);
void spi_WrRd_byte (uint8_t * p_cSrc, uint8_t * p_cDst, uint8_t cLenth);
//----------------------------------------------------------------------------//
#endif