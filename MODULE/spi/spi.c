#include <sn8f5702.h>
#include "spi.h"

code unsigned char color1[] = {};


struct Spi_t spi;

void init_spi(void){
    SPCON |= SPI_EN;
    SPCON = SPI_MASTER_MODE;
    SPCON |= SPI_SPEED;
    
}

unsigned char spi_wirte(unsigned char *arr, unsigned char len){
    if(spi.state != SPI_IDLE_STATE) return 1;
    spi.state = SPI_WRITE_DATA;
    IEN1 |= SPI_IT_EN;

    spi.buf_len = len;
    spi.index = 0;
    memcpy(spi.buf, arr, len);

    while(spi.wait < SPI_WAIT_MAX){
        spi.wait++;
        if(spi.state == SPI_WRITE_DONE){
            return 0;
        }else if(spi.state == SPI_ERR_STATE){
            return 3;
        }
    }
    return 2;
}

void spi_isr(void) interrupt ISPSPi{
    switch(SPSTA){
        case 0x80:
            if(spi.state == SPI_WRITE_DATA){
                if(spi.index < spi.buf_len){
                    SPDAT = spi.buf[spi.index++];
                }else{
                    spi.state = SPI_WRITE_DONE;
                }
            }else{
                spi.state = SPI_ERR_STATE;
            }
            break;
        case 0x40:
            break;
        case 0x20:
            break;
        case 0x10:
            spi.state = SPI_ERR_STATE;
            break;
    }
}
