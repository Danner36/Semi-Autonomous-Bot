/**PUTTING IT ALL TOGETHER**/

#include "lcd.h"
#include "movement.h" //Lab 2
#include "init.h"
#include "uart.h" //Lab 5
#include "wifi.h"
#include "adc.h" //Lab 6
#include "sonar.h" //Lab 7
#include "servo.h" //Lab 8
#include <string.h>
#include <inc/tm4c123gh6pm.h>
#include "driverlib/interrupt.h"
#include <stdio.h>
#include <math.h>
#include <scanner.h> //Lab 9

void initialize();
void wifiStart();

void main() {

    initialize();

    //wifiStart(); //Always comment out and reupload after first use

    scan();

}

void initialize() {
    portB_init();
    adc_init();
    lcd_init();
    uart_init();
}

void wifiStart() {
    int established = WiFi_start("password");
    timer_waitMillis(10000); //wait 10 sec
    WiFi_Check(established);
}
