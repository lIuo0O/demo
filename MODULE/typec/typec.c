#include <sn8f5702.h>
#include "typec.h"

sbit insert_pin = P0^2;

unsigned char get_typec_insert_state(void){
    unsigned char i = 0;
    unsigned char in_count = 0;
    while(i < CHECK_TYPEC_INSERT_MAX){
        if(insert_pin){
            in_count++;
        }
        i++;
    }
    return (in_count > TYPEC_INSERT_CONFIRM);
}
