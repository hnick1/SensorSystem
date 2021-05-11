#ifndef SERVO_TASK_H
#define SERVO_TASK_H

#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/Timer.h>
#include <ti/drivers/Board.h>
#include <ti/drivers/PWM.h>
#include "ti_drivers_config.h"
#include "FreeRTOS.h"
#include "definitions.h"
#include "servo_thread_queue.h"
#include "servo_thread_state.h"
#include "tof_thread_queue.h"
#include <pthread.h>
#include "debug.h"

#define PRIORITY 1
#define SERVOTHREADSIZE 1024

void init_servo_thread(Timer_Handle servoTimer);
void *servo_task();

#endif
