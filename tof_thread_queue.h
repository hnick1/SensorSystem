#ifndef TOF_THREAD_QUEUE_H
#define TOF_THREAD_QUEUE_H

#include <stdio.h>
#include <FreeRTOS.h>
#include "queue.h"
#include "definitions.h"
#include "debug.h"
#include <stdbool.h>
#include <ti/drivers/dpl/HwiP.h>

#define TOF_QUEUE_LENGTH 10
#define TOF_QUEUE_ITEM_SIZE sizeof(struct ToFMessage_t)

void createToFQueue();

bool readToFMessage(ToFMessage_t* message_ptr);
void sendToFMessage(ToFMessage_t* message_ptr);

#endif
