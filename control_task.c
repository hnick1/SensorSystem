#include "control_task.h"

static mqd_t QHandle;

void init_control_thread( MQTTClient_Handle handle ) {
    //dbgEvent(TOF_PREINIT);
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

    retc |= pthread_attr_setstacksize(&attrs, CONTROLTHREADSTACKSIZE);
    if (retc != 0) {
        //fail
    }

    priParam.sched_priority = CONTROLPRIORITY;
    pthread_attr_setschedparam(&attrs, &priParam);

    retc = pthread_create(&thread, &attrs, control_task, NULL);
    if (retc != 0) {
        //dbgEvent( FATAL_CHAIN_INIT );
        // PUT A NEW DEBUG EVENT HERE SOON
    }

    QHandle = handle;

   // dbgEvent(TOF_THREAD_CREATED);
}

void *control_task() {
    static ServoMessage_t message_out;
    static ControlMessage_t message_in;

    message_out.angle = 600;
    message_out.message_type = SERVO_ROTATE;
    sendServoMessage(&message_out);

    while (1) {
        readControlMessage(&message_in);
        update_control_FSM(message_in, QHandle);
    }
}
