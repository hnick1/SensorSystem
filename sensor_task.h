#ifndef SENSOR_TASK_H
#define SENSOR_TASK_H

#include "FreeRTOS.h"
#include "definitions.h"
#include "sensor_thread_queue.h"
#include "sensor_thread_state.h"
#include <pthread.h>
#include "debug.h"
#include "mqtt_if.h"
#include "mqueue.h"

#define PRIORITY 1
#define SENSORTHREADSTACKSIZE 1024

void init_sensor_thread( mqd_t handle );
void* sensor_task();

#endif
