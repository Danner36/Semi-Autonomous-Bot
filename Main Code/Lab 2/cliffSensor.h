#include "open_interface.h"

//Average floor color values
#define FLOOR_MIN 1500
#define FLOOR_MAX 2150

//Average boundary line color values
#define BOUND_MIN 2600
#define BOUND_MAX 2900

char checkAnyCliff(oi_t* sensor_data);

char checkBoundary(oi_t* sensor_data);
