#ifndef __BAT_H
#define __BAT_H

/***************************************************************************/
/***************************************************************************/
#define          BAT_LEVEL_LEN                    0x05

#define          BAT_LOW_LIMIT                  0x8888
#define          BAT_MIN_VOL                    0x9990 
#define          BAT_MAX_VOL                    0xeeef 
#define          BAT_HIGH_LIMIT                 0xF2C8          

#define          BAT_BALANCE_VOL                0xe93e

#define          BAT_AUTO_MAX_VOL               0xeaaa
#define          BAT_LEVEL4_VOL                 0xe730
#define          BAT_LEVEL3_VOL                 0xd820
#define          BAT_FULL_LED_VOL               0xE500

#define          LED_WAIT_LEVEL_0                0xdb06
//                                               7.7
#define          LED_WAIT_LEVEL_1                0xe38f
//                                               8.0

#define          BAT_ADD_MAX                      0x10
#define          BAT_SUB_MAX                      0x07

#define          BAT_CHARGE_MODE                  0x01
#define          BAT_DISCHARGE_MODE               0x00


#define          BAT_EMPTY_TRUE                   0x01
#define          BAT_EMPTY_FALSE                  0x00


#define          BAT_LEVEL_4                      0x04
#define          BAT_LEVEL_3                      0x03
#define          BAT_LEVEL_2                      0x02
#define          BAT_LEVEL_1                      0x01
#define          BAT_LEVEL_0                      0x00

#define          BAT_AUTO_INCREASE_CONFIRM       0xC8



/***************************************************************************/
struct Bat{
    unsigned int vol;
    unsigned int max_vol;
    unsigned int auto_increase_count;
    
    unsigned char sub_delta;
    
    unsigned char stable:1;

    unsigned char full:1;
    unsigned char imbalance:1;
    
};
/***************************************************************************/
void init_bat(void);

void set_bat_vol(unsigned int new_vol);
unsigned int get_bat_vol(void);

unsigned char get_bat_level(unsigned char state);

void set_bat_stable(unsigned char stable);
unsigned char get_bat_stable(void);
void update_max_delta(void);
void set_bat_max_vol(unsigned int vol);
void bat_auto_increase(void);
void set_bat_sub_delta(int max_vol);
#endif
