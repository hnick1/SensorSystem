#ifndef SENSOR_THREAD_STATE_H
#define SENSOR_THREAD_STATE_H

#include "definitions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "debug.h"
//#include "uart_thread_queue.h"
//#include "jsmn.h"
#include "mqtt_if.h"
#include "mqueue.h"
#include "mqtt_publish_queue_def.h"
#include "hash-string.h"

void update_FSM( SensorMessage_t* mes, mqd_t handle );

#endif
