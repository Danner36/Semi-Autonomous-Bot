#include <stdio.h>
#include "sonar.h"
#include "stdbool.h"
#include "driverlib/interrupt.h"
#include <inc/tm4c123gh6pm.h>

/*
 * Initialize GPIO Port B for Servos and Sonar readings
 * SERVO - PB 5, SONAR - PB3
 */
void init_PortB_Servo();

/*
 * Configures TIMER 3B and TIMER 1B
 */
void init_timers();

/**
 * Initialize Port B and Timers
 * Calls two sub-functions for simplicity
 */
void portB_init();
