#ifndef __SPI_H
#define __SPI_H

#define  SPI_SPEED                0x00
#define  SPI_EN                   0x40
#define  SPI_DIS                  0xbf
#define  SPI_MASTER_MODE          0x10
#define  SPI_SLAVE_MODE           0x00

#define  SPI_IT_EN                0x02
#define  SPI_IT_DIS               0xfd

#define  SPI_IDLE_STATE           0x00
#define  SPI_WRITE_DATA           0x01
#define  SPI_WRITE_DONE           0x02
#define  SPI_READ_START           0x03
#define  SPI_READ_DONE            0x04
#define  SPI_ERR_STATE            0x05
#define  SPI_BUF_LEN              0x10

#define  SPI_WAIT_MAX           0x3E8
struct Spi_t{
    unsigned char addr;
    unsigned char buf[];
    unsigned char buf_len;
    unsigned char index;
    unsigned char state;
    unsigned int wait;
};


void init_spi(void);
#endif
