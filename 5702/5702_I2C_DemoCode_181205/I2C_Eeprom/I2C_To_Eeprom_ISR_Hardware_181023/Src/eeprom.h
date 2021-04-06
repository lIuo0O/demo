#ifndef _EEPROM_H_
#define _EEPROM_H_

#include "sn8f5702.h"
#include "i2c_master.h"

/**************************************************************
01  -> 24C01;   02  -> 24C02;  04   -> 24C04;   08  -> 24C08;
16  -> 24C16;   32  -> 24C32;  64   -> 24C64;   128 -> 24C128;
256 -> 24C256;  512 -> 24C512; 1024 -> 24C1024; 
***************************************************************/
#define EEPROM 								2										// device type
#define EEPROM_ADDR						0xA0								// device address
//------------------------------------------------------------------------------------------------------------//
#define EEPROM_WRITE          0x00                // Write
#define EEPROM_READ           0x01                // Rea
//------------------------------------------------------------------------------------------------------------//
#if EEPROM == 1
   #define PAGE_SIZE           8									// Page Size
   #define EEPROM_WORD_ADDR_SIZE   8							// Data Address Size
#elif EEPROM == 2
   #define PAGE_SIZE           8 									// Page Size
   #define EEPROM_WORD_ADDR_SIZE   8							// Data Address Size 
#elif EEPROM == 4
   #define PAGE_SIZE           16									// Page Size
   #define EEPROM_WORD_ADDR_SIZE   8							// Data Address Size 
#elif EEPROM == 8
   #define PAGE_SIZE           16									// Page Size
   #define EEPROM_WORD_ADDR_SIZE   8							// Data Address Size 
#elif EEPROM == 16
   #define PAGE_SIZE           16									// Page Size
   #define EEPROM_WORD_ADDR_SIZE   8							// Data Address Size 
#elif EEPROM == 32
   #define PAGE_SIZE           32									// Page Size
   #define EEPROM_WORD_ADDR_SIZE   16							// Data Address Size 
#elif EEPROM == 64
   #define PAGE_SIZE           32									// Page Size
   #define EEPROM_WORD_ADDR_SIZE   16							// Data Address Size 
#elif EEPROM == 128
   #define PAGE_SIZE           64									// Page Size
   #define EEPROM_WORD_ADDR_SIZE   16							// Data Address Size 
#elif EEPROM == 256
   #define PAGE_SIZE           64									// Page Size
   #define EEPROM_WORD_ADDR_SIZE   16							// Data Address Size 
#elif EEPROM == 512
   #define PAGE_SIZE           128								// Page Size
   #define EEPROM_WORD_ADDR_SIZE   16							// Data Address Size 
#elif EEPROM == 1024
   #define PAGE_SIZE           256								// Page Size
   #define EEPROM_WORD_ADDR_SIZE   16							// Data Address Size 
#endif 
//------------------------------------------------------------------------------------------------------------//
void delay_ms (uint8_t cTemp);
/*************************************************************************************************
												Eeprom Write
**************************************************************************************************/
void eeprom_write_page(uint8_t cDevAddr,uint16_t cWrDataAddr, uint8_t * p_cWrDataBuf, uint8_t cNumByteToWrite);
void eeprom_write_n_byte(uint8_t cDevAddr,uint16_t cWrDataAddr, uint8_t * p_cWrData, uint8_t cNumByteToWrite);
/**************************************************************************************************
												Eeprom Read
***************************************************************************************************/
void eeprom_read_n_byte(uint8_t cDevAddr,uint16_t cRdDataAddr, uint8_t * p_cRdData, uint8_t cNumByteToRead);
//------------------------------------------------------------------------------------------------------------//
#endif