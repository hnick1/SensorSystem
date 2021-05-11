/*
 * timer500.c
 *
 *  Created on: Feb 9, 2021
 *      Author: drew1
 */

#include "timer500.h"
Timer_Handle timer500Setup(void *arg0)
{
    Timer_Handle timer1;
    Timer_Params params;

    /* Call driver init functions */
    Timer_init();
    /*
     * Setting up the timer in continuous callback mode that calls the callback
     * function every 500000 microseconds, or 500 ms.
     */
    Timer_Params_init(&params);
    params.period = TIMER500_LENGTH;
    params.periodUnits = Timer_PERIOD_US;
    params.timerMode = Timer_ONESHOT_CALLBACK;
    params.timerCallback = timerCallback500;

    timer1 = Timer_open(CONFIG_TIMER_2, &params);

    if (timer1 == NULL) {
        /* Failed to initialized timer */
        while (1) {
            //Debug
            //dbgEvent(FAILURE_TO_INITIALIZE_TIMER500);
        }
    }

    //if (Timer_start(timer1) == Timer_STATUS_ERROR) {
        /* Failed to start timer */
        //while (1) {
            //Debug
            //dbgEvent(FAILURE_TO_START_TIMER500);
        //}
    //}

    return timer1;
}


void timerCallback500(Timer_Handle myHandle, int_fast16_t status) {
    dbgEvent(0x6E);
    static ServoMessage_t message_out;
    message_out.angle = 0;
    message_out.message_type = SERVO_TIMER_CALLBACK;
    sendServoMessage(&message_out);
}
