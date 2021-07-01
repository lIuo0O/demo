#ifndef __KEY_H
#define __KEY_H
/***************************************************************************/
/***************************************************************************/
#define          KEY_NULL                     0x00
#define          KEY1_CLICK                   0x10
#define          KEY1_PRESS                   0x90
#define          KEY2_CLICK                   0x08
#define          KEY2_PRESS                   0x88
#define          KEY_DOWN_CONFIRM             0x03
#define          KEY_UP_CONFIRM               0x05
#define          KEY_DOWN_MAX                 0x88
#define          KEY_UP_MAX                   0x88
#define          KEY_PRESS_CONFIRM            0x70

#define          KEY_INVALID_MODE             0x00
#define          KEY_VALID_MODE               0x01
/***************************************************************************/
struct Key{
    unsigned char new_val;
    unsigned char old_val;
    unsigned char act_val;
    
    unsigned char down_count;
    unsigned char up_count;

    unsigned char valid:1;
    unsigned char press_en:1;
};
/***************************************************************************/
void init_key(void);
void scan_key(void);
unsigned char get_key_pin_state(void);
unsigned char get_act_key(void);
void free_key(void);
void set_key_mode(unsigned char mode);
#endif
