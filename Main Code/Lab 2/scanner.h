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

//Function headers
void scan();

void reset();

float calculateLinearWidth(int angle, float distance);

void collectData();

int getAverge(int array[]);

float getIRtoDis(float result);

int getSmallest(int array[]);

int getSmallestIndex(int array[]);

void initialize();

void resetTempVars();

void sendData(int i, float linearWidth);

void sendHeader();
