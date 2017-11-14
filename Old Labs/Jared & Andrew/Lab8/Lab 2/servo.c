#include "servo.h"

//Configure pin3 of portB
void init_PortB() {

    //Enables clock for portB.
    SYSCTL_RCGCGPIO_R |= 0x02;

    //Digitally enables pin 5 on portB.
    GPIO_PORTB_DEN_R |= 0x20;

    //Enable alternate function for PORTB.
    GPIO_PORTB_AFSEL_R |= 0x20;

    //???
    GPIO_PORTB_PCTL_R |= GPIO_PCTL_PB5_T1CCP1;

    //Set PB5 as output.
    GPIO_PORTB_DIR_R |= 0x20;
}

//Configures TIMER3B
void clock_timer_init(void) {

    //Enables clock for TIMER3B
    SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R1;

    //Disable timer for config
    TIMER1_CTL_R &= ~TIMER_CTL_TBEN;

    //Enables the interrupt to notice both edges.
    TIMER1_CTL_R |= TIMER_CTL_TBEVENT_BOTH;

    //Inverted or not? 14th bit for Timer B
    TIMER1_CTL_R &= 0b100000000000000;

    //Sets TIMER3B to be a 16 bit counter.
    TIMER1_CFG_R |= TIMER_CFG_16_BIT;

    //Sets TIMER3B to PWM mode.
    TIMER1_TBMR_R |= 0x8;

    //Sets TIMER3B to edge-time mode.
    TIMER1_TBMR_R &= ~TIMER_TBMR_TBCMR;

    //Set TIMER3B to Periodic mode
    TIMER1_TBMR_R |= 0x2;

    //Sets TIMBER3B to count down mode.
    TIMER1_TBMR_R &= ~TIMER_TBMR_TBCDIR; //assumed; not given in config instructions

    //Re-enable Timer
    TIMER1_CTL_R |= TIMER_CTL_TBEN;

    //Pulse
    int pulse_period = setPeriod(0);

    //Lower 16
    TIMER1_TBILR_R = pulse_period & 0xFFFF;

    //Upper 8
    TIMER1_TBPR_R = (pulse_period >> 16) & 0xFF;

    //Set
    TIMER1_TBMATCHR_R = PERIOD & 0xFFFF;
    TIMER1_TBPMR_R = (PERIOD >> 16) & 0xFF;

    timer_waitMillis(1000);
}

void move_servo(int degree) {
    //Pulse
    int pulse_period = setPeriod(degree);

    //Lower 16
    TIMER1_TBILR_R = pulse_period & 0xFFFF; // ???

    //Upper 8
    TIMER1_TBPR_R = (pulse_period >> 16) & 0xFF;

    //Set
    TIMER1_TBMATCHR_R = PERIOD & 0xFFFF;
    TIMER1_TBPMR_R = (PERIOD >> 16) & 0xFF;
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


void move_servo2(int pulse) {
    //Lower 16
    TIMER1_TBILR_R = pulse & 0xFFFF; // ???

    //Upper 8
    TIMER1_TBPR_R = (pulse >> 16) & 0xFF;

    //Set
    TIMER1_TBMATCHR_R = PERIOD & 0xFFFF;
    TIMER1_TBPMR_R = (PERIOD >> 16) & 0xFF;
}

