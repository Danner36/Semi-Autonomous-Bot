#include "open_interface.h"
#include "cliffSensor.h"
#include "uart.h"

//Preset speeds
#define SPD_1 250
#define SPD_2 200
#define SPD_3 150
#define SPD_4 100
#define SPD_5 50
#define SPD_6 25

///Move forward a certain distance
/**
 * @param sensor - open interface sensor pointer
 * @param centimeters - how far the bot will travel before stopping
 * @param spd - speed, how fast the motors will turn
 *
 * Sends a char to UART, 0 - 4, depending on if the bot encountered anything while moving.
 *
 * Return 0 if clear.
 * Return 1 if left bumper hit.
 * Return 2 if right bumper hit.
 * Return 3 if bot is in front of a cliff.
 * Return 4 if bot hit the boundary.
 */
char move_forward(oi_t *sensor, int centimeters, int speed);

///A check of all obstacles detectable by the open interface.
/**
 * Checks for left bumper, right bumper, and cliff sensors.
 * Run at the beginning of forward movement as an initial check.
 *
 * @param sensor - open interface sensor pointer
 */
char checkAll();

///Turn counterclockwise a certain number of degrees
/**
 * The wheels are set to turn in opposite directions to cause the turn.
 *
 * @param sensor - an open interface sensor pointer
 * @param degrees - how far the bot will turn
 * @param speed - how fast to turn
 */
void turn_ccw(oi_t *sensor, int degrees, int speed);

///Turn clockwise a certain number of degrees
/**
 * The wheels are set to turn in opposite directions to cause the turn.
 *
 * @param sensor - an open interface sensor pointer
 * @param degrees - how far the bot will turn
 * @param speed - how fast to turn
 */
void turn_cw(oi_t *sensor, int degrees, int speed);

///Move in reverse a certain distance
/**
 *
 * Similar to the function for moving forward.
 * While moving back, the cliff signals are checked to make sure the bot doesn't accidentally back up over the boundary.
 * Sends a 7 through UART to let the driver know the reverse completed successfully.
 * Sends a 4 if the boundary was hit.
 *
 * @param sensor - an open interface sensor pointer
 * @param centimeters - how far the bot will move backwards
 * @param spd - the speed at which the bot will move (speed of the motors)
 */
void move_backward(oi_t *sensor, int centimeters, int speed);

///Stop the bot by disabling its motors
/**
 * Set the wheels' power to 0.
 */
void stop();
