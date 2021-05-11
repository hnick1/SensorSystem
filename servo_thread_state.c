#include "servo_thread_state.h"

void update_servo_FSM(PWM_Handle pwm, Timer_Handle time) {
    static servoState_t currServoState = IDLE;
    static uint16_t duty = 600;
    static uint16_t dutyInc = 10;
    static uint16_t nextDuty;
    static ServoMessage_t message_in;
    static ControlMessage_t message_out;
    readServoMessage(&message_in);

    switch (currServoState) {
    case IDLE:
        if (message_in.message_type == SERVO_ROTATE) {
            dbgEvent(0x66);
            currServoState = TURN;
            nextDuty = message_in.angle;
            Timer_start(time);
        }
        break;
    case TURN:
        dbgEvent(0x68);
        if (message_in.message_type == SERVO_TIMER_CALLBACK) {
            dbgEvent(0x6A);
            if (duty == nextDuty) {
                message_out.message_type = SERVO_ROTATE_DONE;
                message_out.reading[0] = '\0';
                sendControlMessage(&message_out);
                currServoState = IDLE;
            }
            else {
                Timer_start(time);
            }
            duty = duty + dutyInc;
            PWM_setDuty(pwm, duty);
            if (duty == 2400 || duty == 600) {
                dutyInc = -dutyInc;
            }
        }
        break;
    default:
        break;
    }
}
