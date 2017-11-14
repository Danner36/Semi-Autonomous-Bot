#ifndef SONAR_H_
#define SONAR_H_

#include <stdio.h>
#include "timer.h"
#include "lcd.h"
#include "stdbool.h"
#include "driverlib/interrupt.h"
#include <math.h>


void TIMER3B_Handler(void);

void send_pulse(void);

float ping_read(void);


#endif
