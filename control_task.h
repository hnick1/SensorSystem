#ifndef CONTROL_TASK_H
#define CONTROL_TASK_H

#include "FreeRTOS.h"
#include "definitions.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "debug.h"
#include "mqtt_if.h"
#include "mqueue.h"
#include "mqtt_publish_queue_def.h"
#include "hash-string.h"
#include "tof_thread_queue.h"
#include "servo_thread_queue.h"
#include "control_thread_queue.h"
#include "control_thread_state.h"

#define CONTROLPRIORITY 1
#define CONTROLTHREADSTACKSIZE 1024

void init_control_thread( mqd_t handle );
void *control_task();

#endif
