#include <sn8f5702.h>
#include "light.h"
/***************************************************************************/
sbit red_pin = P0^7;
sbit white_pin = P1^7;
/***************************************************************************/
code unsigned char SOS_COUNTS[SOS_INDEX_LEN] = { 3, 6, 9, 12, 15, 25, 34, 37, 46, 49, 58, 68, 71, 74, 77, 80, 83, 98 };
struct Light light;
/***************************************************************************/
void init_light(void){
    red_pin = 1;
    white_pin = 1;
    light.red_mode = 0;
    light.white_mode = 0;
    light.sos_count = 0;
    light.sos_index = 0;
}
/*********************************************************************************/
/*                         °×µÆ                                                 */
/*********************************************************************************/
void set_white_mode(unsigned char mode){                   // mode
    if(mode > WHITE_MODE_LEN){
        mode = 0;
    }
    if(mode == WHITE_ON_MODE){
        light.white_mode = WHITE_ON_MODE;
        light.sos_count = 0;
        light.sos_index = 0;
        white_pin = 0;
    }else if(mode == WHITE_SOS_MODE){
        light.white_mode = WHITE_SOS_MODE;
    }else{
        light.white_mode = WHITE_OFF_MODE;
    }
}
unsigned char get_white_mode(void){
    return light.white_mode;
}
/***************************************************/
void set_white_pin_state(unsigned char state){              // state
    if(state == LIGHT_ON){
        white_pin = 0;
    }else{
        white_pin = 1;
    }
}

unsigned char get_white_pin_state(void){
    return white_pin == 0;
}
/***************************************************/
void set_white_sos_increase(void){                                    // sos
    light.sos_count++;
    light.sos_count %= SOS_COUNTS_LEN;
    if(light.sos_count > SOS_COUNTS[light.sos_index]){
        light.sos_index++;
        light.sos_index %= SOS_INDEX_LEN;
    }
}

unsigned char get_white_sos_index(void){
    return light.sos_index;
}
/*********************************************************************************/
/*                         ºìµÆ                                                 */
/*********************************************************************************/
void set_red_mode(unsigned char mode){                // mode
    if(mode ==  RED_ON_MODE){
        light.red_mode = RED_ON_MODE;
    }else{
        light.red_mode = RED_OFF_MODE;
    }
}

unsigned char get_red_mode(void){
    return light.red_mode;
}
/***************************************************/
void set_red_pin_state(unsigned char state){             // state
    if(state == LIGHT_ON){
        red_pin = 0;
    }else{
        red_pin = 1;
    }
}
unsigned char get_red_pin_state(void){
    return red_pin == 0;
}

