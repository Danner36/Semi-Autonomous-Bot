/*
 * main.c
 */
#include <open_interface.h>
#include <Timer.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inc/tm4c123gh6pm.h>
#include <lcd.h>
#include <math.h>
#include <servo.h>
#include "stdbool.h"
#include "button.h"
#include "servo.h"
#include "ping.h"
#include "uart.h"
#include "WiFi.h"
#include "ir.h"

int degrees;
int travel_distance;

int main(void)
{
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);
//    /// \brief Load song sequence
//    /// \param An integer value from 0 - 15 that acts as a label for note sequence
//    /// \param An integer value from 1 - 16 indicating the number of notes in the sequence
//    /// \param A pointer to a sequence of notes stored as integer values
//    /// \param A pointer to a sequence of durations that correspond to the notes
//    void oi_loadSong(int song_index, int num_notes, unsigned char  *notes, unsigned char  *duration);
//
//    /// \brief Play song
//    /// \param An integer value from 0 - 15 that is a previously establish song index
//    void oi_play_song(int index);
    char password[] = "prawnstar";
    WiFi_start(password);
    play_songs(0);
    int i;
    unsigned char xbox_input;

    while (1)
    {
        power_flash(1, 0);
        timer_waitMicros(100);
        power_flash(1, 255);

    }

}

void play_songs(int i)
{
    unsigned char notes[] = { 69, 69, 69, 69, 65, 67, 69, 0, 67, 69 };
    unsigned char lengths[] = { 12, 12, 12, 24, 24, 24, 12, 12, 12, 40 };
    oi_loadSong(i, 10, notes, lengths);
    oi_play_song(i);
}
/// \brief Set the LEDS on the Create
/// \param play_led 0=off, 1=on
/// \param advance_led 0=off, 1=on
/// \param power_color (0-255), 0=green, 255=red
/// \param power_intensity (0-255) 0=off, 255=full intensity
void power_flash(int on, int color)
{
    oi_setLeds(on, 0, color, 255);

}
/*
 * l = left front bumper
 * r = right front bumper
 * L = left back trigger
 * R = right back trigger
 * x, y, a, b are their actual button letters
 */
void controller_input(unsigned char input)
{
    if (input == 'x')
    {

    }
    if (input == 'y')
    {

    }
    if (input == 'a')
    {

    }
    if (input == 'b')
    {

    }
//    if (input == 'l')
//    {
//        travel_distance = travel_distance - 5;
//
//
//    }
//    if (input == 'r')
//
//        travel_distance = travel_distance + 5;
//    }
//    if (input == 'L')
//    {
//        degrees = degrees - 5;
//        if(degrees < 0)
//            degrees = 0;
//    }
//    if (input == 'R')
//    {
//        degrees = degrees +5;
//        if(degrees > 0)
//    }
}
