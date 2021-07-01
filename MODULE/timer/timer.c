#include <sn8f5702.h>
#include "timer.h"
#include "ctrl.h"
#include "except.h"


struct Timer timer;
extern struct Ctrl ctrl;
extern struct Except except;

void start_timer0(void){
    if(timer.t0_on) return;
    TH0 = TIMER0_H;
    TL0 = TIMER0_L;
    TMOD |= TIMER0_MODE1;
    TCON |= TIMER0_RUN;
    IEN0 |= TIMER0_IT_EN;
    timer.t0_on = 1;
}
/***************************************************************************/
void stop_timer0(void){
    if(timer.t0_on==0) return;
    IEN0 &= TIMER0_IT_DIS;
    TCON &= TIMER0_STOP;
    timer.t0_on = 0;
}
/***************************************************************************/


void timer_irq(void) interrupt ISRTimer0{       // key 10ms    0.0015ms * 6667 = 10ms
    TH0 = TIMER0_H;
    TL0 = TIMER0_L;
    /**************************************************************************/
    ctrl.adc_tick = 1;       // TODO 30ms
    ctrl.average_vol_tick = 1;
    ctrl.average_ntc1_tick = 1;
    ctrl.average_ntc2_tick = 1;
    /**************************************************************************/
    
    except.adc_tick = 1;
    except.bat_tick = 1;
    except.ntc1_tick = 1;
    except.ntc2_tick = 1;
    except.charge_tick = 1;
    except.discharge_tick = 1;
    except.moto_tick = 1;
    
    if(ctrl.charge_count++ > ctrl.charge_tick_max){
        ctrl.charge_count = 0;
        ctrl.bat_charge_tick = 1;
    }
    if(ctrl.discharge_count++ > ctrl.discharge_tick_max){
        ctrl.discharge_count = 0;
        ctrl.bat_discharge_tick = 1;
    }    
    /**************************************************************************/
    ctrl.key_tick = 1;
    /**************************************************************************/
    ctrl.moto_tick = 1;
    /**************************************************************************/
    /**************************************************************************/
    if(timer.t0_50ms_count++ > TIMER0_50MS_CONFIRM){
        timer.t0_50ms_count = 0;
        ctrl.red_light_tick = 1;
        ctrl.white_light_tick = 1;
    }
    /**************************************************************************/
    if(timer.t0_300ms_count++ > TIMER0_300MS_CONFIRM){
        timer.t0_300ms_count = 0;
        ctrl.charge_full_tick = 1;
        ctrl.led_tick = 1;
    }
    
}
