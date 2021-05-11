#include "control_thread_queue.h"

static QueueHandle_t controlQueueHandle = NULL;

void createControlQueue() {
    //dbgEvent( CHAIN_QUEUE_CREATE );

    controlQueueHandle = xQueueCreate( CONTROL_QUEUE_LENGTH, CONTROL_QUEUE_ITEM_SIZE );

    if (controlQueueHandle == NULL) {
        //dbgEvent( FATAL_CHAIN_QUEUE );
    }

    //dbgEvent( CHAIN_QUEUE_SUCCESS );
}

bool readControlMessage( ControlMessage_t* message_ptr ) {
    //dbgEvent( CHAIN_QUEUE_READ_ENTER );
    dbgEvent(0x02);
    if( HwiP_inISR() ) {
        //dbgEvent( CHAIN_QUEUE_READ_ISR );
        BaseType_t xtask = pdFALSE;

        if( xQueueReceiveFromISR( controlQueueHandle, message_ptr, &xtask ) != pdPASS ) {
            return false;
        }
        // message now contains new info
        //dbgEvent
        //dbgEvent( CHAIN_QUEUE_READ_SUCCESS );
        dbgEvent(0x04);
        return true;
    }
    else {
        //dbgEvent
        //dbgEvent( SENSOR_THREAD_QUEUE_READ_NOT_ISR );
        if( xQueueReceive( controlQueueHandle, message_ptr, portMAX_DELAY ) != pdPASS ) {
            return false;
        }
        // message now contains new info
        //dbgEvent
        //dbgEvent( CHAIN_QUEUE_READ_SUCCESS );
        dbgEvent(0x06);
        return true;
    }
}

void sendControlMessage( ControlMessage_t* message_ptr ) {
    BaseType_t xHigherPriorityTaskWoken;
    xHigherPriorityTaskWoken = pdFALSE;

    //dbgEvent( CHAIN_QUEUE_SEND_ENTER );
    if ( HwiP_inISR() ) {
        //dbgEvent( CHAIN_QUEUE_SEND_ISR );
        if( xQueueSendFromISR( controlQueueHandle, message_ptr,  &xHigherPriorityTaskWoken ) != pdPASS ) {
            // Queue is full, fail
            return;
        }

        //dbgEvent( SENSOR_THREAD_QUEUE_SEND_ISR_SUCCESS );
    }
    else {
        //dbgEvent( CHAIN_QUEUE_SEND_NOT_ISR );
        if( xQueueSend( controlQueueHandle, message_ptr, portMAX_DELAY ) != pdPASS ) {
            //dbgEvent( FATAL_CHAIN_QUEUE_SEND );
            return;
        }
    }
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );

    //dbgEvent( CHAIN_QUEUE_SEND_SUCCESS );
}
