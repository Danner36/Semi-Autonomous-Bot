#include "servo.h"
#include <inc/tm4c123gh6pm.h>

void move_servo(int pulse) {
    //Lower 16
    TIMER1_TBILR_R = pulse & 0xFFFF;

    //Upper 8
    TIMER1_TBPR_R = (pulse >> 16) & 0xFF;

    //Set
    TIMER1_TBMATCHR_R = PERIOD & 0xFFFF;
    TIMER1_TBPMR_R = (PERIOD >> 16) & 0xFF;

    //Pause between servo movements
    timer_waitMillis(20);

    /*
    //Lower 16
    TIMER1_TBILR_R = PERIOD & 0xFFFF;

    //Upper 8
    TIMER1_TBPR_R = (PERIOD >> 16) & 0xFF;

    //Set
    TIMER1_TBMATCHR_R = pulse & 0xFFFF;
    TIMER1_TBPMR_R = (pulse >> 16) & 0xFF;
    */
}

void move_servo2(int degree) {
    //Pulse
    int pulse_period = setPeriod(degree);

    /*
    //Lower 16
    TIMER1_TBILR_R = pulse_period & 0xFFFF; // ???

    //Upper 8
    TIMER1_TBPR_R = (pulse_period >> 16) & 0xFF;

    //Set
    TIMER1_TBMATCHR_R = PERIOD & 0xFFFF;
    TIMER1_TBPMR_R = (PERIOD >> 16) & 0xFF;
    */

    //Lower 16
    TIMER1_TBILR_R = PERIOD & 0xFFFF; // ???

    //Upper 8
    TIMER1_TBPR_R = (PERIOD >> 16) & 0xFF;

    //Set
    pulse_period = PERIOD - CW;
    TIMER1_TBMATCHR_R = pulse_period & 0xFFFF;
    TIMER1_TBPMR_R = (pulse_period >> 16) & 0xFF;
}

int setPeriod(int degree) {

    int pulse_period = PERIOD;

    switch(degree) {

    //Clockwise Full - 0 degrees
    case 2:
        pulse_period += CW;
        break;

    //Clockwise 45
    case 1:
        pulse_period += CW_45;
        break;

    //Midpoint - 90 degrees
    case 0:
        pulse_period += MID;
        break;

    //Counterclockwise 135
    case -1:
        pulse_period += CCW_135;
        break;

    //Counterclockwise Full - 180 degrees
    case -2:
        pulse_period += CCW;
        break;

    }

    return pulse_period;
}
