#include <sn8f5702.h>
#include "led.h"
/***************************************************************************/
sfr led_out_pin = 0x90;
code unsigned char LED_ON_ARR[LED_ARR_LEN] = {0x00, 0x08, 0x18, 0x38};
/***************************************************************************/
struct Led led;
/***************************************************************************/
void init_led(void){
    led.level = LED_ON0;
    led.mode = LED_OFF_MODE;
}

void set_led_level(unsigned char level){
    level %= LED_ARR_LEN;
    led.level = level;
    led_out_pin &= CLEAR_LED;
    led_out_pin |= LED_ON_ARR[led.level];
}
void set_led_mode(unsigned char mode){
    led.mode = mode;
}

unsigned char get_led_mode(void){
    return led.mode;
}
unsigned char get_led_level(void){
    return led.level;
}


