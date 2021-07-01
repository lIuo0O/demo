#include <sn8f5702.h>
#include "adc.h"
#include "bat.h"
#include "ctrl.h"
#include "device.h"
#include "key.h"
#include "led.h"
#include "light.h"
#include "moto.h"
#include "timer.h"
#include "typec.h"
#include "except.h"

struct Ctrl ctrl;

code unsigned char CTRL_CHARGE_MAXS[] = {0x38, 0x30, 0x22, 0x0a, 0x0a};
code unsigned char CTRL_DISCHARGE_MAXS[] = {0x08, 0x08, 0x1C, 0x20, 0x24};

code unsigned char SOS_ARR[SOS_INDEX_LEN] = {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0};

    
sbit charge_pin = P0^0;
sbit len_pin = P0^1; 

void init_ctrl(void){
    init_adc();
    init_bat();
    init_key();
    init_led();
    init_light();
    init_moto();
    start_timer0();
    ctrl.wait_acc = 1;
}

void ctrl_adc_event(void){
    if(ctrl.adc_tick == 0) return;
    ctrl.adc_tick = 0;
    adc_start_convert();
}

void ctrl_average_vol(void){
    unsigned int adc_vol = 0;
    if(ctrl.average_vol_tick == 0) return;
    ctrl.average_vol_tick = 0;
    adc_vol = get_adc_it_val(BAT_CHANNEL);
    if(ctrl.vol_count < AVERAGE_COUNT){
        ctrl.vol_sum += adc_vol;
        ctrl.vol_count++;
    }else{
        ctrl.average_vol = (ctrl.vol_sum / AVERAGE_COUNT) << 4;
        ctrl.vol_sum = 0;
        ctrl.vol_count = 0;
    }
}

void ctrl_bat_charge_event(void){
    unsigned int bat_vol = 0;
    unsigned char bat_level = 0;
    unsigned char is_typec_in = 0; 
    if(ctrl.bat_charge_tick == 0 ) return;
    ctrl.bat_charge_tick = 0;
    is_typec_in = get_typec_insert_state();
    bat_level = get_bat_level(is_typec_in);
    ctrl.charge_tick_max = CTRL_CHARGE_MAXS[bat_level];
    if(is_typec_in == 0) return;
    bat_vol = get_bat_vol();
    if(ctrl.average_vol > bat_vol){
        set_bat_vol(ctrl.average_vol);
    }
}

void ctrl_bat_discharge_event(void){
    unsigned int bat_vol = 0;
    unsigned char bat_level = 0;
    unsigned char is_typec_in = 0;
    if(ctrl.bat_discharge_tick == 0 ) return;
    ctrl.bat_discharge_tick = 0;
    is_typec_in = get_typec_insert_state();
    bat_level = get_bat_level(is_typec_in);
    ctrl.discharge_tick_max = CTRL_DISCHARGE_MAXS[bat_level];
    bat_vol = get_bat_vol();
    if(is_typec_in) return;
    if(ctrl.average_vol < bat_vol){
        set_bat_vol(ctrl.average_vol);
    }
}

void ctrl_key_event(void){
    if(ctrl.key_tick == 0) return;
    ctrl.key_tick = 0;
    scan_key();
}

void ctrl_charge_full_event(void){
    unsigned char is_typec_in = 0;
    if(ctrl.charge_full_tick == 0) return;
    ctrl.charge_full_tick = 0;
    is_typec_in = get_typec_insert_state();
    if(is_typec_in == 0){
        if(ctrl.average_vol < CTRL_FULL_VOL_MIN ){
            ctrl.wait_acc = 1;
            ctrl.charge_full_wait0 = 0;
            ctrl.charge_full_wait1 = 0;
            ctrl.charge_full_wait_done = 0;
        }
        return;
    }
    if(ctrl.average_vol > LED_WAIT_LEVEL_1){
        if(ctrl.charge_full_wait1 < CTRL_CHARGE_WAIT_TIME1){
            ctrl.charge_full_wait1 += ctrl.wait_acc;
            ctrl.charge_full_wait_done = 0;
        }else{
            ctrl.charge_full_wait_done = 1;
        }
    }else if(ctrl.average_vol > LED_WAIT_LEVEL_0){
        if(ctrl.charge_full_wait0 < CTRL_CHARGE_WAIT_TIME0){
            ctrl.charge_full_wait0 += ctrl.wait_acc;
            ctrl.charge_full_wait_done = 0;
        }else{
            ctrl.charge_full_wait_done = 1;
        }
    }else{
        ctrl.charge_full_wait0 = 0;
        ctrl.charge_full_wait1 = 0;
        ctrl.charge_full_wait_done = 0;
    }
}

