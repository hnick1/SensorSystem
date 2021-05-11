#ifndef TOF_THREAD_STATE_H
#define TOF_THREAD_STATE_H

#include "FreeRTOS.h"
#include "definitions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "debug.h"
#include "hash-string.h"
#include "tof_thread_queue.h"
#include "control_thread_queue.h"

#define DATA_END 13

typedef enum tofState_t {
    WAIT,
    INIT_DATA,
    APPEND_DATA
} tofState_t;

void update_tof_FSM(char sensorReading);

#endif
