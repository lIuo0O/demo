#ifndef __HT1621_H
#define __HT1621_H

#define         HT1621_DATA_LEN            0x07

#define         HT1621_SYSTEM_HEAD         0x80
#define         HT1621_DATA_HEAD           0xa0
#define         HT1621_BIAS3_COM4          0x52
#define         HT1621_RC256K              0x30
#define         HT1621_SYSTEM_ON           0x02
#define         HT1621_LCD_ON              0x06
#define         HT1621_WDT_DIS             0x0a
#define         HT1621_TIMER_DIS           0x08
#define         HT1621_LCD_OFF             0x04
#define         HT1621_SYSTEM_OFF          0x00

#define         HT1621_OFF                 0x00
#define         HT1621_ON                  0x01

#define         HT1621_BODY_LEN            0x09
struct Ht1621 {
    unsigned char data_arr[HT1621_BODY_LEN]; // 0-8 char, arr[8.0:3] = headp14, arr[8.4:7] = tailt13;
    unsigned char on:1;
};

void init_ht1621(void);
void set_ht1621_state(unsigned char state);

void set_ht1621_mem(unsigned char index, unsigned char val);
unsigned char get_ht1621_mem(unsigned char index);

void show_ht1621_data(void);
#endif
