#include <sn8f5804.h>
#include "uart.h"
//username=manager&password=75952

/************************************************************************************/
unsigned char check_parity(unsigned char val){
    unsigned char i = 0;
    unsigned char tmp = val;
    unsigned char parity = 0;
    while(i++<BYTE_LEN){
        parity += (tmp&0x01);
        tmp >>= 1;
    }
    return (parity & 0x01);
}
/************************************************************************************/
/**
 * baurd_rate = 115200;
 * SMOD = 1; // PCON |= 0x80; // uart_rate select fcpu/32
 * S0RELH = 0x03;S0RELL = 0xf7;//S0REL = 0x03f7;
 * S0CON |= 0x10; //enable uart
 * S0CON2 = 0x80; // controlled by S0REL
 * IEN0 |= 0x10;  // enable uart_it
 * 
 * +UART_CUR:<baudrate>,<databits>,<stopbits>,<parity>,<flow    control>
 */
void init_uart(void){
    P0M |= P00_UTX;
    P0M &= P01_URX;
    P0 |= P00_LOGIC_HIGH;
    P0OC &= P00_PP;
    P0OC &= P01_IN;
    S0REL = UART_115200;
    S0CON2 = CTRL_BY_S0REL; // 
    S0CON =  UART_MODE3;
    IEN0 |= UART_IT_EN;
}

unsigned char write_str(unsigned char *str, unsigned char len){
    unsigned char wait = 0;
    unsigned char i = 0;
    unsigned char val = *str;
    while(i < len){
        val = *(str + i);
#if PARITY_MODE
        TB80 = check_parity(val);
#endif
        S0BUF = val;
        while(!TI0){
            if(wait++> TX_WAIT_MAX) return i+1;
        }
        TI0 = 0;
        i++;
    }
    return 0;
}

void read_str(unsigned char len){
    S0CON |= UART_RX_EN;
    uart.rx_index = 0;
    uart.rx_start_index = 0;
    uart.rx_compare_result = 0;
    while(uart.rx_index < len);
    S0CON &= UART_RX_DIS;
}


void uart_irq(void) interrupt ISRUart{
    unsigned char i = 0;
    if(RI0){
        while(i < uart.compare_len){
            if(uart.rx_start_head[(uart.rx_start_index + i)%RX_START_HEAD_LEN] != uart.compare_head[i]){
                uart.rx_compare_result = 1;
                break;
            }
            i++;
        }
        if(uart.rx_compare_result){
             if(uart.rx_start_len < RX_START_HEAD_LEN){
                 uart.rx_start_head[uart.rx_start_len++] = S0BUF;
             }else{
                 uart.rx_start_head[uart.rx_start_index++] = SOBUF;
                 if(uart.rx_start_index >= RX_START_HEAD_LEN){
                     uart.rx_start_index = 0;
                 }
            }
        }else{
            uart.rx_buffer[uart.rx_buffer_index++] = S0BUF;
        }
        RI0 = 0;
    }
}



