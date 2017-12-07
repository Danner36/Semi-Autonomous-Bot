#include <stdio.h>
#include <inc/tm4c123gh6pm.h>
#include "timer.h"

#define PERIOD 320000 //Original - 320,000
#define CW 7000 //Original - 16,000
#define CCW 34500 //Original - 32,000
#define MID 20000 //Original - 24,000
#define CW_45 13500 //
#define CCW_135 27000 //
#define DEGREE 153

///Rotate servo
/**
 * Set the period of PWM correctly as adjusted for particular bots.
 *
 * @param pulse - length of pulse
 */
void move_servo(int pulse_period);
