//
// Created by makleyston on 18/03/23.
//

#include "../ufcity_interface.h"
#include "ext/observer_client.h"

#include <thread>

using namespace ufcity_interface;

/* Send data to Fog Computing. */

int example2(){
    /* Initializing the Edge Module */
    init(samples::json_device);

    /* Setting observer client */
    auto * observerClient = new observer_client(123);
    register_observer(observerClient);

    /* Connecting to Fog Computing */
    std::thread connect_thread(&connect_to_fog, "172.19.0.2"); //IP Example. Change this IP for the fog computing node IP.
    connect_thread.detach();
//    connect_to_fog("172.19.0.2");

    /* Registering a resource */
    register_resource(samples::json_humidity_sensor);
    register_resource(samples::json_thermometer_sensor);
    register_resource(samples::json_light_pole);

    /* Sending data of sensors
     * Here we are simuling the several sensor data present in environment. */
    while(true) {
        switch (rand() % 3) {
            case 0:
                send_resource_data(samples::json_thermometer_sensor);
                break;
            case 1:
                send_resource_data(samples::json_humidity_sensor);
                break;
            case 2:
                send_resource_data(samples::json_light_pole);
                break;
        }
        std::chrono::seconds inteval(2);
        std::this_thread::sleep_for(inteval);
    }
}