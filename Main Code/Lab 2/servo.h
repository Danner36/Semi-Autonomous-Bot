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

/**
 * Rotate servo
 *
 * pulse - length of pulse
 */
void move_servo(int pulse_period);

/**
 * Alternative rotate servo
 *
 * degree - degree the servo should be moved to
 */
void move_servo2(int degree);

/**
 * Set the PWM period
 *
 * degree - chooses 0, 45, 90, 135, or 180 degrees to move servo to
 */
int setPeriod(int degree);
