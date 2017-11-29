/**PUTTING IT ALL TOGETHER**/

#include "lcd.h"
#include <open_interface.h>
#include <stdbool.h>
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
#include "music.h" //Extra Credit

void initialize();
void wifiStart();
void controller_input(unsigned char input, oi_t *sensor );

void power_flash(int on, int color);
int degrees;
int travel_distance;
bool done = false, command = false;

void main()
{

    //SETUP
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);  ///TURN BOT ON!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    initialize();
  //  wifiStart(); //Always comment out and reupload after first use

    char password[] = "prawnstar";
    unsigned char input_data;
    WiFi_start(password);
    play_songs(0);
    int i, y, execute;
    unsigned char xbox_input;
    while (done == false) // takes the input data from the controller and stores it into an array
    {
        if (command == false)
        {
            input_data = uart_receive();
            controller_input(input_data, sensor_data );

        }
        if (command == true)
        {
            uart_sendChar('T');
            command = false;
        }

        //        if(input_data[y] == 'a'){
        //            for (execute = ; y > 0; y--) // reads the array and does the output of the of each letter in controller_input.
        //            {
        //                controller_input(input_data[y]);
        //            }
        //        }
        if(done== true){
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
    }

    //OPERATION

    //FINISH

}

void controller_input(unsigned char input,  oi_t *sensor)
{

    if (input == 'x')
    {
        move_forward(sensor, 15, 250);
        command = true;
    }
    if (input == 'l')
    {
        turn_ccw(sensor, 15);
        command = true;
    }
    if (input == 'r')
    {
        turn_cw(sensor, 15);
        command = true;
    }
    if (input == 's')
    {
        scan();
        command = true;
    }
    if(input == 'd'){
        done = true;
        command = true;
    }
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
    int established = WiFi_start("password");
    timer_waitMillis(10000); //wait 10 sec
    WiFi_Check(established);
}

//Flash the power symbol
void power_flash(int on, int color)
{
    oi_setLeds(on, 0, color, 255);
}

