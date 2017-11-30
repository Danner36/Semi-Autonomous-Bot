/**PUTTING IT ALL TOGETHER**/

#include "lcd.h"
#include <open_interface.h>
#include <stdbool.h>
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
#include "music.h" //Extra Credit
#include "control.h"

void initialize();
void wifiStart();
void power_flash(int on, int color);

bool command = false;
char feedback;

void main()
{

    //SETUP
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);  ///TURN BOT ON!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    initialize();
    wifiStart(); //Always comment out and reupload after first use

    unsigned char input_data;

    while (1) {
        lcd_printf("Waiting...");

        input_data = uart_receive();

        lcd_printf("Received: %c", input_data);

        feedback = controller_input(input_data, sensor_data);

        if (feedback == 5) {
            play_songs(0); //Music

            int i;
            for (i = 0; i < 5; i++)
            { //Lights
               power_flash(1, 255);
               timer_waitMillis(250);
               power_flash(1, 0);
               timer_waitMillis(250);
            }

            power_flash(1, 255);
        }

        /** feedback key
         * 0 - Clear
         * 1 - Left Bumper
         * 2 - Right Bumper
         * 3 - Cliff
         * 4 - Boundary
         * 5 - Finish
         * 6 - Turn complete
         * 7 - Reverse complete
         *
         */
    }

    //FINISH
    play_songs(0); //Music

    int i;
    for (i = 0; i < 5; i++)
    { //Lights
       power_flash(1, 255);
       timer_waitMillis(250);
       power_flash(1, 0);
       timer_waitMillis(250);
    }

    power_flash(1, 255);

    oi_free(sensor_data);

}

//Several initialization functions in one
void initialize()
{
    portB_init();
    adc_init();
    lcd_init();
    uart_init();
}

//Initialize WiFi
void wifiStart()
{
    int established = WiFi_start("PrawnStars");
    timer_waitMillis(10000); //wait 10 sec
    WiFi_Check(established);
}

//Flash the power symbol
void power_flash(int on, int color)
{
    oi_setLeds(on, 0, color, 255);
}

