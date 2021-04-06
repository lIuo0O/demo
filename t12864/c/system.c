#include <sn8f5804.h>
#include "system.h"
#include "lcd.h"
#include "key.h"

struct System system;
extern struct Lcd lcd;
extern struct Key key;
/*******************************************************************************************/

/*******************************************************************************************/
void init_system(void){
    CKCON = 0x70;
    CLKSEL = 0x83;    //  2M
    CLKCMD = 0x69;
    CKCON = 0x10;
    system.state = 1;
    system.id = SYSTEM_ID;
}
/*******************************************************************************************/
void start_system(void){
    P0UR = 0x00;
    P0M  = 0xfd;
    P0   = 0x00;
    P1UR = 0x00;
    P1M  = 0xff;
    P1   = 0x00;
    P2UR = 0x0F;
    P2M  = 0xf0;
    P2   = 0x0F;
    P3UR = 0x00;
    P3M  = 0xff;
    P3   = 0x00;
    IEN0 = 0x80;
}
/*******************************************************************************************/
void stop_system(void){
    P0UR = 0x00;
    P0M  = 0xff;
    P0   = 0x00;
    P1UR = 0x00;
    P1M  = 0xff;
    P1   = 0x07;
    P2UR = 0x00;
    P2M  = 0xff;
    P2   = 0x00;
    P3UR = 0x00;
    P3M  = 0xff;
    P3   = 0x00;
}
/*******************************************************************************************/
void start_timer0(void){
    if(system.t0_on) return;
    TMOD |= TIMER0_MODE1;
    IEN0 |= TIMER0_IT_EN;
    TCON |= TIMER0_RUN;
    system.t0_on = 1;
}

void stop_timer0(void){
    if(system.t0_on == 0) return;
    TCON &= TIMER0_STOP;
    IEN0 &= TIMER0_IT_DIS;
    system.t0_on = 0;
}
void check_exception(void){

}
/*******************************************************************************************/
void check_state(void){
    if(system.shutting){
        system.state = 0;
        switch_lcd(LCD_OFF);
        stop_timer0();
        stop_system();
        STOP();
        start_system();
        start_timer0();
        return;
    }
    system.state = 1;
    switch_lcd(LCD_ON);
}
/*******************************************************************************************/
void timer0_irq(void) interrupt ISRTimer0{
    TH0 = TIMER0_H;
    TL0 = TIMER0_L;
    key.scan_tick = 1;
    key.handler_tick = 1;
}