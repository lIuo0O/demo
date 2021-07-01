#include <sn8f5708.h>
#include "ht1621.h"

sbit cs_pin = P3^0;
sbit rd_pin = P3^1;
sbit wr_pin = P3^2;
sbit data_pin = P3^3;
sbit ledw_pin = P3^5;
sbit ledr_pin = P3^6;

struct Ht1621 ht1621;

void send_bits(unsigned char dat, unsigned char len);
void write_cmd(unsigned char cmd);
/*********************************************************************/
void init_ht1621(void){

}
void set_ht1621_state(unsigned char state){
    unsigned char i = 0;
    if(state){
        if(ht1621.on) return;
        cs_pin = 1;
        wr_pin = 1;
        data_pin = 1;
        write_cmd(HT1621_BIAS3_COM4);
        write_cmd(HT1621_RC256K);
        write_cmd(HT1621_SYSTEM_ON);
        while(i++<200);
        write_cmd(HT1621_LCD_ON);
        write_cmd(HT1621_WDT_DIS);
        write_cmd(HT1621_TIMER_DIS);
        ledr_pin = 1;
        ledw_pin = 1;
        ht1621.on = 1;
    }else{
        if(ht1621.on == 0) return;
        cs_pin = 0;
        send_bits(HT1621_DATA_HEAD, 3);
        send_bits(0x00, 6);                       // start address at 0x00;
        while(i++ < HT1621_BODY_LEN + 1){
            send_bits(0x00, 8);
        }
        cs_pin = 1;
        write_cmd(HT1621_LCD_OFF);
        write_cmd(HT1621_SYSTEM_OFF);
        ledr_pin = 0;
        ledw_pin = 0;
        ht1621.on = 0;
    }
}

void show_ht1621_data(void){
    unsigned char temp = 0;
    unsigned char i = 0;
    temp = ht1621.data_arr[8];
    cs_pin = 0;
    send_bits(HT1621_DATA_HEAD, 3);
    send_bits(0x00, 6);
    send_bits(temp, 4);
    cs_pin = 1;
    i = 0;
    cs_pin = 0;
    send_bits(HT1621_DATA_HEAD, 3);
    send_bits(0x04, 6);
    while(i < HT1621_DATA_LEN){
        send_bits(ht1621.data_arr[i], 8);
        i++;
    }
    cs_pin = 1;
    temp = 0;
    cs_pin = 0;
    send_bits(HT1621_DATA_HEAD, 3);
    send_bits(0x44, 6);
    temp = (ht1621.data_arr[8] & 0x0f) << 4;
    send_bits(temp, 4);
    cs_pin = 1;
}

void set_ht1621_mem(unsigned char index, unsigned char val){
    ht1621.data_arr[index] = val;
}
unsigned char get_ht1621_mem(unsigned char index){
    return ht1621.data_arr[index];
}
/*********************************************************************/
/*************************** private *********************************/
void send_bits(unsigned char dat, unsigned char len){
    unsigned char i = 0;
    unsigned char j = 0;
    while(i++<len){
        data_pin = dat & 0x80;
        wr_pin = 0;
        j = 0;
        while(j++<4);
        wr_pin = 1;
        dat <<= 1;
    }
}
void write_cmd(unsigned char cmd){
    unsigned char i = 0;
    cs_pin = 1;
    wr_pin = 1;
    data_pin = 1;
    while(i++<3);
    cs_pin = 0;
    cs_pin = 0;
    wr_pin = 0;
    wr_pin = 0;
    cs_pin = 0;
    send_bits(HT1621_SYSTEM_HEAD, 4);
    send_bits(cmd, 8);
    cs_pin = 1;
}