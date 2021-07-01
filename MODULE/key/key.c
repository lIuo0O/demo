#include <sn8f5702.h>
#include "key.h"

struct Key key;
/*********************************************************************************/
void init_key(void){
    key.down_count = 0;
    key.up_count = 0;
    key.new_val = KEY_NULL;
    key.old_val = KEY_NULL;
    key.act_val = KEY_NULL;
    key.press_en = 1;
    key.valid = 1;
}

void scan_key(void){
    if(key.valid==0){
        key.old_val = KEY_NULL;
        key.new_val = KEY_NULL;
        key.act_val = KEY_NULL;
        return;
    }
    key.new_val = ~(P0 | 0xe7);
    if(key.new_val == KEY_NULL){
        if(key.up_count < KEY_UP_MAX){
            key.up_count++;
        }
        if(key.up_count > KEY_UP_CONFIRM){
            if(key.down_count > KEY_DOWN_CONFIRM && key.down_count < KEY_PRESS_CONFIRM){
                key.act_val = key.old_val;
            }
            key.press_en = 1;
            key.down_count = 0;
        }
    }else{
        if(key.old_val == key.new_val){
            if(key.down_count < KEY_DOWN_MAX){
                key.down_count++;
            }
            if(key.down_count > KEY_PRESS_CONFIRM && key.press_en){
                if(key.new_val == KEY1_CLICK){
                    key.act_val = KEY1_PRESS;
                }else if(key.new_val == KEY2_CLICK){
                    key.act_val = KEY2_PRESS;
                }
                key.press_en = 0;
            }
            key.up_count = 0;
        }else{
            key.down_count = 0;
            key.old_val = key.new_val;
        }
    }    
}
/*********************************************************************************/
unsigned char get_key_pin_state(void){
    return ~(P0 | 0xe7);
}

unsigned char get_act_key(void){
    return key.act_val;
}

void free_key(void){
    key.act_val = KEY_NULL;
}

void set_key_mode(unsigned char mode){
    if(mode == KEY_VALID_MODE){
        key.valid = 1;
    }else{
        key.valid = 0;
        key.act_val = KEY_NULL;
    }
}
