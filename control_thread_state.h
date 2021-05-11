#ifndef CONTROL_THREAD_STATE_H
#define CONTROL_THREAD_STATE_H

#include "FreeRTOS.h"
#include "definitions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "tof_thread_queue.h"
#include "servo_thread_queue.h"
#include "control_thread_queue.h"
#include "mqtt_if.h"
#include "mqueue.h"
#include "mqtt_publish_queue_def.h"

#define MIN_DUTY 600
#define MAX_DUTY 2400
#define DUTY_INC 300
#define DUTY_TO_DEGREES_SUB 600
#define DUTY_TO_DEGREES_DIV 10

typedef enum controlState_t {
    UPDATE_SERVO,
    UPDATE_SENSOR
} controlState_t;

void update_control_FSM(ControlMessage_t mes, mqd_t handle);

#endif
