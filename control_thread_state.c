#include "control_thread_state.h"

void update_control_FSM(ControlMessage_t mes, mqd_t handle) {
    static controlState_t currControlState = UPDATE_SERVO;
    static ServoMessage_t servoMes_out;
    static ToFMessage_t tofMes_out;
    static msgQueue mqttMes_out;
    static uint16_t duty = MIN_DUTY;
    static uint16_t dutyInc = DUTY_INC;
    static uint16_t currAngle = 0;
    static int return_size;

    switch(currControlState) {
    case UPDATE_SERVO:
        if (mes.message_type == SERVO_ROTATE_DONE) {
            currControlState = UPDATE_SENSOR;
            tofMes_out.message_type = TOF_START_READ;
            sendToFMessage(&tofMes_out);
        }
        break;
    case UPDATE_SENSOR:
        if (mes.message_type == SENSOR_READ_DONE) {
            currAngle = (duty - DUTY_TO_DEGREES_SUB) / DUTY_TO_DEGREES_DIV;
            // mqtt publish goes in here
            mqttMes_out.event = 0;
            return_size = snprintf(mqttMes_out.topic, TOPIC_STRING_LENGTH, "Sensor/Data");
            mqttMes_out.topic[return_size] = 0;
            return_size = snprintf(mqttMes_out.payload, PAYLOAD_STRING_LENGTH, "{ \"Distance\" : %s , \"Angle\" : %d }", mes.reading, currAngle);
            mqttMes_out.payload[return_size] = 0;
            mqttMes_out.payload_size = return_size;
            return_size = mq_send(handle, (char*)&mqttMes_out, sizeof(struct msgQueue), 0);

            //servoMes_out.angle = angle;
            duty = duty + dutyInc;
            servoMes_out.angle = duty;
            servoMes_out.message_type = SERVO_ROTATE;
            if (duty == MIN_DUTY || duty == MAX_DUTY) {
                dutyInc = -dutyInc;
            }
            currControlState = UPDATE_SERVO;
            sendServoMessage(&servoMes_out);

            // mqtt publish goes in here
            /*
            mqttMes_out.event = 0;
            return_size = snprintf(mqttMes_out.topic, TOPIC_STRING_LENGTH, "Sensor/Data");
            mqttMes_out.topic[return_size] = 0;
            return_size = snprintf(mqttMes_out.payload, PAYLOAD_STRING_LENGTH, "{ \"Distance\" %s mm , \"Angle\" %d degrees }", mes.reading, currAngle);
            mqttMes_out.payload[return_size] = 0;
            mqttMes_out.payload_size = return_size;
            return_size = mq_send(handle, (char*)&mqttMes_out, sizeof(struct msgQueue), 0);
            */
        }
        break;
    default:

        break;
    }
}
