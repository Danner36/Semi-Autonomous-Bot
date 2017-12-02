#include "init.h"
#include "uart.h" //Lab 5
#include "wifi.h"
#include "adc.h" //Lab 6
#include "sonar.h" //Lab 7
#include "servo.h" //Lab 8
#include <string.h>
#include <inc/tm4c123gh6pm.h>
#include "driverlib/interrupt.h"
#include <stdio.h>
#include <math.h>

#define M_PI 3.14159265358979323846

/**
 * Collect data on surroundings in 180-degree scan
 */
void scan();

/**
 * Reset all variables and return the servo to its starting position at 0 degrees
 */
void reset();

/**
 * Linear Width calculation
 *
 * angle - angular width of object as read by scanner
 * distance - distance between scanner and target object
 */
float calculateLinearWidth(int angle, float distance);

/**
 * Collect data from both Sonar and IR sensors.
 */
void collectData();

/*
 * Calculates and returns the average of the passed in array.
 *
 * array - an array of integers to average
 */
int getAverge(int array[]);

/*
 * Calculates the conversion from IR input to distance.
 *
 * result - distance in centimeters
 */
float getIRtoDis(float result);

/*
 * Resets temporary variables.
 */
void resetTempVars();

/*
 * Sends current information to Putty.
 *
 * i - degrees
 * linearWidth - actual width of object most recently scanned
 */
void sendData(int i, float distance, float linearWidth);

/*
 * Sends Header information to Putty (only needed for Lab 9)
 */
void sendHeader();
