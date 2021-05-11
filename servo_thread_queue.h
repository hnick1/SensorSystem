#ifndef SERVO_THREAD_QUEUE_H
#define SERVO_THREAD_QUEUE_H

#include "FreeRTOS.h"
#include "queue.h"
#include "definitions.h"
#include "debug.h"
#include <stdbool.h>
#include <ti/drivers/dpl/HwiP.h>

#define SERVO_QUEUE_LENGTH 20
#define SERVO_QUEUE_ITEM_SIZE sizeof( struct ServoMessage_t )

void createServoQueue();

bool readServoMessage( ServoMessage_t* message_ptr );
void sendServoMessage( ServoMessage_t* message_ptr );

#endif
