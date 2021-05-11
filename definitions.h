#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <stdio.h>
#include <stdint.h>

//////////////////////////////////////////////////////////////////////////////////////////////
// SENSOR TASK
typedef enum eSensorState_t {
    INIT_AVERAGE,
    UPDATE_AVERAGE
} eSensorState_t;

//////////////////////////////////////////////////////////////////////////////////////////////
// SENSOR_THREAD_QUEUE
#define SENSOR_TIMER70_MESSAGE 1
#define SENSOR_TIMER500_MESSAGE 2
typedef struct SensorMessage_t {
    char message_type;
    int  value;
} SensorMessage_t;


//////////////////////////////////////////////////////////////////////////////////////////////
// SENSOR_THREAD_STATE
//#define MAX_SENSOR_STRING_SIZE 50

//////////////////////////////////////////////////////////////////////////////////////////////
// QUEUE_THREAD
#define MAX_STRING_SIZE 50
typedef struct UartMessage_t {
    int size;
    char string[ MAX_STRING_SIZE ];
} UartMessage_t;
#define QUEUE_LENGTH 3
#define QUEUE_ITEM_SIZE sizeof( UartMessage_t )

//////////////////////////////////////////////////////////////////////////////////////////////
// THREADS


//////////////////////////////////////////////////////////////////////////////////////////////
// CHAIN
typedef struct ChainMessage_t {
    int count;
    unsigned int hash;
} ChainMessage_t;

/////////////////////////////////////////////////////////////////////////////////////////////
//TOF
#define TOF_START_READ 1
typedef struct ToFMessage_t {
    char message_type;
} ToFMessage_t;

///////////////////////////////////////////////////////////////////////////////////////////////
// SERVO
#define SERVO_ROTATE 1
#define SERVO_TIMER_CALLBACK 2
typedef struct ServoMessage_t {
    char message_type;
    uint16_t angle;
} ServoMessage_t;

//////////////////////////////////////////////////////////////////////////////////////////////
#define SERVO_ROTATE_DONE 1
#define SENSOR_READ_DONE 2
#define READING_SIZE 5
typedef struct ControlMessage_t {
    char message_type;
    char reading[READING_SIZE];
} ControlMessage_t;

/////////////////////////////////////////////////////////////////////////////////////////////
// STATS
typedef enum eStatsType_t {
    STATS_PUBLISH,
    STATS_RECEIVE,
    STATS_MISSED,
    STATS_CORRUPTED,
    STATS_SEND
} eStatsType_t;

typedef struct StatsMessage_t {
    eStatsType_t type;
} StatsMessage_t;

/////////////////////////////////////////////////////////////////////////////////////////////
typedef struct version2_t {
    int totalNumMes;
    int messagesPerSecond;
    int avgSensReadings;
    int sendMes;
    unsigned int hash;
    int time;
    int value;
} version2_t;

#define AVG_ERROR -2
#endif
