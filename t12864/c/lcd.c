#include <sn8f5804.h>
#include "lcd.h"
/*******************************************************************************************/
// 开机的欢迎界面
code unsigned char gui1_row1[] = "欢迎使用";
code unsigned char gui1_row2[] = "创赢高科";

// 冒号后面的数据为纯ACSII码，由WIFI传输过来更新
code unsigned char gui2_row0[] = "型号";
code unsigned char gui2_row1[] = "订单";
code unsigned char gui2_row2[] = "合格";
code unsigned char gui2_row3[] = "不良";

// 单片机内部记录所有品质不良列表
// 对齐为固定12个字节，然后只需要刷新
code unsigned char *gui3_rows[] = {
                             "            ",
                             "1234跟我开始",
                             "2234现在又有",
                             "3234切克闹啊",
                             "4goo再来一次",
                             "5ort不良情况",
                             "6ier不良情况",
                             "7777不良情况",
                             "8998不良情况",
                             "9889不良情况",
                             "1002不良情况",
};
code unsigned char *error[] = {
                            "无反应      ",
                            "不划线      ",
                            "不烧录      ",
                            "断线        ",
                            "出彩线      ",
                            "信号弱      ",
                            "灯不亮      ",
                            "自划线      ",
                            "不自开机    ",
                            "充电TC不转QC",
                            "充电TC不转PD",
                            "MC不转QC    ",
                            "无静态      ",
                            "不开机      ",
                            "输出TC不转QC",
                            "输出TC不转PD",
                            "DC充电不转伏",
                            "无输出      ",
                            "不充电      ",
                            "充电电流高  ",
                            "MC不转伏    ",
                            "不转伏      ",
                            "屏不良      ",
                            "带载不良    ",
                            "灯长亮      ",
                            "无声音      ",
                            "排针内杂物  ",
                            "USB胶芯融化 ",
                            "自动熄屏    ",
                            "声音小      ",
                            "逆变信号    ",
                            "马达不转    ",
                            "马达自转    ",
                            "D+D-高      ",
                            "AC烧        ",
                            "触摸不良    ",
                            "蓝灯屏      ",
                            "U2QC12V",
                            "空载不良    ",
                            "不关机      ",
};
/*******************************************************************************************/
sfr lcd_out = 0xA0;
sbit vss_pin = P0^2;    // 模块负极
sbit vdd_pin = P0^3;    // 模块正极
sbit v0_pin = P0^4;     // 模块驱动电压输入
// parallel
sbit rs_pin = P0^5;
sbit rw_pin = P0^6;
sbit e_pin = P0^7;
// serial
sbit cs_pin = P0^5;     // 使能脚
sbit sid_pin = P0^6;    // 数据位
sbit clk_pin = P0^7;    // 时钟位
/*******************************************************************************************/
sbit psb_pin = P1^0;    // 高电压并行
sbit ret_pin = P1^1;    // 低电平复位
sbit led_a = P1^3;      // 背光正极
sbit led_k = P1^4;      // 背光负极
/*******************************************************************************************/
struct Lcd lcd;
/*******************************************************************************************/
void delay_us(unsigned char n);
void delay_ms(unsigned char n);
void check_busy(void);
void send_bit(unsigned char dat);
void switch_lcd_mode(unsigned char mode);
void clear_screen(void);
void print_info(unsigned char pos, unsigned char *arr, unsigned char len);
/*******************************************************************************************/
void switch_lcd(unsigned char state){
    unsigned char i = 0;
    if(state == LCD_ON){
        if(lcd.on) return;
        ret_pin = 1;
        vss_pin = 0;
        vdd_pin = 1;
        v0_pin = 1;
        led_a = 1;
        led_k = 0;
        #if (LCD_PSB_MODE == LCD_PARALLEL)
        psb_pin = 1;
        rs_pin = 0;
        rw_pin = 0;
        e_pin = 0;
        #elif (LCD_PSB_MODE == LCD_SERIAL)
        psb_pin = 0;
        cs_pin = 0;
        sid_pin = 0;
        clk_pin = 0;
        #endif
        delay_ms(40); 
        write_byte(CMD_TYPE, 0x30);          // fun_instrct_set      100us   // re = 0; 0x30
        delay_ms(DELAY_NMS);
        write_byte(CMD_TYPE, 0x30);
        delay_ms(DELAY_NMS);
        write_byte(CMD_TYPE, 0x01);          // clear                 10us
        delay_ms(DELAY_NMS);
        write_byte(CMD_TYPE, 0x06);          // move right             10us
        delay_ms(DELAY_NMS);
        write_byte(CMD_TYPE, 0x0c);          // turn on                10us
        delay_ms(DELAY_NMS);
        led_a = 1;
        lcd.on = 1;
        
        // initial display
        write_byte(CMD_TYPE, 0x92);
        i = 0;
        while(i<8){
            write_byte(DATA_TYPE, gui1_row1[i]);
            i++;   
        }
        write_byte(CMD_TYPE, 0x8a);
        i=0;
        while(i<8){
            write_byte(DATA_TYPE, gui1_row2[i]);
            i++;   
        }
        delay_ms(200);
        clear_screen();
        print_info(ROW1_HEAD, gui2_row0, GUI2_HEAD_LEN);
        print_info(ROW2_HEAD, gui2_row1, GUI2_HEAD_LEN);
        print_info(ROW3_HEAD, gui2_row2, GUI2_HEAD_LEN);
        print_info(ROW4_HEAD, gui2_row3, GUI2_HEAD_LEN);
        lcd.updated = 1;
    }else{
        if(lcd.on == 0) return ;
        write_byte(CMD_TYPE, 0x08);         // reset display
        delay_ms(DELAY_NMS);
        write_byte(CMD_TYPE, 0x01);         // clear ac
        delay_ms(DELAY_NMS);
        vdd_pin = 0;                        // turn off power
        v0_pin = 0;
        led_a = 0;
        lcd.on = 0;
        lcd.updated = 0;
    }
}
/*******************************************************************************************/
/*******************************************************************************************/
void display(void){
    unsigned char i = 0;
    if(lcd.updated) return;
    lcd.str = error[lcd.err_ids[lcd.err_index]];          // TODO
    print_info(lcd.pos, lcd.str, BUFFER_LEN);
    lcd.updated = 1;
}
/*******************************************************************************************/
#if (LCD_PSB_MODE == LCD_PARALLEL)
void write_byte(unsigned char type, unsigned char dat){
    if(lcd.stable){
        check_busy();
    }
    rs_pin = type;
    rw_pin = 0;
    lcd_out = dat;
    e_pin = 1;
    delay_us(DELAY_NUS);
    e_pin = 0;
    rs_pin = 0;
    delay_us(DELAY_NUS);
}
void check_busy(void){
    unsigned char res = 0;
    P2M = 0x00;
    do{
        e_pin = 0;
        rs_pin = 0;
        rw_pin = 1;
        delay_us(DELAY_NUS);
        e_pin = 1;
        delay_us(DELAY_NUS);
        res = (lcd_out & 0x80);
    }while(res);
    e_pin = 0;
    P2M = 0xff;
}
/*******************************************************************************************/
#elif (LCD_PSB_MODE == LCD_SERIAL)
/**   fosc 540 khz   
    11111ABC, 
    A=H:LCD => MCU,   A=L: MCU => LCD
    B=H:DISPLAY_DATA, B=L:CONTROL_DATA;
    C = 0;
**/
void write_byte(unsigned char type, unsigned char dat){
    unsigned char head = 0xf8;
    clk_pin = 0;
    cs_pin = 1;
    check_busy();
    if(type){
        head |= 0x02;
    }
    send_bit(head);
    send_bit(dat&0xf0);
    send_bit(dat<<4);
    delay_us(1);
    clk_pin = 0;
    cs_pin = 0;
}

