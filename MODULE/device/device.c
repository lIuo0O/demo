#include <sn8f5702.h>
#include "device.h"

struct Device device;

void init_device(void){
    CKCON  = 0x70;
    CLKSEL = 0x05;
    CLKCMD = 0x69;
    CKCON  = 0x10;
    
    device.mode = DEVICE_RUN_MODE;
}
/***************************************************************************/
void start_device(void){
    P0UR = 0x18;
    P0M  = 0xe3;
    P0   = 0x98;
    P1UR = 0x00;
    P1M  = 0xba;
    P1   = 0x80;
    P2UR = 0x03;
    P2M  = 0x00;
    P2   = 0x03;
    IEN0 |= 0x80;
    device.mode = DEVICE_RUN_MODE;
}
/***************************************************************************/
void stop_device(void){
    P0UR = 0x18;
    P0M  = 0xe3;
    P0   = 0x98;
    P1UR = 0x00;
    P1M  = 0xff;
    P1   = 0x80;
    P2UR = 0x00;
    P2M  = 0x03;
    P2   = 0x00;
    P1CON = 0x00;
}

void set_device_mode(unsigned char mode){
    if(mode > DEVICE_MODE_LEN){
        mode = 0;
    }
    device.mode = mode;
}

unsigned char get_device_mode(void){
    return device.mode;
}
