#include "movement.h"

/**Move forward for a certain distance;
 *
 * 0 = Clear
 * 1 = Left Bumper
 * 2 = Right Bumper
 * 3 = Cliff
 * 4 = Boundary
 *
 */
char move_forward(oi_t *sensor, int centimeters, int spd) {

    if (checkAll(sensor)) {
        return 0;
    }

    int sum = 0;
    int hit = 0;
    oi_setWheels(spd, spd); // move forward;

    while (sum < centimeters*10) {
        oi_update(sensor);

        if (sensor->bumpLeft) {
            uart_sendChar('1');
            hit = 1;
            break;
        }
        else if (sensor->bumpRight) {
            uart_sendChar('2');
            hit = 1;
            break;
        }
        else if (checkAnyCliff(sensor)) {
            uart_sendChar('3');
            hit = 1;
            break;
        }
        else if (checkBoundary(sensor)) {
            uart_sendChar('4');
            hit = 1;
            break;
        }

        sum += sensor->distance;
    }

    stop();

    if (!hit) {
        uart_sendChar('0');
    }

    return 0;
}

char checkAll(oi_t *sensor) {
    if (sensor->bumpLeft) {
        uart_sendChar('1');
        return 1;
    }
    else if (sensor->bumpRight) {
        uart_sendChar('2');
        return 1;
    }
    else if (checkAnyCliff(sensor)) {
        uart_sendChar('3');
        return 1;
    }
    else if (checkBoundary(sensor)) {
        uart_sendChar('4');
        return 1;
    }

    return 0;
}

void turn_ccw(oi_t *sensor, int degrees) {

    int sum = 0;
    oi_setWheels(SLOW, -SLOW); // move forward;

    while (sum < degrees) {
        oi_update(sensor);
        sum += sensor->angle;
    }

    stop();

    uart_sendChar('6');
}

void turn_cw(oi_t *sensor, int degrees) {

    int sum = degrees;
    oi_setWheels(-SLOW, SLOW); // move forward;

    while (sum > 0) {
        oi_update(sensor);
        sum += sensor->angle;
    }

    stop();

    uart_sendChar('6');
}

void move_backward(oi_t *sensor, int centimeters, int spd) {

    int sum = centimeters;
    oi_setWheels(-spd, -spd); // move forward;

    while (sum > 0) {
        oi_update(sensor);
        sum += sensor->distance;
    }

    stop();

    uart_sendChar('7');
}

void stop() {
    oi_setWheels(0, 0);
}
