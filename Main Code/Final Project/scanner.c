#include "scanner.h"

#define CALIB -10

//Counter to keep track of detected objects.
char numObjects = 0;

//Beginning angle, ending angle, and the total angle width of the object.
int angle1 = 0, angle2 = 0, totalAngle = 0;

//Holds the current cycles Sonar Distance.
float sonarDis = 0.0;

//Holds the current cycles IR Distance.
float irDis = 0.0;

//First recorded distance
float firstDistance = 0.0;

//Once an object is detected, this value is compounded with each cycles's
//   distance. This is used to calculate the average.
float totalDis = 0.0;

//Value used to move the servo.
int pulse_period = 0;

//Once an object is detected, this value will increment by one with every
//   cycle. This is used to keep track of how many degrees the object was
//   was detected for.
float cyclesDetected = 0.0;

float linearWidth = 0.0;

//Used to keep track of this projects status as a state machine.
enum status {NONE , DETECTED, SCANNING};
enum status STATE = NONE;

///Collect data on surroundings in 180-degree scan
/**
 * The scan stops every 2 degrees to make an IR and Sonar reading.
 * The readings are recorded and then the scan continues.
 * While scanning, data is interpreted by the readings to try to tell if the scan has encountered objects within 100 centimeters of the scanner.
 * Scan results are transmitted via UART as objects are detected.
 */
void scan() {

    uart_sendChar('\n');
    uart_sendChar('\r');
    uart_sendChar('$');
    uart_sendChar('\n');
    uart_sendChar('\r');

    reset();

    int i = 0;

    //Main loop. Iterates servo from degree 0 to 180 while capturing data. Also
    //   performs calculations and transmits useful info to Putty via WiFi.
    for (i = 0; i < 180; i += 2) {

        //Moves the servo two degrees.
        pulse_period += DEGREE;
        move_servo(pulse_period);

        pulse_period += DEGREE;
        move_servo(pulse_period);

        //Collects data from both IR & Sonar sensors.
        collectData();

        //Object has been detected. Updates state machine.
        if ((STATE == NONE) && ((irDis < 100) && (sonarDis < 100))) {

            //Object has been detected. Updates state machine.
            STATE = DETECTED;

            //Captures the angle at which the object is first detected.
            angle1 = i;

            //Increments the number of objects detected by 1.
            numObjects++;

            firstDistance = sonarDis;

            //Used in the calculation of where the current object is located.
            totalDis += sonarDis;

            //Used to later calculate the average distance.
            //   (number of cycles the object is in sight)
            cyclesDetected++;

        }

        //Object is still being detected. Continues to read in data.
        else if((STATE == DETECTED) && ((irDis < 100) && (sonarDis < 100))){

            //Updates state machine to reflect the current situation.
            STATE = SCANNING;

            //Updates the current distance of the object in case the object is no longer detected
            //   next cycle.
            totalDis += sonarDis;

            //Used to later calculate the average distance.
            //   (number of cycles the object is in sight)
            cyclesDetected++;

        }

        //Object has been lost. Current data shows no object within 100cm.
        else if (STATE == SCANNING && (irDis > 100 || sonarDis > 100)) {

            int angleCalibration = 2;

            //Captures the angle at which the object is last detected.
            angle2 = i;

            //Calculates the total angle width of the object.
            //   - 2  <- moves the degree back to when the object was detected. (ending degree)
            //   / 2  <- gets the average of the two angles. (degree location of object)
            int degreeOfObject = ((angle1 + angle2)/2) - angleCalibration;

            //Calculates the average distance to the object.
            float objectDis = (totalDis / cyclesDetected);

            //Calculate the angle of the object.
            int objectAngle = ((angle2 - angle1) - 2);

            linearWidth = calculateLinearWidth(objectAngle, objectDis);

            //Sends datat to PUTTY
            sendData((degreeOfObject + CALIB), objectDis, linearWidth);

            //Resets temporary variables.
            resetTempVars();
        }

        linearWidth = 0;
    }

    uart_sendChar('\r');
    uart_sendChar('$');

    uart_sendChar('\n');
    uart_sendChar('\n');

    uart_sendChar('\r');
}

///Reset scan
/**
 * Used before the scan begins.
 * Resets variables used by the scanner.
 * Turns the servo to the 0-degree position.
 */
void reset() {
    numObjects = 0;

    angle1 = 0;
    angle2 = 0;
    totalAngle = 0;

    sonarDis = 0.0;

    irDis = 0.0;

    firstDistance = 0.0;

    totalDis = 0.0;

    pulse_period = 0;

    cyclesDetected = 0.0;

    STATE = NONE;

    //Resets the servo's position to zero degrees (Far right).
    pulse_period = PERIOD + CW;
    move_servo(pulse_period);

    //1.5 second delay to ensure servo reaches the 0th degree.
    timer_waitMillis(1500);

    //Sends the header information to Putty (lab 9).
    //sendHeader();
}

///Linear Width calculation
/**
 * Width = distance * sin(angle in radians divided by two)
 *
 * @param angle - angular width of object as read by scanner
 * @param distance - distance between scanner and target object
 *
 * Returns a linear width in centimeters.
 */
float calculateLinearWidth(int angle, float distance) {
    float angleInRads = ((float)angle * (float)M_PI)/180.0;

    float width = distance * sinf(angleInRads/2.0);

    if (width < 0) width *= -1;

    return width;
}

///Collect data from both Sonar and IR sensors.
/**
 * Runs both functions for sending and receiving Sonar/IR signals.
 */
void collectData(){
    sonarDis = ping_read();
    irDis = getIRtoDis((float)adc_Read());
}

///Calculates the conversion from IR input to distance.
/*
 * Distance = (1.682 * 10^7) / ((IR reading) ^ 500/239) + 10
 *
 * @param result - the raw IR reading
 *
 * Returns a distance in centimeters.
 */
float getIRtoDis(float result){
    return (float)(1.682* pow(10,7))/(pow(result,500/239)) + 10;
}

///Resets temporary variables.
/*
 * Resets certain variables which are re-used 90 times during the scan.
 * Not to be confused with the total reset function.
 */
void resetTempVars(){

    cyclesDetected = 0.0;
    totalDis = 0.0;
    angle1 = 0;
    angle2 = 0;

    //Back to default state
    STATE = NONE;
}

///Sends current information via UART.
/*
 * Data on the most recently scanned object is transmitted char-by-char to UART.
 * Data is formatted in a compact line with angle, distance, and linear width.
 *
 * @param i - degree of scanned object relative to the front of the scanner
 * @param distance - distance in centimeters
 * @param linearWidth - actual width of object most recently scanned
 */
void sendData(int i, float distance, float linearWidth) {

    float dis = distance - 10;
    float lin = linearWidth;
    int angle = i;

    if (angle < 1) angle = 0;
    if (lin <= 1) lin = 1.0;

    char data[50];
    sprintf(data, "%i,%0.0f,%0.0f", angle, dis, lin);

    uart_sendChar('\r');

    int j = 0;
    for(j = 0; j < strlen(data); j++) {
       uart_sendChar(data[j]);
    }

    uart_sendChar('\n');
}
