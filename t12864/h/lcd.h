#ifndef __LCD_H
#define __LCD_H

#define  LCD_SERIAL                  0x00
#define  LCD_PARALLEL                0x01

#define  LCD_PSB_MODE                LCD_SERIAL

#define  DELAY_MS_START              0x29b

#define  CMD_TYPE                    0x00
#define  DATA_TYPE                   0x01

#define  LCD_ON                      0x01
#define  LCD_OFF                     0x00


#define  LCD_TEXT_MODE               0x30
#define  LCD_GRAPH_MODE              0x36

#define  DELAY_NMS                   0x03
#define  DELAY_NUS                   0x0a

#define  LCD_LEN                     0x40

#define  STRS_LEN                    0x0c

#define  GUI2_HEAD_LEN               0x05
#define  ROW1_HEAD                   0x80
#define  ROW2_HEAD                   0x90
#define  ROW3_HEAD                   0x88
#define  ROW4_HEAD                   0x98

#define  ROW1_BODY                   0x82
#define  ROW2_BODY                   0x92
#define  ROW3_BODY                   0x8a
#define  ROW4_BODY                   0x9a

#define  BUFFER_LEN                  0x0c
//BUFFER_LEN 不良描述固定占用12个字符

#define  GUI3_ROW_LEN                0x0b

struct Lcd {
    
    unsigned char gui_id;
    
    unsigned char buffer[STRS_LEN];

    
    unsigned char pos;                  // 行定入时的行首定位
    unsigned char *str;                 // 
    unsigned char err_index;            // 当前的错误ID下标
    unsigned char err_len;              // err_ids 的有效长度  
    unsigned char err_ids[BUFFER_LEN];  // http返回的错误ID列表
    unsigned char on:1;
    unsigned char updated:1;
};

void init_lcd(void);

void switch_lcd(unsigned char state);

void write_byte(unsigned char type, unsigned char dat);

void display(void);



#endif