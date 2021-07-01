#ifndef __LED_H
#define __LED_H

#define          CLEAR_LED                    0xc7
#define          LED_ARR_LEN                  0x04

#define  LED_OFF_MODE             0x00
#define  LED_CHARGE_MODE          0x01
#define  LED_DISCHARGE_MODE       0x02
#define  LED_ALERT_MODE           0x03

#define          LED_ON0                      0x00
#define          LED_ON1                      0x01
#define          LED_ON2                      0x02
#define          LED_ON3                      0x03

struct Led {
    unsigned char mode;
    unsigned char level;
};
void init_led(void);
void set_led_level(unsigned char level);
void set_led_mode(unsigned char mode);
unsigned char get_led_mode(void);
unsigned char get_led_level(void);

#endif
