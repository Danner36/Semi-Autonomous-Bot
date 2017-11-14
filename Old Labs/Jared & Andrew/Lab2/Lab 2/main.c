#include "open_interface.h"
#include "movement.h"

void main() {
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    int sum = 0;

    while(sum <= 2000){

        oi_update(sensor_data);


        if(sum!=2000){
            int travel = 2000 - sum;

            sum += move_forward(sensor_data, travel);

            if (sensor_data->bumpLeft) {
                move_backward(sensor_data);
                sum -= 150;

                turn_cw(sensor_data, 90);

                move_forward(sensor_data, 250);

                turn_ccw(sensor_data, 90);

            }

            else if (sensor_data->bumpRight) {
                move_backward(sensor_data);
                sum -= 150;

                turn_ccw(sensor_data, 90);

                move_forward(sensor_data, 250);

                turn_cw(sensor_data, 90);
            }

        }


    }

    oi_free(sensor_data);
}
