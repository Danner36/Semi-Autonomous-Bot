/*
 * WiFi.h
 *
 *  Created on: Sep 25, 2016
 *      Author: ericm
 */

#ifndef WIFI_H_
#define WIFI_H_

#include <stdint.h>
#include <string.h>
#include <inc/tm4c123gh6pm.h>
#include "uart.h"

int WiFi_start();

int WiFi_stop();

void WiFi_Check(int established);

uint8_t _sendCommand(uint8_t command, uint8_t* param, uint8_t len);

#endif /* WIFI_H_ */
