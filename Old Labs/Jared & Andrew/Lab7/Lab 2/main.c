#include <stdio.h>
#include "timer.h"
#include "lcd.h"
#include "stdbool.h"
#include "driverlib/interrupt.h"
#include <math.h>




void init_PortB(void);
void clock_timer_init(void);
void TIMER3B_Handler(void);
void send_pulse(void);
float time2dist(signed time);
float ping_read(void);



//Rising edge of the clock cycle.
volatile unsigned rising_time = 0;

//Falling edge of the clock cycle.
volatile unsigned falling_time = 0;

//Used as a state machine which treats the clock revolution as a cycle instead of separate events.
volatile enum {Rising_Edge, Falling_Edge, Complete} cycle;

//The difference between the rising edge and falling edge times.
volatile signed difference = 0;

//Overflow status of the program.
volatile int overflow = 0;



void main(void) {

    init_PortB();
    clock_timer_init();
    lcd_init();


    while(1){

        //Distance from sonar sensor to object. (centimeters)
        float distance = ping_read();

        lcd_printf("Distance: %.1f cm \nWidth: %d \nOverflow: %d",distance, difference, overflow);

        //Pauses program to delay for sonar.
        timer_waitMillis(200);
    }
}


//Configure pin3 of portB
void init_PortB(){

    //Enables clock for portB.
    SYSCTL_RCGCGPIO_R |= 0x02;

    //Digitally enables pin 3 on portB.
    GPIO_PORTB_DEN_R |= 0x08;

    GPIO_PORTB_PCTL_R |= GPIO_PCTL_PB3_T3CCP1;
}


//Configures TIMER3B
void clock_timer_init(void){

    //Enables clock for TIMER3B
    SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R3;

    //Configure the timer for input capture mode
    TIMER3_CTL_R &= ~TIMER_CTL_TBEN;

    //Enables the interrupt to notice both edges.
    TIMER3_CTL_R |= TIMER_CTL_TBEVENT_BOTH;

    //Sets TIMER3B to be a 16 bit counter.
    TIMER3_CFG_R |= TIMER_CFG_16_BIT;

    //Sets TIMER3B to capture mode.
    TIMER3_TBMR_R |= TIMER_TBMR_TBMR_CAP;

    //Sets TIMER3B to edge-time mode.
    TIMER3_TBMR_R |= TIMER_TBMR_TBCMR;

    //Sets TIMBER3B to count up mode.
    TIMER3_TBMR_R |= TIMER_TBMR_TBCDIR;

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

    //Re-enable TIMER3.
    TIMER3_CTL_R |= TIMER_CTL_TBEN;
}


void TIMER3B_Handler(void){

    //Clears interrupt flags.
    TIMER3_ICR_R |= TIMER_ICR_CBECINT;

    //Checks for the rising edge of the clock cycle.
    if(cycle == Rising_Edge){

        //Captures current time.
        rising_time = TIMER3_TBR_R;

        //Switches to watch for the second clock edge.
        cycle = Falling_Edge;
    }
    //Checks for the falling edge of the clock cycle.
    else if(cycle == Falling_Edge){

        //Captures current time.
        falling_time = TIMER3_TBR_R;

        //Updates the cycle (state machine) to signal the end of the current clock cycle.
        //   This will ensure the next cycle it looks for is the rising edge of the next cycle.
        cycle = Complete;
    }
}


void send_pulse(){


    //IntMasterDisable();

    //Disables alternate function for PORTB.
    GPIO_PORTB_AFSEL_R &= ~(0x08);

    //Set PB3 as output.
    GPIO_PORTB_DIR_R |= 0x08;

    //Set PB3 to high.
    GPIO_PORTB_DATA_R |= 0x08;

    //Delays for 5 micro seconds.
    timer_waitMicros(5);

    //Set PB3 to low.
    GPIO_PORTB_DATA_R &= 0xF7;

    //Set PB3 as input.
    GPIO_PORTB_DIR_R &= 0xF7;

    //Re-enables alternate function for portB.
    GPIO_PORTB_AFSEL_R |= 0x08;

    //IntMasterEnable();
}


float ping_read(){

    //Sends sonar pulse.
    send_pulse();

    //Sets the state machine to look for the rising edge of the clock cycle.
    cycle = Rising_Edge;

    //Stalls until the clock cycle is completed. This infinite loop still
    //   allows for the interrupts to call which will update the state machine.
    //   Once the rising and falling edge have occurred, the while loop will exit.
    while(cycle != Complete){};

    //Calculate & adjusts for the overflow of the system.
    if(rising_time > falling_time){

        //Equivalent of shifting the bit by 24 positions to the left. Subtracts appropriate amount to correct the value.
        //falling_time += ((unsigned) pow(2,24) - 1 - rising_time);
        difference = ((unsigned long) overflow << 24) + difference;

        //Increments the overflow.
        overflow = overflow + 1;
    }
    else{
        //Subtracts the rising and falling edge to get the difference between the two clock values.
        difference = falling_time - rising_time;
    }


    //Returns the calculated distance in cm.
    return ((float)((difference/2.0 * (34000.0 / 16000000.0))));
}
