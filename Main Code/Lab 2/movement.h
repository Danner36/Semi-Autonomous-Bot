#include "open_interface.h"
#include "cliffSensor.h"

#define SPD 250 //Normal Speed
#define SLOW 100 //Slow Speed

enum status {CLEAR, LEFT_BUMPER, RIGHT_BUMPER, CLIFF, BOUNDARY};

enum status move_forward(oi_t *sensor, int centimeters, int speed);

void turn_ccw(oi_t *sensor, int degrees);

void turn_cw(oi_t *sensor, int degrees);

void move_backward(oi_t *sensor, int centimeters, int speed);

void stop();
