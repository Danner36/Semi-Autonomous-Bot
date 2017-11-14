#include "timer.h"
#include "adc.h"
#include "lcd.h"
#include "math.h"


int getDistance(int result){
    return (1.682* pow(10,7))/(pow(result,500/239)) + 10;

}

int calculateAverage(int array[], int size) {
    int sum = 0, j;

    for (j = 0; j < size; j++) {
        sum += array[j];
    }

    return (sum / size);
}

void main() {
    adc_Start();
    lcd_init();

    while(1){

        int values[16];
        int i;

        for (i = 0; i < 16; i++) {
            values[i] = adc_Read();
            timer_waitMillis(12);
        }

        //Printed average
        int average = calculateAverage(values, 16);

        lcd_printf("Data: %d, Avg: %d", average, getDistance(average));

        /*
        int result = 0;
        result = adc_Read();

        lcd_printf("%d", result);
        lcd_printf("%d", getDistance(result));
        timer_waitMillis(200);
        */

    }

    adc_Stop();
}

