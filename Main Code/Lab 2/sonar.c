#include "sonar.h"
#include <inc/tm4c123gh6pm.h>

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
