#ifndef __EXCEPT_H
#define __EXCEPT_H

#define        DISCHARGE_PROTECT_CONFIRM           0x02
#define        CHARGE_PROTECT_CONFIRM              0x64
#define        OVER_TEMP_CONFIRM                   0x64
#define        EXCEPT_UNSTABLE_MAX                 0x64
#define        EXCEPT_STABLE_MAX                   0x64
#define        EXCEPT_ALERT_DONE                   0x01

struct Except {
    unsigned char idle_count;
    unsigned char charge_err_count;
    unsigned char discharge_err_count;
    
    unsigned char unstable_count;
    unsigned char stable_count;
    

    unsigned char ntc1_err_count;
    unsigned char ntc2_err_count;

    unsigned char first_on:1;
    
    unsigned char adc_tick:1;
    unsigned char bat_tick:1;
    unsigned char ntc1_tick:1;
    unsigned char ntc2_tick:1;
    unsigned char charge_tick:1;
    unsigned char discharge_tick:1;
    unsigned char moto_tick:1;
    
    unsigned char is_vol_err:1;
    unsigned char is_bat_empty:1;
    unsigned char is_ntc1_err:1;
    unsigned char is_ntc2_err:1;
    unsigned char is_charge_err:1;
    unsigned char is_discharge_err:1;
    unsigned char is_moto_err:1;
    unsigned char is_alert_done:1;
};

void init_except(void);
void check_adc_vol_except(void);
void check_bat_except(void);
void check_ntc1_except(void);
void check_ntc2_except(void);
void check_charge_except(void);
void check_discharge_except(void);
void check_moto_except(void);
void check_device_except(void);

void handle_run_mode(void);
void handle_charge_except(void);
void handle_discharge_except(void);


void set_except_alert_done(unsigned char done);
#endif
