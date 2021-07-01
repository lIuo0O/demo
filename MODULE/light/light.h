#ifndef __LIGHT_H
#define __LIGHT_H

#define          LIGHT_OFF                        0x00
#define          LIGHT_ON                         0x01

#define          SOS_INDEX_LEN                    0x12
#define          SOS_COUNTS_LEN                   0x64
#define          WHITE_MODE_LEN                   0x02

#define          WHITE_OFF_MODE                   0x00
#define          WHITE_ON_MODE                    0x01
#define          WHITE_SOS_MODE                   0x02

#define          RED_OFF_MODE                     0x00
#define          RED_ON_MODE                      0x01


struct Light {
    unsigned char red_mode;
    unsigned char white_mode;
    unsigned char sos_count;
    unsigned char sos_index;
};

void init_light(void);
void set_white_mode(unsigned char mode);
unsigned char get_white_mode(void);
void set_white_pin_state(unsigned char state);
unsigned char get_white_pin_state(void);
void set_white_sos_increase(void);
unsigned char get_white_sos_index(void);
void set_red_mode(unsigned char mode);
unsigned char get_red_mode(void);
void set_red_pin_state(unsigned char state);
unsigned char get_red_pin_state(void);
#endif
