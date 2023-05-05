//
// Created by makleyston on 18/03/23.
//

#include "../ufcity_interface.h"
#include "ext/observer_client.h"
#include <thread>
#include "menu.h"
#include "../in_memory_storage/message_queue.h"
#include "../model/config/methods.h"
#include "../model/config/config.h"

using namespace ufcity_interface;

/* Send data to Fog Computing. */

int example2(int argc, char *argv[]){

    if(menu(argc, argv) != 0) {
        return 1;
    }

    /* Initializing the Edge Module */
    init(samples::json_device);

    auto * config = new ufcity::config();
    config->get_data_grouping_config()->set_method(methods::FIXED_SIZE_GROUPING);
    config->get_data_grouping_config()->set_size(2);
    config->get_data_aggregation_config()->set_method(methods::MEAN_AGGREGATION_METHOD);
    set_config(config);

    /* Setting observer client */
    auto * observerClient = new observer_client(123);
    register_observer(observerClient);

    /* Connecting to Fog Computing */
    connect_to_fog(HOST, PORT); //IP Example. Change this IP for the fog computing node IP.

    /* Registering a resource */
    register_resource(samples::json_humidity_sensor);
    register_resource(samples::json_thermometer_sensor);
    register_resource(samples::json_light_pole);

    /* Sending data of sensors
     * Here we are simulating the several sensor data present in environment. */
    while(alive()) {
        time_t end = time(nullptr) + 5; // Pass to 2 second
        while (time(nullptr) < end);
        switch (rand() % 4) {
            case 0:
                send_resource_data(samples::get_thermometer_sensor_json());
                break;
            case 1:
                send_resource_data(samples::get_humidity_sensor_json());
                break;
            case 2:
                send_resource_data(samples::get_light_pole_json());
                break;
        }
    }

    return 0;
}