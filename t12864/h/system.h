#ifndef __SYSTEM_H
#define __SYSTEM_H

#define   TIMER0_H              0xfc
#define   TIMER0_L              0xbf
#define   TIMER0_MODE1          0x01
#define   TIMER0_RUN            0x10
#define   TIMER0_STOP           0xef
#define   TIMER0_IT_EN          0x02
#define   TIMER0_IT_DIS         0xfd


#define   SYSTEM_ID             0x34




struct System {
    unsigned char state;
    unsigned char id;
    unsigned char shutting:1;
    unsigned char t0_on:1;
};

void init_system(void);

void start_system(void);

void stop_system(void);

void start_timer0(void);
void stop_timer0(void);

void check_exception(void);

void check_state(void);

#endif