void send_bit(unsigned char dat){
    unsigned char i = 0;
    while(i<8){
        clk_pin = 0;
        sid_pin = (dat & 0x80);
        clk_pin = 1;
        dat <<= 1;
        i++;
    }
}

void check_busy(void){
    unsigned char res = 0;

}
#endif
void clear_screen(void){
    write_byte(CMD_TYPE, 0x01); 
}

void print_info(unsigned char pos, unsigned char *arr, unsigned char len){
    unsigned char i = 0;
    write_byte(CMD_TYPE, pos);
    while(i<len){
        write_byte(DATA_TYPE, *(arr+i));
        i++;
    }
}
/*******************************************************************************************/
void delay_us(unsigned char n){
    while(n--);
}
void delay_ms(unsigned char n){
    unsigned int i = 0;
    while(n--){
        i = DELAY_MS_START;
        while(i--);
    }
}
/**
void switch_lcd_mode(unsigned char mode){
    delay_ms(DELAY_NMS);
    write_byte(CMD_TYPE, mode);
    delay_ms(DELAY_NMS);
    write_byte(CMD_TYPE, mode);
    delay_ms(DELAY_NMS);
}
**/
/**
void init_lcd(void){
    unsigned char i = 0;      // config pin
    ret_pin = 1;
    vss_pin = 0;
    vdd_pin = 1;
    v0_pin = 1;
    led_a = 1;
    led_k = 0;
    #if (LCD_PSB_MODE == LCD_PARALLEL)
    psb_pin = 1;
    rs_pin = 0;
    rw_pin = 0;
    e_pin = 0;
    #elif (LCD_PSB_MODE == LCD_SERIAL)
    psb_pin = 0;
    cs_pin = 0;
    sid_pin = 0;
    clk_pin = 0;
    #endif
    delay_ms(40);                        // power_on              40ms
    write_byte(CMD_TYPE, 0x30);          // fun_instrct_set      100us   // re = 0; 0x30
    delay_ms(DELAY_NMS);
    write_byte(CMD_TYPE, 0x30);
    delay_ms(DELAY_NMS);
    write_byte(CMD_TYPE, 0x0f);          // turn on              100us
    delay_ms(DELAY_NMS);
    write_byte(CMD_TYPE, 0x01);          // clear                 10us
    delay_ms(DELAY_NMS);
    write_byte(CMD_TYPE, 0x06);          // display_control       10us
    delay_ms(DELAY_NMS);

    lcd.on = 1;
}
**/
/**    ST7920
            psb:     1
            ret:     1
          led_a:     1
          led_k:     0
                    rs    rw    db7    db6    db5    db4    db3    db2    db1    db0
          clear:     0     0      0      0      0      0      0      0      0      1
   reset_cursor:     0     0      0      0      0      0      0      0      1      x
   access_point:     0     0      0      0      0      0      0      1     i/d     x
display_control:     0     0      0      0      0      0      1      d      c      b
    cursor_move:     0     0      0      0      0      1     s/c    r/l     x      x
fun_instrct_set:     0     0      0      0      1      1      x     re      x      x
      set_cgram:     0     0      0      1    ac5    ac4    ac3    ac2    ac1    ac0
      set_ddram:     0     0      1    ac6    ac5    ac4    ac3    ac2    ac1    ac0
     check_busy:     0     1     bf    ac6    ac5    ac4    ac3    ac2    ac1    ac0
      write_ram:     1     0    db7    db6    db5    db4    db3    db2    db1    db0
       read_ram:     1     1    db7    db6    db5    db4    db3    db2    db1    db0
**/
