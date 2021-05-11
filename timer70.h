/*
 * timer70.h
 *
 *  Created on: Feb 9, 2021
 *      Author: drew1
 *
 *  Edited Feb 9 by Addison Ferrari
 */

#ifndef TIMER70_H_
#define TIMER70_H_
#define TIMER70_LENGTH 70000

// not sure if correct,
#define ADC_SAMPLE_COUNT (10)

// conversion constants to millimeters
#define NUMERATOR 94.62
#define SUBTRACTOR 1692*5
#define VCC 5000000

#define MIN_RANGE 220000
#define MAX_RANGE 900000
#define SPLIT 416000
#define INVALID   -1
#define NUM1 400
#define DEN1 520000
#define B1 900
#define NUM2 700
#define DEN2 160000
#define B2 2400

#include <stddef.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/Timer.h>
#include <ti/drivers/ADC.h>

/* Board Header file */
#include "ti_drivers_config.h"

#include "definitions.h"
#include "debug.h"


void timer70Setup();
/* Callback used for toggling the LED. */
void timerCallback70(Timer_Handle myHandle, int_fast16_t status);





#endif
