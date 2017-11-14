#include <stdio.h>
#include <string.h>

#include "lcd.h"
#include "timer.h"
#include "button.h"
#include "uart.h"
#include "wifi.h"

//Doesn't work for some reason
void checkIndex(char* index) {
    *index++;

    if (*index == 20) {
        *index = 0;
        uart_sendChar('\r');
        uart_sendChar('\n');
        lcd_printf("");
    }
}

void main() {
    lcd_init();
    uart_init();
    WiFi_start();
    button_init();

    char received[21];

    char lastChar = 'a';
    char lastLastChar = 'a';

    char* b6 = "Yes";
    char* b5 = "No";
    char* b4 = "Blue, no green, Ahhhhh!!!";
    char* b3 = "Andrew is great!";
    char* b2 = "Jared is sorta great, I guess";
    char* b1 = "CPRE 288";

    while(1){
        char index = 0;

        while(index < 20){

            lastChar = uart_receive();

            //Button Presses - really repetitive hear, wish i could make a function for it
            if (lastChar == 6 && lastLastChar != 6) {
                int j = 0;
                for (j = 0; j < strlen(b6); j++) {
                    uart_sendChar(b6[j]);
                    checkIndex(&index);
                    index++;
                    if (index == 20) {
                        index = 0;
                        uart_sendChar('\r');
                        uart_sendChar('\n');
                        lcd_printf("");
                    }
                }
            }
            else if (lastChar == 5 && lastLastChar != 5) {
                int j = 0;
                for (j = 0; j < strlen(b5); j++) {
                    uart_sendChar(b5[j]);
                    index++;
                    if (index == 20) {
                        index = 0;
                        uart_sendChar('\r');
                        uart_sendChar('\n');
                        lcd_printf("");
                    }
                }
            }
            else if (lastChar == 4 && lastLastChar != 4) {
                            int j = 0;
                            for (j = 0; j < strlen(b4); j++) {
                                uart_sendChar(b4[j]);
                                index++;
                                if (index == 20) {
                                    index = 0;
                                    uart_sendChar('\r');
                                    uart_sendChar('\n');
                                    lcd_printf("");
                                }
                            }
                        }
            else if (lastChar == 3 && lastLastChar != 3) {
                int j = 0;
                for (j = 0; j < strlen(b3); j++) {
                    uart_sendChar(b3[j]);
                    index++;
                    if (index == 20) {
                        index = 0;
                        uart_sendChar('\r');
                        uart_sendChar('\n');
                        lcd_printf("");
                    }
                }
            }
            else if (lastChar == 2 && lastLastChar != 2) {
                            int j = 0;
                            for (j = 0; j < strlen(b2); j++) {
                                uart_sendChar(b2[j]);
                                index++;
                                if (index == 20) {
                                    index = 0;
                                    uart_sendChar('\r');
                                    uart_sendChar('\n');
                                    lcd_printf("");
                                }
                            }
                        }
            else if (lastChar == 1 && lastLastChar != 1) {
                int j = 0;
                for (j = 0; j < strlen(b1); j++) {
                    uart_sendChar(b1[j]);
                    index++;
                    if (index == 20) {
                        index = 0;
                        uart_sendChar('\r');
                        uart_sendChar('\n');
                        lcd_printf("");
                    }
                }
            }

            //Normal char input
            else if (lastChar > 6) { //1-6 reserved for button presses
                if(lastChar != '\r') {
                    received[index] = lastChar;

                    index++;

                    lcd_printf("%c, index: %d", lastChar, index);
                    uart_sendChar(lastChar);

                }
                else {
                    break;
                }
            }

            if (button_getButton() == 0) lastLastChar = 0;
            else lastLastChar = lastChar;
        }

        received[index] = '\0';

        lcd_printf(received);
        uart_sendChar('\r');
        uart_sendChar('\n');
    }

    WiFi_stop();
}


