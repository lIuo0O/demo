#ifndef __MOTO_H
#define __MOTO_H
/***************************************************************************/
/***************************************************************************/
#define          MOTO_LEVEL_OFF               0x00
#define          MOTO_LEVEL_1                 0x01
#define          MOTO_LEVEL_2                 0x02
//  12/ 32M .= 2667



#define          PW1M_IT_DIS                  0x7f
#define          PW1M_IT_EN                   0x80
#define          PW1M_DIS                     0x7f
#define          PW1M_EN                      0x80
#define          PW1M_CLEAR_CHANNEL           0x00
#define          PW1M_RATE                    0x70

#define          PW1MY_MAX                   0x6A6b

#define          MOTO_ACC1                    0x12
#define          PWM_START_VAL               0x2a12

#define          P06_PWM_MODE                 0x10
#define          P06_GPIO_MODE                0xef

#define          PWM_MAX_SPEED               0x60d7
/**
 *     0x6a6b      27243
 *     0x60d7      24791
 *                   91%
 */
/***************************************************************************/
struct Moto{
    unsigned int  max_pwm;
    unsigned int  new_pwm;
    unsigned char delta_pwm;
    unsigned char level;
    unsigned char on:1;
    unsigned char first_acc:1;
    
};
/***************************************************************************/
void init_moto(void);
void set_moto_level(unsigned char level);
unsigned char get_moto_level(void);
void stop_moto(void);
void set_moto_state(void);
#endif
