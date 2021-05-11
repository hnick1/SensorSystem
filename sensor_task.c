#include "sensor_task.h"

static mqd_t QHandle;

void init_sensor_thread( MQTTClient_Handle handle ) {
    //dbgEvent( SENSOR_TASK_CREATE_ENTER );
    pthread_t thread;
    pthread_attr_t attrs;
    struct sched_param priParam;
    int retc;
    int detachState;

    pthread_attr_init(&attrs);

    detachState = PTHREAD_CREATE_DETACHED;
    retc = pthread_attr_setdetachstate(&attrs, detachState);
    if (retc != 0) {
        // fail
    }

    retc |= pthread_attr_setstacksize(&attrs, SENSORTHREADSTACKSIZE);
    if (retc != 0) {
        //fail
    }

    priParam.sched_priority = PRIORITY;
    pthread_attr_setschedparam(&attrs, &priParam);

    retc = pthread_create(&thread, &attrs, sensor_task, NULL);
    if (retc != 0) {
        //fail
    }

    QHandle = handle;

    //dbgEvent( SENSOR_TASK_CREATE_SUCCESS );
}

void* sensor_task() {
    //dbgEvent( SENSOR_TASK_INIT );
    // initialization code
    SensorMessage_t message;

    //dbgEvent( SENSOR_TASK_PRE_WHILE );
    while(1) {
        //dbgEvent( SENSOR_TASK_READ_ATTEMPT );
        // Make one subroutine call to receive message from sensor_thread_queue
        readSensorMessage( &message );
        // Send message (by reference) to FSM in sensor_thread_state
        //dbgEvent( SENSOR_TASK_READ_SUCCESS );
        update_FSM( &message, QHandle );
        //dbgEvent( SENSOR_TASK_POST_FSM_UPDATE );

        // do nothing if queue is empty
    }
}
