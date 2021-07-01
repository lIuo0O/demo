#include <sn8f5702.h>
#include "moto.h"

sbit pwm_pin = P0^6;

struct Moto moto;
/*********************************************************************************/
void init_moto(void){
    PW1Y = PW1MY_MAX;
    PW1D = 0x0000;
    PW1B = 0x0000;
    PW1A = 0x0000;
    PW1M = PW1M_RATE;
    moto.max_pwm = 0;
    moto.new_pwm = 0;
    moto.delta_pwm = 0;
    moto.level = 0;
    moto.first_acc = 1;
}

void set_moto_level(unsigned char level){
    level %= 2;
    moto.level = level;
}

void set_moto_state(void){
    if(moto.level){
        if(moto.on) return;
        moto.new_pwm = PWM_START_VAL;
        PW1D = moto.new_pwm;
        PW1B = moto.new_pwm;
        moto.delta_pwm = MOTO_ACC1;
        PW1CH |= P06_PWM_MODE;
        IEN4 |= PW1M_IT_EN;
        PW1M |= PW1M_EN;
        moto.on = 1;   
    }else{
        if(moto.on == 0) return;
        stop_moto();
        return;
    }    
}

unsigned char get_moto_level(void){
    return moto.level;
}

void stop_moto(void){
    IEN0 &= 0x7f;
    IEN4 &= PW1M_IT_DIS;
    PW1M &= PW1M_DIS;
    PW1CH &= P06_GPIO_MODE;
    pwm_pin = 0;
    IEN0 |= 0x80;
    moto.on = 0;
    moto.max_pwm = 0;
    moto.new_pwm = 0;
    moto.delta_pwm = 0;
    moto.level = 0;
    moto.first_acc = 1;
}
/*********************************************************************************/
void pwm_irq(void) interrupt ISRPwm1{            // moto
    if((IEN4 & 0x08) == 0x08){
        IEN4 &= 0xf7;
        if(moto.new_pwm < PWM_MAX_SPEED){
            moto.new_pwm += moto.delta_pwm;
            IEN4 &= PW1M_IT_DIS;
            PW1D = moto.new_pwm;
            PW1B = moto.new_pwm;
            IEN4 |= PW1M_IT_EN;
        }
    }
}


