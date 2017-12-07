#include "cliffSensor.h"

///Update cliff sensor variables and check if any are positive
/**
 * The 4 cliff sensors are each checked individually.
 * Return 0 if they are all clear.
 * Return 1 if not, meaning there is a cliff in front of the bot.
 */
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

///Update cliff signals and check if the bot has hit the boundary
/**
 * Each cliff signal is read individually into a small array.
 * The array is checked for if any signal reads the color white (the border color).
 * Return 0 if all signals are clear.
 * Return 1 if white is detected, meaning the bot has reached the boundary.
 */
char checkBoundary(oi_t* sensor_data) {

    uint16_t signals[4];

    signals[0] = sensor_data->cliffLeftSignal;
    signals[1] = sensor_data->cliffFrontLeftSignal;
    signals[2] = sensor_data->cliffFrontRightSignal;
    signals[3] = sensor_data->cliffRightSignal;

    //lcd_printf("%u, %u, %u, %u", prevValues[0], prevValues[1], prevValues[2], prevValues[3]); //For testing purposes

    char i;
    for (i = 0; i < 4; i++) {
        if (signals[i] > BOUND_MIN) {
            char data[50];
            sprintf(data, "%u, %u, %u, %u", signals[0], signals[1], signals[2], signals[3]);

            uart_sendChar('\r');

            int j = 0;
            for(j = 0; j < strlen(data); j++) {
               uart_sendChar(data[j]);
            }

            uart_sendChar('\n');

            return 1;
        }
    }

    return 0;
}
