#include <inc/tm4c123gh6pm.h>
#include "lcd.h"

///Initialize sample sequencing and wait for a conversion response
/*
 * ADC 0 Sample sequencer is activated.
 * The function enters a while loop to wait for the conversion to finish.
 * Then it returns the result as an int.
 */
int adc_Read();

///Initialize everything necessary for ADC
/*
 * Initializes individual bits in several registers manually.
 * Uses Port D, Pin 0 and enables it as an analog alternate function.
 */
void adc_init();
