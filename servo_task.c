#include "servo_task.h"

static Timer_Handle timer;

void init_servo_thread(Timer_Handle servoTimer) {
    //dbgEvent
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

    retc |= pthread_attr_setstacksize(&attrs, SERVOTHREADSIZE);
    if (retc != 0) {
        //fail
    }

    priParam.sched_priority = PRIORITY;
    pthread_attr_setschedparam(&attrs, &priParam);

    retc = pthread_create(&thread, &attrs, servo_task, NULL);
    if (retc != 0) {
        // fail
    }

    timer = servoTimer;
    //dbgEvent() SERVO TASK SUCCESSFULLY CREATED
    dbgEvent(0x60);
}

void *servo_task() {
    static uint16_t pwmPeriod = 3000;
    static uint16_t duty = 600;
    static PWM_Handle pwm = NULL;
    static PWM_Params params;

    PWM_init();

    PWM_Params_init(&params);
    params.dutyUnits = PWM_DUTY_US;
    params.dutyValue = duty;
    params.periodUnits = PWM_PERIOD_US;
    params.periodValue = pwmPeriod;
    pwm = PWM_open(CONFIG_PWM_0, &params);
    if (pwm == NULL) {
        // PWM did not open
        while (1);
    }

    PWM_start(pwm);

    while (1) {
        dbgEvent(0x62);
        update_servo_FSM(pwm, timer);
        dbgEvent(0x64);
    }
}
