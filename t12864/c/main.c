#include <sn8f5804.h>
#include "system.h"
#include "lcd.h"
#include "key.h"


extern struct System system;

void main(void){
    init_system();
    start_system();
    start_timer0();
    switch_lcd(LCD_ON);
    while(1){
        WDTR = 0x5a;
        check_exception();
        check_state();
        scan_key();
        handle_key();
        display();
    }
}