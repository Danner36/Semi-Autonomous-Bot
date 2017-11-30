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

/**
 *
 * Move forward a certain distance
 *
 * sensor - open interace sensor pointer
 * centimeters - how far the bot will travel before stoping
 * spd - speed, how fast the motors will turn
 *
 * returns a number for any obstacle encountered:
 * 0 = Clear
 * 1 = Left Bumper
 * 2 = Right Bumper
 * 3 = Cliff
 * 4 = Boundary
 *
 */
char move_forward(oi_t *sensor, int centimeters, int speed);

/**
 * A check of all obstacles detectable by the open interface.
 * Run at the beginning of forward movement as an initial check.
 *
 * sensor - open interface sensor pointer
 */
char checkAll();

/**
 * Turn counterclockwise a certain number of degrees slowly
 *
 * sensor - an open interface sensor pointer
 * degrees - how far the bot will turn
 * speed - how fast to turn
 */
void turn_ccw(oi_t *sensor, int degrees, int speed);

/**
 * Turn clockwise a certain number of degrees slowly
 *
 * sensor - an open interface sensor pointer
 * degrees - how far the bot will turn
 * speed - how fast to turn
 */
void turn_cw(oi_t *sensor, int degrees, int speed);

/**
 * Move in reverse a certain distance
 *
 * sensor - an open interface sensor pointer
 * centimeters - how far the bot will move backwards
 * spd - the speed at which the bot will move (speed of the motors)
 */
void move_backward(oi_t *sensor, int centimeters, int speed);

/**
 * Stop the bot by disabling its motors
 */
void stop();
