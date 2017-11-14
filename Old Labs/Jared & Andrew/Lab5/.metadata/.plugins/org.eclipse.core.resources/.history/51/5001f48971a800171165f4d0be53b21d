/*
 * wifi.c
 *
 *  Created on: Oct 3, 2017
 *      Author: jdanner
 */

#include "uart.h"



void WiFi_start(){
    int commandPin = 1; //Enter command mode
    uart_sendChar(0x00); //Send command
    uart_sendStr("password"); //Send WiFi PSK
    uart_sendChar(0x00); //NULL terminator
    char response = uart_waitForChar(); //Wait for response
    commandPin = 0; //Leave command mode
    if(response != 0) {
        //An error occurred…
    }
}

void WiFi_stop(){
    int commandPin = 1; //Enter command mode
    uart_sendChar(0x00); //Send command
    char response = uart_waitForChar(); //Wait for response
    commandPin = 0; //Leave command mode
    if(response != 0) {
        //An error occurred…
    }
}
