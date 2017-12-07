#include <stdio.h>
#include "timer.h"
#include "lcd.h"
#include "stdbool.h"
#include "driverlib/interrupt.h"
#include <math.h>

///Interrupt function for Timer 3B.
/**
 * Records rising and falling edges.
 */
void TIMER3B_Handler(void);

///PWM pulse for sending out Sonar.
/**
 * Send out pulse and then prepare to receive it back.
 * Inserts a tiny delay between sending and receiving.
 */
void send_pulse(void);

///Wait for a return pulse from previously-sent sonar.
/**
 * Can only be used after send pulse function.
 * Adjusts its return value in case of overflow.
 * Returns the calculated distance in centimeters.
 */
float ping_read(void);
