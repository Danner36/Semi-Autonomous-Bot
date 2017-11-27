#include "movement.h"

/**Move forward for a certain distance; return 1 if stopped by right bumper, -1 by left */
enum status move_forward(oi_t *sensor, int centimeters, int spd) {

    enum status STATE = CLEAR;

    int sum = 0;
    oi_setWheels(spd, spd); // move forward;

    while (sum < centimeters*10) {
        oi_update(sensor);

        if (sensor->bumpLeft) {
            STATE = LEFT_BUMPER;
            break;
        }
        else if (sensor->bumpRight) {
            STATE = RIGHT_BUMPER;
            break;
        }
        else if (checkAnyCliff(sensor)) {
            STATE = CLIFF;
            break;
        }
        else if (checkBoundary(sensor)) {
            STATE = BOUNDARY;
            break;
        }

        sum += sensor->distance;
    }

    stop();

    return STATE;
}

void turn_ccw(oi_t *sensor, int degrees) {

    int sum = 0;
    oi_setWheels(SPD, -SPD); // move forward;

    while (sum < degrees) {
        oi_update(sensor);
        sum += sensor->angle;
    }

    stop();
}

void turn_cw(oi_t *sensor, int degrees) {

    int sum = degrees;
    oi_setWheels(-SPD, SPD); // move forward;

    while (sum > 0) {
        oi_update(sensor);
        sum += sensor->angle;
    }

    stop();
}

void move_backward(oi_t *sensor, int centimeters, int spd) {

    int sum = centimeters;
    oi_setWheels(-spd, -spd); // move forward;

    while (sum > 0) {
        oi_update(sensor);
        sum += sensor->distance;
    }

    stop();
}

void stop() {
    oi_setWheels(0, 0);
}
