#ifndef __DEVICE_H
#define __DEVICE_H

#define       DEVICE_STOP_MODE              0x00
#define       DEVICE_RUN_MODE               0x01
#define       DEVICE_CHARGE_MODE            0x02

#define       DEVICE_MODE_LEN               0x02

#define       DEVICE_IDLE_CONFIRM           0x08

struct Device {
    unsigned char mode;
};

void init_device(void);
void start_device(void);
void stop_device(void);
void set_device_mode(unsigned char mode);
unsigned char get_device_mode(void);
#endif
