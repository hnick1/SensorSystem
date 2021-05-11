#include "sensor_thread_state.h"

void update_FSM( SensorMessage_t* mes, mqd_t handle ) {
    static eSensorState_t FSM_state = INIT_AVERAGE;
    static int sent_count = 0;

    //dbgEvent( SENSOR_THREAD_STATE_ENTER );

    static int sensorTotal;
    static int sensorCount;
    static int average;
    static unsigned int hash;
    static int return_size;
    static int i;
    static msgQueue message;
    message.event = 0;

    switch( FSM_state ) {
        case INIT_AVERAGE:
            //dbgEvent( SENSOR_THREAD_STATE_INIT );

            sensorTotal = 0;
            sensorCount = 0;
            average = 0;
            if ( mes->message_type == SENSOR_TIMER500_MESSAGE ) {
                //dbgEvent( SENSOR_THREAD_STATE_INIT_500 );
                FSM_state = UPDATE_AVERAGE;
            }
            break;
        // end case INIT
        case UPDATE_AVERAGE:
            //dbgEvent( SENSOR_THREAD_STATE_UPDATE );

            if ( mes->message_type == SENSOR_TIMER70_MESSAGE ) {
                //dbgEvent( SENSOR_THREAD_STATE_UPDATE_70 );

                sensorTotal += mes->value;
                sensorCount++;

                return_size = snprintf( message.topic, TOPIC_STRING_LENGTH, "cc32xx/IRDataSend");
                message.topic[return_size] = 0;
                return_size = snprintf( message.payload, PAYLOAD_STRING_LENGTH, "{ \"Count\" : %d , \"Value\" : %d ,  ",sent_count,  mes->value  );
                sent_count++;
                hash = string_hash( message.payload );
                return_size = snprintf( message.payload, PAYLOAD_STRING_LENGTH, "%s\"Hash\" : %u }", message.payload, hash );

                message.payload[return_size] = 0;
                message.payload_size = return_size;

                //dbgEvent( SENSOR_THREAD_STATE_UPDATE_70_SEND );
                message.event = 0; //APP_MQTT_PUBLISH;
                //return_size = mq_send( handle, (char*)&message, sizeof(struct msgQueue), 0);

                for( i = 0 ; i < PAYLOAD_STRING_LENGTH ; i++ ) {
                    message.payload[i] = 0;
                }

                //dbgEvent( SENSOR_THREAD_STATE_UPDATE_70_POST_SEND );
            }
            else if( mes->message_type == SENSOR_TIMER500_MESSAGE) {
                //dbgEvent( SENSOR_THREAD_STATE_UPDATE_500 );

                if ( sensorCount == 0 ) {
                    average = 0;
                }
                else {
                    average = (int)(sensorTotal / sensorCount);
                }


                return_size = snprintf( message.topic, TOPIC_STRING_LENGTH, "cc32xx/IRDataSend");
                message.topic[return_size] = 0;
                return_size = snprintf( message.payload, PAYLOAD_STRING_LENGTH, "{ \"Average\" : %d , \"Count\" : %d ,\"Time\" : %d , ", average,sent_count, mes->value );
                sent_count++;
                hash = string_hash( message.payload );
                return_size = snprintf( message.payload, PAYLOAD_STRING_LENGTH, "%s\"Hash\" : %u }", message.payload, hash );

                message.payload[return_size] = 0;
                message.payload_size = return_size;

                //dbgEvent( SENSOR_THREAD_STATE_UPDATE_500_SEND );
                // send string to UART
                //sendUartMessage( &to_send );

                //return_size = mq_send( handle, (char*)&message, sizeof(struct msgQueue), 0);

                for( i = 0 ; i < PAYLOAD_STRING_LENGTH ; i++ ) {
                    message.payload[i] = 0;
                }

                //dbgEvent( SENSOR_THREAD_STATE_UPDATE_500_POST_SEND );
                FSM_state = INIT_AVERAGE;
            }
            break;
        // end case UPDATE
    } // end switch
}
