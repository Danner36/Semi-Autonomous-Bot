//This file includes initialization for timers

#include "init.h"

///Initialize GPIO Port B for Servos and Sonar readings
/*
 * Pin B5 is used for the servo and Pin PB3 is used for Sonar.
 * Alternate digital functions are used.
 */
void init_PortB() {

    //Enables clock for portB.
    SYSCTL_RCGCGPIO_R |= 0x02;

    //Digitally enables pin 5, pin 3 on portB.
    GPIO_PORTB_DEN_R |= 0x20 | 0x8;

    //Enable alternate function for PORTB.
    GPIO_PORTB_AFSEL_R |= 0x20;

    //Select alternate function
    GPIO_PORTB_PCTL_R |= GPIO_PCTL_PB5_T1CCP1 | GPIO_PCTL_PB3_T3CCP1;

    //Set PB5 as output.
    GPIO_PORTB_DIR_R |= 0x20;
}

///Configures TIMER 3B and TIMER 1B
/*
 * Timers are set to be 16-Bit, up and down respectively, and in edge time / period modes respectively.
 * Timer 3B is used for Sonar readings and Timer 1B uses PWM for Servos
 */
void init_timers(void){

    //SYSTEM CTL - Enables clock for TIMER3, TIMER1
    SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R3 | SYSCTL_RCGCTIMER_R1;

    //CTL - Disable timers for configurations
    TIMER3_CTL_R &= ~TIMER_CTL_TBEN; // 3B
    TIMER1_CTL_R &= ~TIMER_CTL_TBEN; // 1B

    //CTL - Enables the interrupt to notice both edges.
    TIMER3_CTL_R |= TIMER_CTL_TBEVENT_BOTH; // 3B
    TIMER1_CTL_R |= TIMER_CTL_TBEVENT_BOTH; // 1B

    //Inverted or not? 14th bit for Timer B
            TIMER1_CTL_R &= 0b100000000000000; //???

    //CFG - 16 Bit Counters
    TIMER3_CFG_R |= TIMER_CFG_16_BIT; // 3
    TIMER1_CFG_R |= TIMER_CFG_16_BIT; // 1

    //MODE
    TIMER3_TBMR_R |= TIMER_TBMR_TBMR_CAP; // 3B - Capture Mode
    TIMER1_TBMR_R |= TIMER_TBMR_TBAMS; // 1B = PWM (0x8)

    //MODE
    TIMER3_TBMR_R |= TIMER_TBMR_TBCMR; // 3B - Edge Time
    TIMER1_TBMR_R &= ~TIMER_TBMR_TBCMR; // 1B - Disable
    TIMER1_TBMR_R |= TIMER_TBMR_TBMR_PERIOD; // 1B - Periodic mode

    //COUNT
    TIMER3_TBMR_R |= TIMER_TBMR_TBCDIR; // 3B - Up
    TIMER1_TBMR_R &= ~TIMER_TBMR_TBCDIR; // 1B - Down

    //Set upper bound.
    TIMER3_TBILR_R |= 0xFFFF;

    //Enables capture input for TIMER3B
    TIMER3_IMR_R |= TIMER_IMR_CBEIM;

    //Clears interrupt flags.
    TIMER3_ICR_R |= TIMER_ICR_CBECINT;


    /**
    * Interrupt Number: 36
    * Vector Number: 117
    * Vectors Address/Offset: 0x0000.01D4
    * Interrupts 32-63
    * 4th bit in the register
    */
    NVIC_EN1_R |= 0x10;

    IntRegister(INT_TIMER3B, TIMER3B_Handler);  //Register TIMER3B interrupt handler.
    IntMasterEnable();  //Initialize global interrupts.

    //Re-enable
    TIMER3_CTL_R |= TIMER_CTL_TBEN; // 3B
    TIMER1_CTL_R |= TIMER_CTL_TBEN; // 1B
}

///Initialize Port B and Timers
/**
 * Calls two sub-functions for simplicity
 */
void portB_init() {
    init_PortB();
    init_timers();
}


