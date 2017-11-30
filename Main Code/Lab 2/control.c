#include "control.h"

/**
 * Input from the xbox controller is interpreted as a keystroke and the proper action is performed by the bot
 */
char controller_input(unsigned char input,  oi_t *sensor)
{
    char obstacle = 0;

    switch (input) {

    //FORWARD
    case 'w':
        obstacle = move_forward(sensor, 15, SPD_5);
        break;

    //LEFT
    case 'a':
        turn_ccw(sensor, 10, SPD_3);
        break;

    //RIGHT
    case 'd':
        turn_cw(sensor, 10, SPD_3);
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
