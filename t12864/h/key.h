#ifndef __KEY_H
#define __KEY_H

#define   KEY_NULL                   0x00
#define   KEY1_CLICK                 0x01
#define   KEY2_CLICK                 0x02
#define   KEY3_CLICK                 0x04
#define   KEY4_CLICK                 0x08

#define   KEY_DOWN_CONFIRM           0x06
#define   KEY_DOWN_MAX               0x10
#define   KEY_UP_CONFIRM             0x08
#define   KEY_UP_MAX                 0x10

struct Key {
    unsigned char up_count;
    unsigned char down_count;
    unsigned char union_val;
    unsigned char down_val;
    unsigned char new_val;
    
    unsigned char gui_id;
    unsigned char product_id;
    unsigned char select_id;
    
    unsigned char scan_tick:1;
    unsigned char handler_tick:1;
};

void scan_key(void);
void handle_key(void);
#endif
/**


**/