void ctrl_led_event(void){
    unsigned char led_level = 0;
    unsigned char led_mode = 0;
    unsigned char bat_level = 0;
    unsigned char is_typec_in = 0;
    if(ctrl.led_tick == 0) return;
    ctrl.led_tick = 0;
    
    is_typec_in = get_typec_insert_state();
    led_level = get_led_level();
    bat_level = get_bat_level(is_typec_in);
    led_mode = get_led_mode();
    
    if(led_mode == CTRL_OFF_MODE){
        set_led_level(LED_ON0);
    }else if(led_mode == CTRL_ALERT_MODE){
        if(ctrl.alert_count < CTRL_ALERT_MAX){
            ctrl.alert_count++;
            if(led_level){
                set_led_level(LED_ON0);
            }else{
                set_led_level(LED_ON3);
            }
        }else{
            led_mode = CTRL_DISCHARGE_MODE;
            ctrl.alert_count = 0;
            set_except_alert_done(1);
        }
    }else if(led_mode == CTRL_CHARGE_MODE){  
        
        if(bat_level >= BAT_LEVEL_3){
            if(ctrl.charge_full_wait_done){
                set_led_level(LED_ON3);
            }else{
                if(led_level == 3){
                    led_level = LED_ON2;
                }else{
                    led_level = LED_ON3;
                }
                set_led_level(led_level);
            }
        }else if(bat_level == BAT_LEVEL_2){
            if(led_level == 2){
                led_level = LED_ON3;
            }else if(led_level == 1){
                led_level = LED_ON2;
            }else{
                led_level = LED_ON1;
            }
            set_led_level(led_level);
        }else{
            set_led_level(led_level + 1);
        }
    }else if(led_mode == CTRL_DISCHARGE_MODE){
        if(bat_level == BAT_LEVEL_0){
            set_led_level(LED_ON0);
        }else if(bat_level == BAT_LEVEL_1){
            if(led_level){
                set_led_level(LED_ON0);
            }else{
                set_led_level(LED_ON1);
            }
        }else{
            set_led_level(bat_level - 1);
        }
    }
}

void ctrl_red_light_event(void){
    unsigned char red_mode = 0;
    unsigned char red_state = 0;
    if(ctrl.red_light_tick == 0) return;
    ctrl.red_light_tick = 0;
    red_mode = get_red_mode();
    red_state = get_red_pin_state();
    if(red_mode == RED_ON_MODE){
        set_red_pin_state(!red_state);
    }else{
        set_red_pin_state(LIGHT_OFF);
    }
}

void ctrl_white_light_event(void){
    unsigned char white_mode = 0;
    unsigned char white_state = 0;
    unsigned char sos_index = 0;
    if(ctrl.white_light_tick == 0) return;
    ctrl.white_light_tick = 0;
    white_mode = get_white_mode();
    white_state = get_white_pin_state();
    if(white_mode == WHITE_ON_MODE){
        set_white_pin_state(LIGHT_ON);
    }else if(white_mode == WHITE_SOS_MODE){
        set_white_sos_increase();
        sos_index = get_white_sos_index();
        set_white_pin_state(SOS_ARR[sos_index]);
    }else{
        set_white_pin_state(LIGHT_OFF);
    }
}

void ctrl_moto_event(void){
    if(ctrl.moto_tick == 0) return;
    ctrl.moto_tick = 0;
    set_moto_state();
}

void set_device_state_entry(void){
    unsigned char mode = 0;
    mode = get_device_mode();
    if(mode == DEVICE_STOP_MODE){
        stop_timer0();
        set_adc_state(ADC_OFF);
        set_led_mode(LED_OFF_MODE);
        init_key();
        init_led();
        init_light();
        stop_moto();
        stop_device();
        STOP();
        set_device_mode(DEVICE_RUN_MODE);
        start_device();
        start_timer0();
        set_adc_state(ADC_ON);
    }
}


void set_work_mode_entry(void){
    unsigned char val = 0;
    unsigned char red_mode = 0;
    unsigned char white_mode = 0;
    unsigned char moto_level = 0;
    val = get_act_key();
    switch(val){
        case KEY1_CLICK:
            red_mode = get_red_mode();
            if(red_mode){
                set_red_mode(RED_OFF_MODE);
            }else{
                white_mode = get_white_mode();
                set_white_mode(white_mode + 1);
            }
            stop_moto();
            break;
        case KEY1_PRESS:
            set_red_mode(RED_ON_MODE);
            set_white_mode(WHITE_OFF_MODE);
            stop_moto();
            break;
        case KEY2_CLICK:
            set_red_mode(RED_OFF_MODE);
            set_white_mode(WHITE_OFF_MODE);
            stop_moto();
            break;
        case KEY2_PRESS:
            set_red_mode(RED_OFF_MODE);
            set_white_mode(WHITE_OFF_MODE);
            set_moto_level(MOTO_LEVEL_1);
            break;
    }
    free_key();
}


// ALERT_MODE
/**
*  mode 0: except == 0 and  alert == 0,    mode==0;
*  mode 1: except == 1 and  alert == 0x0f, mode==1;
*  mode 2: except == 1 and  alert == 0,    mode==2;
*  mode 0: no except and alert done;
*/

void set_charge_full_wait_acc(unsigned char acc){
    ctrl.wait_acc = acc;
}
/*
void ctrl_average_ntc1(void){
    unsigned int adc_ntc1 = 0;
    if(ctrl.average_ntc1_tick == 0) return;
    ctrl.average_ntc1_tick = 0;
    adc_ntc1 = get_adc_it_val(NTC1_CHANNEL);
    if(ctrl.ntc1_count < AVERAGE_COUNT){
        ctrl.ntc1_sum += adc_ntc1;
        ctrl.ntc1_count++;
    }else{
        ctrl.average_ntc1 = ctrl.ntc1_sum / AVERAGE_COUNT;
        ctrl.ntc1_sum = 0;
        ctrl.ntc1_count = 0;
    }
}
void ctrl_average_ntc2(void){
    unsigned int adc_ntc2 = 0;
    if(ctrl.average_ntc2_tick == 0) return;
    ctrl.average_ntc2_tick = 0;
    adc_ntc2 = get_adc_it_val(NTC2_CHANNEL);
    if(ctrl.ntc2_count < AVERAGE_COUNT){
        ctrl.ntc2_sum += adc_ntc2;
        ctrl.ntc2_count++;
    }else{
        ctrl.average_ntc2 = ctrl.ntc2_sum / AVERAGE_COUNT;
        ctrl.ntc2_sum = 0;
        ctrl.ntc2_count = 0;
    }
}

*/
