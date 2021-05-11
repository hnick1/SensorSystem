#ifndef CONTROL_THREAD_QUEUE_H
#define CONTROL_THREAD_QUEUE_H

#include "FreeRTOS.h"
#include "queue.h"
#include "definitions.h"
#include "debug.h"
#include <stdbool.h>
#include <ti/drivers/dpl/HwiP.h>

#define CONTROL_QUEUE_LENGTH 5
#define CONTROL_QUEUE_ITEM_SIZE sizeof( struct ControlMessage_t )

void createControlQueue();

bool readControlMessage( ControlMessage_t* message_ptr );
void sendControlMessage( ControlMessage_t* message_ptr );

#endif
