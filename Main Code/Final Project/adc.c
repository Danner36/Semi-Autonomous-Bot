#include "adc.h"

///Initialize sample sequencing and wait for a conversion response
/**
 * ADC 0 Sample sequencer is activated.
 * The function enters a while loop to wait for the conversion to finish.
 * Then it returns the result as an int.
 */
int adc_Read(){

    //initiate SS1 conversion
    ADC0_PSSI_R=ADC_PSSI_SS0;

    //wait for ADC conversion to be complete
    while((ADC0_RIS_R & ADC_RIS_INR0) == 0){
        //wait
    }

    //grab result
    return (int)ADC0_SSFIFO0_R;
}

///Initialize everything necessary for ADC
/*
 * Initializes individual bits in several registers manually.
 * Uses Port D, Pin 0 and enables it as an analog alternate function.
 */
void adc_init(){
    //enable ADC 0 module on port D
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;

    //enable clock for ADC
    SYSCTL_RCGCADC_R |= 0x1;

    //enable port D pin 0 to work as alternate functions
    GPIO_PORTB_AFSEL_R |= 0x10;

    //set pin to input - 0
    GPIO_PORTB_DEN_R &= 0b11101111;

    //disable analog isolation for the pin
    GPIO_PORTB_AMSEL_R |= 0x10;

    //initialize the port trigger source as processor (default)
    GPIO_PORTB_ADCCTL_R = 0x00;

    //disable SS0 sample sequencer to configure it
    ADC0_ACTSS_R &= ~ADC_ACTSS_ASEN0;

    //initialize the ADC trigger source as processor (default)
    ADC0_EMUX_R = ADC_EMUX_EM0_PROCESSOR;

    //set 1st sample to use the AIN10 ADC pin
    ADC0_SSMUX0_R |= 0x000A;

    //enable raw interrupt status
    ADC0_SSCTL0_R |= (ADC_SSCTL0_IE0 | ADC_SSCTL0_END0);

    //enable oversampling to average
    ADC0_SAC_R |= ADC_SAC_AVG_64X;

    //re-enable ADC0 SS0
    ADC0_ACTSS_R |= ADC_ACTSS_ASEN0;
}
