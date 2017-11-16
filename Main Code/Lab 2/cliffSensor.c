#include "cliffSensor.h"

/**Update cliff sensor variables and check if any are positive*/
char checkAnyCliff(oi_t* sensor_data) {

    uint32_t* sensors[4];

    sensors[0] = sensor_data->cliffLeft;
    sensors[1] = sensor_data->cliffFrontLeft;
    sensors[2] = sensor_data->cliffFrontRight;
    sensors[3] = sensor_data->cliffRight;

    char i;
    for (i = 0; i < 4; i++) {
        if (sensors[i]) {
            return 1;
        }
    }

    return 0;
}

/**Boundary check - cliff signals*/
char checkBoundary(oi_t* sensor_data) {

    uint16_t signals[4];

    signals[0] = sensor_data->cliffLeftSignal;
    signals[1] = sensor_data->cliffFrontLeftSignal;
    signals[2] = sensor_data->cliffFrontRightSignal;
    signals[3] = sensor_data->cliffRightSignal;

    //lcd_printf("%u \n%u \n%u \n%u", prevValues[0], prevValues[1], prevValues[2], prevValues[3]); //For testing purposes

    char i;
    for (i = 0; i < 4; i++) {
        if (signals[i] > BOUND_MIN) return 1;
    }

    return 0;
}
