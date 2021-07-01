#include <sn8f5702.h>
#include "bat.h"

code unsigned int BAT_DISCHARGE_VOLS[BAT_LEVEL_LEN]    = {0x9990, 0xaaa0, 0xc160, 0xd820, 0xf1c0};
code unsigned int BAT_CHARGE_VOLS[BAT_LEVEL_LEN] = {0x9990, 0xc160, 0xd820, 0xe930, 0xf1c0};

struct Bat bat;

void init_bat(void){
    bat.vol = 0x9980;
    bat.stable = 0;
    bat.sub_delta = 0;
}

void set_bat_vol(unsigned int new_vol){
    unsigned int tmp = 0;
    if(new_vol < BAT_LOW_LIMIT) return;
    if(new_vol > BAT_HIGH_LIMIT) return;
    if(bat.stable == 0){
        bat.vol = new_vol;
        return;
    }
    if(bat.vol < new_vol){
        tmp = new_vol - bat.vol;
        if(tmp > BAT_ADD_MAX){
            tmp = BAT_ADD_MAX;
        }
        if(bat.vol < BAT_MAX_VOL){
            bat.vol += tmp;
        }
    }else{
        tmp = bat.vol - new_vol;
        if(tmp > BAT_SUB_MAX){
            tmp = BAT_SUB_MAX;
        }
        if(bat.vol > BAT_MIN_VOL){
            bat.vol -= (tmp + bat.sub_delta);
        }
    }
}

void bat_auto_increase(void){
    if(bat.auto_increase_count++ > BAT_AUTO_INCREASE_CONFIRM){
        bat.auto_increase_count = 0;
        if(bat.vol < BAT_AUTO_MAX_VOL){
            set_bat_stable(0);
            set_bat_vol(BAT_AUTO_MAX_VOL);
            set_bat_stable(1);
        }
    }
}

unsigned int get_bat_vol(void){
    return bat.vol;
}

unsigned char get_bat_level(unsigned char state){
    unsigned char i = 0;
    unsigned int *check = 0;
    if(state){
        check = &(BAT_CHARGE_VOLS[0]);
    }else{
        check = &(BAT_DISCHARGE_VOLS[0]);
    }
    while(i < BAT_LEVEL_LEN){
        if(bat.vol < *(check+i)){
            return i;
        }
        i++;
    }
    return BAT_LEVEL_LEN - 1;
}

void set_bat_stable(unsigned char stable){
    bat.stable = (stable == 1);
}
unsigned char get_bat_stable(void){
    return bat.stable;
}
void set_bat_sub_delta(int max_vol){
    if(max_vol > BAT_BALANCE_VOL){
        bat.sub_delta = 0;
    }else{
        bat.sub_delta = (BAT_MAX_VOL - max_vol) / 2800;
    }
}
