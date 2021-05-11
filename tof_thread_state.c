#include "tof_thread_state.h"

void update_tof_FSM(char sensorReading) {
    static tofState_t currToFState = WAIT;
    static ToFMessage_t message_in;
    static ControlMessage_t message_out;
    static int index = 0;
    static int i = 0;

    switch (currToFState) {
    case WAIT:
        readToFMessage(&message_in);
        index = 0;
        for (i = 0; i < 5; i++) {
            message_out.reading[i] = 0;
        }
        if (message_in.message_type == TOF_START_READ) {
            currToFState = INIT_DATA;
        }
        break;
    case INIT_DATA:
        if (sensorReading == DATA_END) {
            message_out.reading[0] = 0;
            message_out.reading[1] = 0;
            message_out.reading[2] = 0;
            message_out.reading[3] = 0;
            message_out.reading[4] = 0;
            currToFState = APPEND_DATA;
            index = 0;
        }
        break;
    case APPEND_DATA:
        dbgEvent(FSM_APPEND_DATA_STATE);
        if (sensorReading == DATA_END || index == 4) {
            currToFState = WAIT;
            message_out.message_type = SENSOR_READ_DONE;
            sendControlMessage(&message_out);
        }
        else {
            message_out.reading[index] = sensorReading;
            index++;
        }
        break;
    default:
        break;
    }
}
