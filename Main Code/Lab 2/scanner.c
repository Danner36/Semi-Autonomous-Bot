#include "scanner.h"

//VARIABLES

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

//Collect data on surroundings in 180-degree scan
void scan() {

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

            linearWidth = calculateLinearWidth(objectAngle, firstDistance);

            //Resets temporary variables.
            resetTempVars();
        }

        //Sends the current most cycles data to Putty.
        sendData(i, linearWidth);

        linearWidth = 0;
    }

    timer_waitMillis(200);
}

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

    //Sends the header information to Putty.
    //sendHeader();
}

//Linear Width
float calculateLinearWidth(int angle, float distance) {
    float angleInRads = ((float)angle * (float)M_PI)/180.0;

    float width = distance * sinf(angleInRads/2.0);

    if (width < 0) width *= -1;

    return width;
}

//Collects data from both Sonar and IR sensors.
void collectData(){
    sonarDis = ping_read();
    irDis = getIRtoDis((float)adc_Read());
}

//Calculates and returns the average of the passed in array.
int getAverage(int array[]) {

    int i, sum = 0;

    for (i = 0; i < sizeof(array)/4; i++) {
        if (array[i] == 0){
            break;
        }
        else{
            sum += array[i];
        }
    }

    return (sum / i);
}

//Calculates the conversion from IR input to distance.
float getIRtoDis(float result){
    return (float)(1.682* pow(10,7))/(pow(result,500/239)) + 10;
}

//Resets temporary variables.
void resetTempVars(){

    cyclesDetected = 0.0;
    totalDis = 0.0;
    angle1 = 0;
    angle2 = 0;

    //Back to default state
    STATE = NONE;
}

//Sends current information to Putty.
void sendData(int i, float linearWidth) {
    char data[50];
    sprintf(data, "%i,%0.1f,%0.2f,%0.2f", i, irDis, sonarDis, linearWidth);

    uart_sendChar('\r');

    int j = 0;
    for(j = 0; j < strlen(data); j++) {
       uart_sendChar(data[j]);
    }

    uart_sendChar('\n');
}

//Sends Header information to Putty
void sendHeader(){

    char* header = "Degrees\t\tIR Distance (cm)\tSonar Distance (cm)\tWidth";

    //Resets the position of the cursor to 2 lines below and the beginning of the line.
    uart_sendChar('\n');
    uart_sendChar('\n');
    uart_sendChar('\r');

    int i = 0;
    //Iterators through the array, sends each character to Putty via WiFi.
    for(i = 0; i < strlen(header); i++){
        uart_sendChar(header[i]);
    }

    //New lines.
    uart_sendChar('\n');
    uart_sendChar('\n');
}
