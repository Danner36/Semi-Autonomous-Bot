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

//PI as used in linear width calculations
#define M_PI 3.14159265358979323846

///Collect data on surroundings in 180-degree scan
/**
 * The scan stops every 2 degrees to make an IR and Sonar reading.
 * The readings are recorded and then the scan continues.
 * While scanning, data is interpreted by the readings to try to tell if the scan has encountered objects within 100 centimeters of the scanner.
 * Scan results are transmitted via UART as objects are detected.
 */
void scan();

///Reset scan
/**
 * Used before the scan begins.
 * Resets variables used by the scanner.
 * Turns the servo to the 0-degree position.
 */
void reset();

///Linear Width calculation
/**
 * Width = distance * sin(angle in radians divided by two)
 *
 * @param angle - angular width of object as read by scanner
 * @param distance - distance between scanner and target object
 *
 * Returns a linear width in centimeters.
 */
float calculateLinearWidth(int angle, float distance);

///Collect data from both Sonar and IR sensors.
/**
 * Runs both functions for sending and receiving Sonar/IR signals.
 */
void collectData();

///Calculates the conversion from IR input to distance.
/*
 * Distance = (1.682 * 10^7) / ((IR reading) ^ 500/239) + 10
 *
 * @param result - the raw IR reading
 *
 * Returns a distance in centimeters.
 */
float getIRtoDis(float result);

///Resets temporary variables.
/*
 * Resets certain variables which are re-used 90 times during the scan.
 * Not to be confused with the total reset function.
 */
void resetTempVars();

///Sends current information via UART.
/*
 * Data on the most recently scanned object is transmitted char-by-char to UART.
 * Data is formatted in a compact line with angle, distance, and linear width.
 *
 * @param i - degree of scanned object relative to the front of the scanner
 * @param distance - distance in centimeters
 * @param linearWidth - actual width of object most recently scanned
 */
void sendData(int i, float distance, float linearWidth);
