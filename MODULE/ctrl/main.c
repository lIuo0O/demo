#include <sn8f5702.h>
#include "device.h"
#include "except.h"
#include "ctrl.h"
/*
*   data:82;
*   code:3346;
*   checksum:0x8ee4;
*/

void main(void){
    init_device();
    start_device();
    init_except();
    init_ctrl();
    while(1){
        WDTR = 0x5a;
        // exceptions
        check_adc_vol_except();
        check_bat_except();
        check_ntc1_except();
        check_ntc2_except();
        check_charge_except();
        check_discharge_except();
        check_moto_except();
        handle_run_mode();
        handle_charge_except();
        handle_discharge_except();
        // 
        set_device_state_entry();
        set_work_mode_entry();
        // event
        ctrl_adc_event();
        ctrl_average_vol();
        ctrl_bat_charge_event();
        ctrl_bat_discharge_event();
        ctrl_key_event();
        ctrl_charge_full_event();
        ctrl_led_event();
        ctrl_red_light_event();
        ctrl_white_light_event();
        ctrl_moto_event();
        // IDLE
        IDLE();
    }
}
