#include "w25q.h"
#include "mspi.h"
/****************************************************************************************
Function:	 	W25Q Read Register
input:			None
Output: 		None
Return:  		None
****************************************************************************************/
bit w25q_busy(void)
{
  uint8_t cTemp;
								
	O_IO_CS = 0;																// Enable Slave

	spi_WtRd_Byte(W25Q_READ_STATUS1);						// Read Status Register Instruction
	
	cTemp = spi_WtRd_Byte(0xFF);								// Read Status  
	
	O_IO_CS = 1;																// Disable Slave
	
	return (cTemp & 0x01) ;
}
/****************************************************************************************
Function:	 	W25Q Read Register
input:			None
Output: 		None
Return:  		None
****************************************************************************************/
void w25q_write_enable(void)   
{
	O_IO_CS = 0;																// Enable Slave
	
  spi_WtRd_Byte(W25Q_WRITE_ENABLE); 					// Send Write Enable Instruction       
	
	O_IO_CS = 1;														 		// Disable Slave	      
} 
/****************************************************************************************
Function:	 	W25Q Read Register
input:			None
Output: 		None
Return:  		None
****************************************************************************************/
void w25q_write_disable(void)   
{  
	O_IO_CS = 0;																// Enable Slave
	
  spi_WtRd_Byte(W25Q_WRITE_DISABLE); 			 		// Send Write Disable Instruction         
	
	O_IO_CS = 1;									 							// Disable Slave      
} 	
/****************************************************************************************
Function:	 	W25Q Erase Sector
input:			None
Output: 		None
Return:  		None
****************************************************************************************/
void w25q_erase_sector(uint16_t iAddr)
{
	while(w25q_busy());														// Wait Bus Idle		
	
  w25q_write_enable(); 													// Send Write Enable Instruction  
	
  O_IO_CS = 0;																	// Enable Slave
	
  spi_WtRd_Byte(W25Q_SECTOR_ERASE);      				// Send Erase Sector Enable Instruction 
	
  spi_WtRd_Byte((uint8_t) ((iAddr) >> 16));  		// Send Address
  spi_WtRd_Byte((uint8_t) ((iAddr) >> 8));
  spi_WtRd_Byte((uint8_t) iAddr);
	
  O_IO_CS = 1;														 			// Disable Slave
}
/****************************************************************************************
Function:	 	W25Q Read Data
input:			None
Output: 		None
Return:  		None
****************************************************************************************/
void w25q_read_data(uint32_t lReadAddr, uint8_t * p_cBuffer, uint16_t iNumByteToRead)
{			
	while(w25q_busy());														// Wait Bus Idle	
	
	O_IO_CS = 0;																	// Enable Slave
		
  spi_WtRd_Byte(W25Q_READ_DATA);         	   		// Send Read Instruction
	
  spi_WtRd_Byte((uint8_t) (lReadAddr >> 16));		// Send Read Address (8 Bytes)
  spi_WtRd_Byte((uint8_t) (lReadAddr >> 8));
  spi_WtRd_Byte((uint8_t) lReadAddr);

  while(iNumByteToRead--)
	{
    *p_cBuffer++ = spi_WtRd_Byte(0xFF);		 			// Read Data
  }
	
	O_IO_CS = 1;														 			// Disable Slave
}
/****************************************************************************************
Function:	 	W25Q Write byte
input:			None
Output: 		None
Return:  		None
****************************************************************************************/
void w25q_write_256bytes(uint32_t lWriteAddr, uint8_t * p_cBuffer, uint16_t iNumByteToWrite)
{
	uint16_t iSectAdr;
	
	iSectAdr = lWriteAddr / 4096; 									// 128(block) * 16(sector) = 2048(sector)  4KB(Each sector) = 4 * 1024 = 4096 (Byte)
	w25q_erase_sector(iSectAdr);										// Erase Sector
	
	while(w25q_busy());  														// Wait Bus Idle		
	
  w25q_write_enable(); 														// Send Write Enable Instruction

	O_IO_CS = 0;																		// Enable Slave
	
  spi_WtRd_Byte(W25Q_PAGE_PROGRAM);      					// Send Page Program Instruction
	
  spi_WtRd_Byte((uint8_t) ((lWriteAddr) >> 16)); 	// Send Write Address (8 Bytes)
  spi_WtRd_Byte((uint8_t) ((lWriteAddr) >> 8));
  spi_WtRd_Byte((uint8_t) lWriteAddr);

	while(iNumByteToWrite--)
	{
		spi_WtRd_Byte(*p_cBuffer++); 									// Send Data
	}
	
	while(w25q_busy());   													// Wait Bus Idle	
	
	O_IO_CS = 1;																		// Disable Slave
	
	w25q_write_disable(); 			 										// Send Write Disable  
}
/****************************************************************************************
Function:	 	Read W25Q ID 
input:			None
Output: 		None
Return:  		None
****************************************************************************************/
//0XEF13,��ʾоƬ�ͺ�ΪW25Q80
//0XEF14,��ʾоƬ�ͺ�ΪW25Q16
//0XEF15,��ʾоƬ�ͺ�ΪW25Q32
//0XEF16,��ʾоƬ�ͺ�ΪW25Q64
//0XEF17,��ʾоƬ�ͺ�ΪW25Q128
void w25q_read_id (void)
{
  static uint16_t g_iId;
	
	while(w25q_busy());  														// Wait Bus Idle	
	
  O_IO_CS = 0;																		// Enable Slave
	
  spi_WtRd_Byte(0x90);								
  spi_WtRd_Byte(0x00);
  spi_WtRd_Byte(0x00);
  spi_WtRd_Byte(0x00);														// Send Read Device ID Instruction
	
	g_iId = 0;
  g_iId |= spi_WtRd_Byte(0xFF) << 8;							// Read ID
  g_iId |= spi_WtRd_Byte(0xFF);
	
  O_IO_CS = 1;																		// Disable Slave
}