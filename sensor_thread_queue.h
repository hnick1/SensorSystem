#ifndef SENSOR_THREAD_QUEUE_H
#define SENSOR_THREAD_QUEUE_H

#include "FreeRTOS.h"
#include "queue.h"
#include "definitions.h"
#include "debug.h"
#include <stdbool.h>
#include <ti/drivers/dpl/HwiP.h>
//#include "mqtt_if.h"
//#include "mqueue.h"

#define SENSOR_QUEUE_LENGTH 3
#define SENSOR_QUEUE_ITEM_SIZE sizeof( SensorMessage_t )

void createSensorQueue();

bool readSensorMessage( SensorMessage_t* message_ptr );
void sendSensorMessage( SensorMessage_t* message_ptr );

#endif
