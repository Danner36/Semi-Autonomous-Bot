#include <stdio.h>
#include "sonar.h"
#include "stdbool.h"
#include "driverlib/interrupt.h"
#include <inc/tm4c123gh6pm.h>

///Initialize GPIO Port B for Servos and Sonar readings
/*
 * Pin B5 is used for the servo and Pin PB3 is used for Sonar.
 * Alternate digital functions are used.
 */
void init_PortB_Servo();

///Configures TIMER 3B and TIMER 1B
/*
 * Timers are set to be 16-Bit, up and down respectively, and in edge time / period modes respectively.
 * Timer 3B is used for Sonar readings and Timer 1B uses PWM for Servos
 */
void init_timers();

/**
 * Initialize Port B and Timers
 * Calls two sub-functions for simplicity
 */
void portB_init();
