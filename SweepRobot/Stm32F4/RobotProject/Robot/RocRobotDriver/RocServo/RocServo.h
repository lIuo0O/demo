/********************************************************************************
 * This code is used for robot control
*********************************************************************************
 * Author        Data            Version
 * Liren         2018/12/15      1.0
********************************************************************************/
#ifndef __ROC_SERVO_H
#define __ROC_SERVO_H


#include <stdint.h>

#include "tim.h"

#include "RocError.h"


//#define ROC_ROBOT_SERVO_DEBUG

#define ROC_SERVO_TIMER_ONE_SECOND_TICKS    (ROC_TIMER_PRESCALER_TIM6 / 1000)


#define ROC_SERVO_SPEED_DIV_STP             4
#define ROC_SERVO_SPEED_DOWN_MAG            1.2


#define ROC_SERVO_PWM_CYCLE                 20  /* ms */


#define ROC_SERVO_MAX_SUPPORT_NUM           18U

#define ROC_SERVO_MAX_PWM_VAL               502
#define ROC_SERVO_MIN_PWM_VAL               102
#define ROC_SERVO_CENTER_VAL                256

#define ROC_SERVO_MAX_ROTATE_ANGLE          180


void RocServoOutputEnable(void);
void RocServoOutputDisable(void);
ROC_RESULT RocServoTimerStop(void);
ROC_RESULT RocServoTimerStart(void);
ROC_RESULT RocServoTurnIsFinshed(void);
ROC_RESULT RocServoInit(int16_t *pServoInputVal);
void RocServoSpeedSet(uint16_t ServoRunTimeMs);
void RocServoControl(int16_t *pServoInputVal);


#endif

