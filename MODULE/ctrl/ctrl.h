#ifndef __CTRL_H
#define __CTRL_H

#define  AVERAGE_COUNT             0x0c

#define  CTRL_FULL_VOL_MIN          0xe300

#define  CTRL_CHARGE_WAIT_TIME1     0x1770
#define  CTRL_CHARGE_WAIT_TIME0     0x3e80

#define  CTRL_OFF_MODE             0x00
#define  CTRL_CHARGE_MODE          0x01
#define  CTRL_DISCHARGE_MODE       0x02
#define  CTRL_ALERT_MODE           0x03


#define  CTRL_ALERT_MAX            0x05

struct Ctrl {
    unsigned int charge_full_wait0;
    unsigned int charge_full_wait1;
    unsigned char wait_acc;

    unsigned int average_vol;
    unsigned int vol_sum;
    unsigned char vol_count;
    

    unsigned char charge_count;
    unsigned char discharge_count;
    
    unsigned char charge_tick_max;
    unsigned char discharge_tick_max;
    
    unsigned char alert_count;
    
    unsigned char adc_tick:1;

    unsigned char average_vol_tick:1;
    unsigned char average_ntc1_tick:1;
    unsigned char average_ntc2_tick:1;

    unsigned char bat_charge_tick:1;
    unsigned char bat_discharge_tick:1;
    unsigned char key_tick:1;
    unsigned char charge_full_tick:1;
    unsigned char led_tick:1;
    unsigned char red_light_tick:1;
    unsigned char white_light_tick:1;
    unsigned char moto_tick:1;
    
    unsigned char charge_full_wait_done:1;
};
void init_ctrl(void);
void ctrl_adc_event(void);
void ctrl_average_vol(void);
void ctrl_bat_charge_event(void);
void ctrl_bat_discharge_event(void);
void ctrl_key_event(void);
void ctrl_charge_full_event(void);
void ctrl_led_event(void);
void ctrl_red_light_event(void);
void ctrl_white_light_event(void);
void ctrl_moto_event(void);

void set_device_state_entry(void);
void set_work_mode_entry(void);

void set_charge_full_wait_acc(unsigned char acc);
unsigned int get_ctrl_average_val(unsigned char channel);

#endif
