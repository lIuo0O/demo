#ifndef __UART_H
#define __UART_H

#define        P00_UTX               0x01
#define        P01_URX               0xfd
#define        P00_LOGIC_HIGH        0x01
#define        P00_PP                0x00
#define        P01_IN                0x00
#define        UART_115200         0x03f7
#define        CTRL_BY_S0REL         0x80
#define        UART_EN               0x10
#define        UART_IT_EN            0x10

#define        RX_BUFFER_LEN         0x10
#define        TX_BUFFER_LEN         0x10

#define        PARITY_NONE           0x00
#define        PARITY_EVEN           0x01
#define        PARITY_ODD            0x02

#define        PARITY_MODE     PARITY_NONE
#define        RX_START_HEAD_LEN     0x04


struct Uart{
    unsigned char rx_buffer[RX_BUFFER_LEN];
    unsigned char rx_buffer_index;
    unsigned char tx_buffer[TX_BUFFER_LEN];
    unsigned char rx_start_head[RX_START_HEAD_LEN];
    unsigned char rx_start_index;
    unsigned char rx_compare_head[RX_START_HEAD_LEN];
    unsigned char rx_compare_len;
    unsigned char rx_compare_result;
};


#endif
