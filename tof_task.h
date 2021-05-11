#ifndef TOF_TASK_H
#define TOF_TASK_H

#include <stddef.h>
#include <stdio.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/Timer.h>
#include <ti/drivers/Board.h>
#include "ti_drivers_config.h"
#include <ti/drivers/UART.h>
#include "FreeRTOS.h"
#include "definitions.h"
#include <pthread.h>
#include "debug.h"
#include "tof_thread_state.h"
#include "tof_thread_queue.h"

#define TOFPRIORITY 1
#define TOFTHREADSTACKSIZE 1024

void init_tof_thread();
void *tof_task();

#endif
