#include "sensor_thread_queue.h"

static QueueHandle_t sensorQueueHandle = NULL;

void createSensorQueue() {
    //dbgEvent( SENSOR_THREAD_QUEUE_CREATE_ENTER );

    sensorQueueHandle = xQueueCreate( SENSOR_QUEUE_LENGTH, SENSOR_QUEUE_ITEM_SIZE );

    if (sensorQueueHandle == NULL) {
       // fail
    }

    //dbgEvent( SENSOR_THREAD_QUEUE_CREATE_SUCCESS );
}

bool readSensorMessage( SensorMessage_t* message_ptr ) {
    //dbgEvent( SENSOR_THREAD_QUEUE_READ_ENTER );
    if ( HwiP_inISR() ) {
        //dbgEvent( SENSOR_THREAD_QUEUE_READ_ISR );
        BaseType_t xtask = pdFALSE;

        if( xQueueReceiveFromISR( sensorQueueHandle, message_ptr, &xtask ) != pdPASS ) {

            return false;
        }
        // message now contains new info
        //dbgEvent( SENSOR_THREAD_QUEUE_READ_ISR_SUCCESS );
        return true;
    }
    else {
        //dbgEvent( SENSOR_THREAD_QUEUE_READ_NOT_ISR );
        if( xQueueReceive( sensorQueueHandle, message_ptr, portMAX_DELAY ) != pdPASS ) {
            return false;
        }
        // message now contains new info
        //dbgEvent( SENSOR_THREAD_QUEUE_READ_NOT_ISR_SUCCESS );
        return true;
    }
}

void sendSensorMessage( SensorMessage_t* message_ptr ) {
    BaseType_t xHigherPriorityTaskWoken;
    xHigherPriorityTaskWoken = pdFALSE;

    //dbgEvent( SENSOR_THREAD_QUEUE_SEND_ENTER );
    if ( HwiP_inISR() ) {
        //dbgEvent( SENSOR_THREAD_QUEUE_SEND_ISR );

        if( xQueueSendFromISR( sensorQueueHandle, message_ptr,  &xHigherPriorityTaskWoken ) != pdPASS ) {
            // Queue is full, fail
            return;
        }

        //dbgEvent( SENSOR_THREAD_QUEUE_SEND_ISR_SUCCESS );
    }
    else {
        //dbgEvent( SENSOR_THREAD_QUEUE_SEND_NOT_ISR );

        if( xQueueSend( sensorQueueHandle, message_ptr, portMAX_DELAY ) != pdPASS ) {
            // Queue is full, fail
            return;
        }
        //dbgEvent( SENSOR_THREAD_QUEUE_SEND_NOT_ISR_SUCCESS );
    }
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}
