#ifndef __TIMER_H
#define __TIMER_H

#define          TIMER0_H                     0xe5
#define          TIMER0_L                     0xf5

#define          TIMER0_MODE1                 0x01
#define          TIMER0_RUN                   0x10
#define          TIMER0_IT_EN                 0x02
#define          TIMER0_IT_DIS                0xfd
#define          TIMER0_STOP                  0xef
#define          TIMER0_60MS                  0x05
#define          TIMER0_300MS                 0x04

#define          TIMER0_50MS_CONFIRM          0x05
#define          TIMER0_300MS_CONFIRM         0x1e

/***************************************************************************/



struct Timer{
    unsigned char t0_50ms_count;
    unsigned char t0_300ms_count;

    unsigned char t0_on:1;
    
};
void start_timer0(void);
void stop_timer0(void);
#endif
