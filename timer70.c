/*
 * timer70.h
 *
 *  Created on: Feb 9, 2021
 *      Author: drew1
 *
 *  Edited Feb 9 by Addison Ferrari
 */


#include "timer70.h"
#include "sensor_thread_queue.h"

static ADC_Handle   adc;
static ADC_Params   adc_params;
static int_fast16_t res;

void timer70Setup()
{
    //////////////////////////////////////////////////////////////////////////////////
    // init timer
    Timer_Handle timer0;
    Timer_Params params;

    /* Call driver init functions */
    //Timer_init();
    /*
     * Setting up the timer in continuous callback mode that calls the callback
     * function every 70000 microseconds, or 70 ms.
     */
    Timer_Params_init(&params);
    params.period = TIMER70_LENGTH;
    params.periodUnits = Timer_PERIOD_US;
    params.timerMode = Timer_CONTINUOUS_CALLBACK;
    params.timerCallback = timerCallback70;

    //timer0 = Timer_open(CONFIG_TIMER_3, &params);

    //if (timer0 == NULL) {
        /* Failed to initialized timer */
        //dbgEvent(FATAL_TIMER70_INIT);
    //}

    //if (Timer_start(timer0) == Timer_STATUS_ERROR) {
        /* Failed to start timer */
        //dbgEvent(FATAL_TIMER70_START);
    //}

    //////////////////////////////////////////////////////////////////////////////////
    // init ADC
    //ADC_init();
    //ADC_Params_init(&adc_params);
    //adc = ADC_open(CONFIG_ADC_0, &adc_params);
}


void timerCallback70(Timer_Handle myHandle, int_fast16_t status)
{
    //dbgEvent( ENTER_TIMER70_CALLBACK );

    static SensorMessage_t message;
    uint16_t adcValue;
    uint32_t adcMicroVolt;
    int millimeters;
    //Read IR sensor and send message to sensor_thread in the sensor_thread_queue

    //if( adc == NULL ){
        // fail
        //dbgEvent(FAILURE_TO_START_ADC);
    //}

    // Read ADC
    // Blocking mode conversion
    //res = ADC_convert( adc, &adcValue );

    //if ( res == ADC_STATUS_SUCCESS ) {

        //adcMicroVolt = ADC_convertRawToMicroVolts(adc, adcValue);

        //if( adcMicroVolt < MIN_RANGE || adcMicroVolt > MAX_RANGE ) {
          //  millimeters = INVALID;
        //}
        //else if( adcMicroVolt > SPLIT ) {
          //  millimeters = B1 - (NUM1*adcMicroVolt)/DEN1;
        //}
        //else {
          //  millimeters = B2 - (NUM2*adcMicroVolt)/DEN2;
        //}

        // send value to sensor_thread_queue
        //message.message_type = SENSOR_TIMER70_MESSAGE;
        //message.value = millimeters;
        //sendSensorMessage( &message );
        //dbgEvent(COMPLETED_TIMERCALLBACK70);
    //}
    //else {
        // fail
        //dbgEvent(FAILURE_TO_READ_ADC);

    //}

}
