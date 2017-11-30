#include "control.h"

char controller_input(unsigned char input,  oi_t *sensor)
{
    char obstacle = 0;

    switch (input) {

    //FORWARD
    case 'w':
        obstacle = move_forward(sensor, 15, SLOW);
        break;

    //LEFT
    case 'a':
        turn_ccw(sensor, 15);
        break;

    //RIGHT
    case 'd':
        turn_cw(sensor, 15);
        break;

    //SCAN
    case 's':
        scan();
        break;

    //Back Up
    case 'x':
        move_backward(sensor, 30, SLOW);
        break;

    //FINISH
    case 'q':
        return 5; // 5 = done
    }

    return obstacle;

}

//Extra code from earlier - may be unnecessary
//        if(input_data[y] == 'a'){
        //            for (execute = ; y > 0; y--) // reads the array and does the output of the of each letter in controller_input.
        //            {
        //                controller_input(input_data[y]);
        //            }
        //        }
