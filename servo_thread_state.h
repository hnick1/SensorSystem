#ifndef SERVO_THREAD_STATE_H
#define SERVO_THREAD_STATE_H

#include "FreeRTOS.h"
#include "definitions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "debug.h"
#include "hash-string.h"
#include "servo_thread_queue.h"
#include "control_thread_queue.h"
#include <ti/drivers/Timer.h>
#include <ti/drivers/PWM.h>

typedef enum servoState_t {
    IDLE,
    TURN
} servoState_t;

void update_servo_FSM(PWM_Handle pwm, Timer_Handle time);

#endif
