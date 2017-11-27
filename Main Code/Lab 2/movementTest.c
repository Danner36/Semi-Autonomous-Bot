#include "open_interface.h"
#include "movement.h"
#include "lcd.h"
#include "timer.h"

/**Tests for movement, bumpers, and cliff sensors/signals */

/* Alternate main
 *
void main() {

    enum status STATE = CLEAR;

    //Inits
    lcd_init();
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    //Move forward
    STATE = move_forward(sensor_data, 30, SLOW);

    switch(STATE) {

    case LEFT_BUMPER: //Left
        turn_ccw(sensor_data, 90);
        break;

    case RIGHT_BUMPER: //Right
        turn_cw(sensor_data, 90);
        break;

    case CLIFF: //Cliff
        turn_cw(sensor_data, 180);
        break;

    case BOUNDARY: //Boundary - don't move
        break;

    default: break;
    }

    oi_free(sensor_data);
}

*/
