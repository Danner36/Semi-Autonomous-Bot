#ifndef SERVO_H_
#define SERVO_H_

#include <stdio.h>
#include <inc/tm4c123gh6pm.h>
#include "timer.h"

#define PERIOD 320000 //Original - 320,000
#define CW 7000 //Original - 16,000
#define CCW 34500 //Original - 32,000
#define MID 20000 //Original - 24,000
#define CW_45 13500 //
#define CCW_135 27000 //

#endif /* SERVO_H_ */

void init_PortB();

void clock_timer_init(void);

int setPeriod(int degree);

void oneWay();

void move_servo(int degree);

void move_servo2(pulse_period);
