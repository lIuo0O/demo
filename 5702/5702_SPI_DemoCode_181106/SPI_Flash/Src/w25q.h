#ifndef __W25Q_H_
#define __W25Q_H_
//----------------------------------------------------------------------------------------------//
#include "sn8f5702.h"
//----------------------------------------------------------------------------------------------//
//÷∏¡Ó±Ì
#define W25Q_WRITE_ENABLE			0x06 
#define W25Q_WRITE_DISABLE		0x04 
#define W25Q_READ_STATUS1 		0x05
#define W25Q_READ_STATUS2 		0x35
#define W25Q_READ_DATA				0x03 
#define W25Q_SECTOR_ERASE			0x20 
#define W25Q_PAGE_PROGRAM			0x02
//----------------------------------------------------------------------------------------------//
bit w25q_busy(void);        
void w25q_read_id (void);
void w25q_erase_sector(uint16_t iAddr);
void w25q_write_256bytes(uint32_t lWriteAddr,uint8_t* p_cBuffer,uint16_t iNumByteToWrite); 
void w25q_read_data(uint32_t lReadAddr,uint8_t* p_cBuffer,uint16_t iNumByteToRead);  
//----------------------------------------------------------------------------------------------//
#endif 



