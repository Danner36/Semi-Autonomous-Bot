#include "open_interface.h"

//Average floor color values
#define FLOOR_MIN 1500
#define FLOOR_MAX 2150

//Average boundary line color values
#define BOUND_MIN 2600
#define BOUND_MAX 2900

/**
 * Update cliff sensor variables and check if any are positive
 */
char checkAnyCliff(oi_t* sensor_data);

/**
 * Update cliff signals and check if any read the boundary color
 */
char checkBoundary(oi_t* sensor_data);
