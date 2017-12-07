#include "movement.h"
#include "scanner.h" //Lab 9


///Manage input from an exterior controller
/**
 * Input given by UART is interpreted as a keystroke and the proper action is performed by the bot.
 * The bot can turn, move forward, reverse, scan, or play music through this function.
 * The movement and scanner files are referenced through this function.
 */
char controller_input(unsigned char input,  oi_t *sensor);
