#include <sn8f5804.h>
#include "key.h"
#include "lcd.h"
/*******************************************************************************************/
struct Key key;
extern struct Lcd lcd;
/*******************************************************************************************/
void scan_key(void){
    if(key.scan_tick == 0) return;
    key.scan_tick = 0;
    key.union_val = ~(P2 | 0xf0);
    if(key.union_val == KEY_NULL){
        if(key.up_count < KEY_UP_MAX){
            key.up_count++;
        }
        if( key.up_count > KEY_UP_CONFIRM ){
            if(key.down_count > KEY_DOWN_CONFIRM){
                key.new_val = key.down_val;
            }
            key.down_count = 0;
        }
    }else{
        if(key.union_val == key.down_val){
            if(key.down_count < KEY_DOWN_MAX){
                key.down_count++;
            }
        }else{
            key.down_count = 0;
            key.down_val = key.union_val;
        }
    }
}


void handle_key(void){
    if(key.handler_tick == 0) return;
    key.handler_tick = 0;
    if(key.new_val == KEY_NULL) return;
    switch(key.new_val){
        case KEY1_CLICK:
            lcd.pos = ROW4_BODY;
            if(lcd.err_index < lcd.err_len - 1){
                lcd.err_index++;
            }else{
                lcd.err_index = 0;
            }
            lcd.updated = 0;
            break;
        case KEY2_CLICK:
            lcd.pos = ROW4_BODY;
            if(lcd.err_index > 0){
                lcd.err_index--;
            }else{
                lcd.err_index = lcd.err_len - 1;
            }
            lcd.updated = 0;
            break;
        case KEY3_CLICK:
            
            break;
        case KEY4_CLICK:
            // set json:id=id&ok=ok&ng=ng
            break;
        default:
            break;
    }
    key.new_val = KEY_NULL;
}