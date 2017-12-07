#include <inc/tm4c123gh6pm.h>
#include "timer.h"

///Initialize USART1
/**
 * Uses GPIO Port B, Pin 1B.
 * Sets baud rate.
 */
void uart_init();

///Blocking call to receive over uart1.
/**
 * Waits in a while loop for received data.
 * Returns char with data just received.
 */
char uart_receive();

///Blocking call that sends a single char over UART 1
/**
 * @param data - data to transmit
 */
void uart_sendChar(char data);
