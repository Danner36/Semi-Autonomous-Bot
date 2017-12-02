#include <inc/tm4c123gh6pm.h>
#include "timer.h"

/**
 * Initialize USART1 to a given baud rate
 */
void uart_init();

/**
 * Blocking call to receive over uart1.
 * Returns char with data.
 */
char uart_receive();

/**
 * Blocking call that sends 1 char over UART 1
 */
void uart_sendChar(char data);
