#include <sn8f5702.h>
#include "except.h"
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

sbit in_fuse_pin = P2^0;
sbit out_fuse_pin = P2^1;
sbit charge_pin = P0^0;
sbit len_pin = P0^1;

struct Except except;

code unsigned int TEMP_HIGHS[] = {0x060, 0x050, 0x050};
code unsigned int TEMP_LOWS[]  = {0x4e0, 0x4e0, 0x4e0};

void init_except(void){
    except.first_on = 1;
}

void check_adc_vol_except(void){
    unsigned int adc_vol = 0;
    unsigned char is_stable = 0;
    if(except.adc_tick == 0) return;
    except.adc_tick = 0;
    adc_vol = (get_adc_it_val(BAT_CHANNEL) <<4);
    
    if(adc_vol < BAT_LOW_LIMIT  || adc_vol > BAT_HIGH_LIMIT ){
        except.stable_count = 0;
        if(except.unstable_count < EXCEPT_UNSTABLE_MAX){
            except.unstable_count++;
        }else{
            set_bat_stable(0);
            except.is_vol_err = 1;
        }
        
    }else{
        except.unstable_count = 0;
        if(except.stable_count < EXCEPT_STABLE_MAX){
            except.stable_count++;
        }else{
            is_stable = get_bat_stable();
            if(is_stable == 0){
                set_bat_vol(adc_vol);
                set_bat_stable(1);
            }
            except.first_on = 0;
        }
    }
}

void check_bat_except(void){
    unsigned int bat_vol = 0;
    unsigned char first_on = 0;
    unsigned char is_typec_in = 0;
    if(except.bat_tick == 0) return;
    except.bat_tick = 0;
    if(except.first_on) return;
    is_typec_in = get_typec_insert_state();
    if(is_typec_in) return;
    bat_vol = get_bat_vol();
    if(bat_vol < BAT_MIN_VOL){
        except.is_bat_empty = 1;
    }
}
void check_ntc1_except(void){
    unsigned int temp = 0;
    unsigned char moto_level = 0;
    if(except.ntc1_tick == 0) return;
    except.ntc1_tick = 0;
    moto_level = get_moto_level();
    temp = get_adc_it_val(NTC1_CHANNEL);
    
    if(temp > TEMP_LOWS[moto_level] || temp < TEMP_HIGHS[moto_level]){
        if(except.ntc1_err_count < OVER_TEMP_CONFIRM){
            except.ntc1_err_count++;
        }else{
            except.is_ntc1_err = 1;
        }
    }else{
        except.ntc1_err_count = 0;
        except.is_ntc1_err = 0;
    }
}
void check_ntc2_except(void){
    unsigned int temp = 0;
    unsigned char moto_level = 0;
    if(except.ntc2_tick == 0) return;
    except.ntc2_tick = 0;
    moto_level = get_moto_level();
    temp = get_adc_it_val(NTC2_CHANNEL);
    
    if(temp > TEMP_LOWS[moto_level] || temp < TEMP_HIGHS[moto_level]){
        if(except.ntc2_err_count < OVER_TEMP_CONFIRM){
            except.ntc2_err_count++;
        }else{
            except.is_ntc2_err = 1;
        }
    }else{
        except.ntc2_err_count = 0;
        except.is_ntc2_err = 0;
    }
}

void check_charge_except(void){
    unsigned char is_typec_in = 0;
    
    if(except.charge_tick == 0) return;
    except.charge_tick = 0;
    is_typec_in = get_typec_insert_state();
    if((in_fuse_pin ==0) && is_typec_in){
        if(except.charge_err_count < CHARGE_PROTECT_CONFIRM){
            except.charge_err_count++;
        }else{
            except.is_charge_err = 1; 
        }
    }else{
        except.charge_err_count = 0;
        except.is_charge_err = 0;
    }
}

