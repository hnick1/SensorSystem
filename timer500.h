/*
 * timer500.h
 *
 *  Created on: Feb 9, 2021
 *      Author: drew1
 */

#ifndef TIMER500_H_
#define TIMER500_H_

#define TIMER500_LENGTH 20000
#include <stddef.h>

/* Driver Header files */
#include <ti/drivers/dpl/HwiP.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/Timer.h>
#include "FreeRTOS.h"
#include "task.h"
#include "definitions.h"
#include "debug.h"
#include "servo_thread_queue.h"
/* Board Header file */
#include "ti_drivers_config.h"

Timer_Handle timer500Setup();

void timerCallback500(Timer_Handle myHandle, int_fast16_t status);




#endif
