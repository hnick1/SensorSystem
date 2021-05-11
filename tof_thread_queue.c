#include "tof_thread_queue.h"

static QueueHandle_t tofQueueHandle = NULL;

void createToFQueue() {
    //dbgEvent( CHAIN_QUEUE_CREATE );

    tofQueueHandle = xQueueCreate( TOF_QUEUE_LENGTH, TOF_QUEUE_ITEM_SIZE );

    if (tofQueueHandle == NULL) {
        //dbgEvent( FATAL_CHAIN_QUEUE );
    }

    //dbgEvent( CHAIN_QUEUE_SUCCESS );
}

bool readToFMessage( ToFMessage_t* message_ptr ) {
    //dbgEvent( TOF_QUEUE_READ_ENTER );
    if( HwiP_inISR() ) {
        //dbgEvent( CHAIN_QUEUE_READ_ISR );
        BaseType_t xtask = pdFALSE;

        if( xQueueReceiveFromISR( tofQueueHandle, message_ptr, &xtask ) != pdPASS ) {
            dbgEvent(0x52);
            return false;

        }
        // message now contains new info
        //dbgEvent( TOF_QUEUE_READ_SUCCESS_ISR );
        return true;
    }
    else {
        //dbgEvent
        //dbgEvent( SENSOR_THREAD_QUEUE_READ_NOT_ISR );
        if( xQueueReceive( tofQueueHandle, message_ptr, portMAX_DELAY ) != pdPASS ) {
            dbgEvent(0x54);
            return false;
        }
        // message now contains new info
        //dbgEvent
        //dbgEvent( TOF_QUEUE_READ_SUCCESS_NOT_ISR );
        return true;
    }
}

void sendToFMessage( ToFMessage_t* message_ptr ) {
    BaseType_t xHigherPriorityTaskWoken;
    xHigherPriorityTaskWoken = pdFALSE;

    //dbgEvent( TOF_QUEUE_SEND_ENTER );
    if ( HwiP_inISR() ) {
        //dbgEvent( CHAIN_QUEUE_SEND_ISR );
        if( xQueueSendFromISR( tofQueueHandle, message_ptr,  &xHigherPriorityTaskWoken ) != pdPASS ) {
            // Queue is full, fail
            return;
        }

        //dbgEvent( SENSOR_THREAD_QUEUE_SEND_ISR_SUCCESS );
    }
    else {
        //dbgEvent( CHAIN_QUEUE_SEND_NOT_ISR );
        if( xQueueSend( tofQueueHandle, message_ptr, portMAX_DELAY ) != pdPASS ) {
            //dbgEvent( FATAL_CHAIN_QUEUE_SEND );
            return;
        }
    }
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );

    //dbgEvent( TOF_QUEUE_SEND_SUCCESS );
}
