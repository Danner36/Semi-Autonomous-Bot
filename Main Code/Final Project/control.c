#include "control.h"

#define CALIB_M 3

#define CALIB_A -2

///Manage input from an exterior controller
/**
 * Input given by UART is interpreted as a keystroke and the proper action is performed by the bot.
 * The bot can turn, move forward, reverse, scan, or play music through this function.
 * The movement and scanner files are referenced through this function.
 */
char controller_input(unsigned char input,  oi_t *sensor)
{
    char obstacle = 0;

    switch (input) {

    //FORWARD
    case 'w':
        obstacle = move_forward(sensor, 15 + CALIB_M, SPD_5);
        break;

    //LEFT
    case 'a':
        turn_ccw(sensor, 15 + CALIB_A, SPD_3);
        break;

    //RIGHT
    case 'd':
        turn_cw(sensor, 15 + CALIB_A, SPD_3);
        break;

    //SCAN
    case 's':
        scan();
        break;

    //Back Up
    case 'x':
        move_backward(sensor, 15, SPD_5);
        break;

    //FINISH
    case 'q':
        return 5; // 5 = done
    }

    return obstacle;

}
