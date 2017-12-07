#include "open_interface.h"
#include "uart.h"

//Average floor color values
#define FLOOR_MIN 1500
#define FLOOR_MAX 2150

//Average boundary line color values
#define BOUND_MIN 2600
#define BOUND_MAX 2900

///Update cliff sensor variables and check if any are positive
/**
 * The 4 cliff sensors are each checked individually.
 * Return 0 if they are all clear.
 * Return 1 if not, meaning there is a cliff in front of the bot.
 */
char checkAnyCliff(oi_t* sensor_data);

///Update cliff signals and check if the bot has hit the boundary
/**
 * Each cliff signal is read individually into a small array.
 * The array is checked for if any signal reads the color white (the border color).
 * Return 0 if all signals are clear.
 * Return 1 if white is detected, meaning the bot has reached the boundary.
 */
char checkBoundary(oi_t* sensor_data);