void check_discharge_except(void){
    unsigned char is_typec_in = 0;
    if(except.discharge_tick == 0) return;
    except.discharge_tick = 0;
    is_typec_in = get_typec_insert_state();
    if(out_fuse_pin || is_typec_in){
        except.discharge_err_count = 0;
    }else{
        if(except.discharge_err_count < DISCHARGE_PROTECT_CONFIRM){
            except.discharge_err_count++;
        }else{
            except.is_discharge_err = 1;
        }
    }
}

void check_moto_except(void){
    if(except.moto_tick == 0) return;
    except.moto_tick = 0;

}

void handle_run_mode(void){
    unsigned char red_mode = 0;
    unsigned char white_mode = 0;
    unsigned char moto_level = 0;
    unsigned char key_pin_state = 0;
    unsigned char is_typec_in = 0;

    is_typec_in = get_typec_insert_state();
    if(is_typec_in){
        len_pin = 0;
        set_device_mode(DEVICE_CHARGE_MODE);
        set_key_mode(KEY_INVALID_MODE);
        set_red_mode(WHITE_OFF_MODE);
        set_white_mode(WHITE_OFF_MODE);
        stop_moto();
        set_led_mode(LED_CHARGE_MODE);
        return;
    }
    set_key_mode(KEY_VALID_MODE);
    
    red_mode = get_red_mode();
    white_mode = get_white_mode();
    moto_level = get_moto_level();
    
    if(red_mode || white_mode || moto_level){
        len_pin = 1;
        except.idle_count = 0;
        if(except.is_ntc1_err || except.is_ntc2_err){
            set_led_mode(LED_ALERT_MODE);   // TODO
        }else{
            set_led_mode(LED_DISCHARGE_MODE);
        }
    }else{
        len_pin = 0;
        set_led_mode(LED_OFF_MODE);
        if(except.first_on) return;
        key_pin_state = get_key_pin_state();
        if(key_pin_state == KEY_NULL){
            if(except.idle_count < DEVICE_IDLE_CONFIRM){
                except.idle_count++;
            }else{
                set_device_mode(DEVICE_STOP_MODE);
            }
        }else{
            except.idle_count = 0;
        }
    }    
}


void handle_charge_except(void){
    int adc_vol = 0;
    unsigned char is_typec_in = 0;
    is_typec_in = get_typec_insert_state();
    if(is_typec_in == 0) return;
    // RECOVER
    except.is_bat_empty = 0;
    except.is_discharge_err = 0;
    except.idle_count = 0;
    
    if(except.is_ntc1_err || except.is_ntc2_err || except.is_charge_err ){
        charge_pin = 0; 
    }else{
        charge_pin = 1;
    }
    if(except.is_charge_err ){
        bat_auto_increase();
        adc_vol = (get_adc_it_val(BAT_CHANNEL) << 4);
        set_bat_sub_delta(adc_vol);
        set_charge_full_wait_acc(10);
    }else{
        set_charge_full_wait_acc(1);
    }
}

void handle_discharge_except(void){
    unsigned char is_typec_in = 0;
    is_typec_in = get_typec_insert_state();
    if(is_typec_in) return;
    charge_pin = 0;
    
    if(except.is_discharge_err){
        // shutdown and lock
        set_device_mode(DEVICE_STOP_MODE);
        return;
    }
    
    if(except.is_bat_empty){
        // shutdown and lock
        set_device_mode(DEVICE_STOP_MODE);
        return;
    }
    if(except.is_vol_err){
        set_device_mode(DEVICE_STOP_MODE);
        except.is_vol_err = 0;
    }
    if(except.is_moto_err){
        // shutdown
        set_device_mode(DEVICE_STOP_MODE);
        except.is_moto_err = 0;
        return;
    }
    if(except.is_alert_done){
        except.is_alert_done = 0;
        except.is_ntc1_err = 0;
        except.is_ntc2_err = 0;
        set_device_mode(DEVICE_STOP_MODE);
    }
}


void set_except_alert_done(unsigned char is_done){
    except.is_alert_done = (is_done == EXCEPT_ALERT_DONE);
}
