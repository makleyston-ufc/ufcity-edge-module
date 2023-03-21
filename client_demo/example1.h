//
// Created by makleyston on 18/03/23.
//

#include "../ufcity_interface.h"
#include "ext/observer_client.h"
#include "ext/json_data_sample.hpp"
#include <thread>

using namespace ufcity_interface;

/* This example show all commands of UFCity lib.
 * It don't have practice working, but it presents the possibles of use this lib.
 * */

int example1(){
    /* Initializing the Edge Module */
    init(samples::json_device);

    /* Setting observer client */
    auto * observerClient = new observer_client(123);
    register_observer(observerClient);

    /* Connecting to Fog Computing */
    std::thread connect_thread(&connect_to_fog, "172.19.0.2"); //IP Example. Change this IP for the fog computing node IP.
    connect_thread.detach();

    /* Removing an observer client */
    remove_observer(observerClient);

    /* Registering a resource */
    register_resource(samples::json_resource);

    /* Printing all stored resources */
    auto * map = get_resources_map();
    for (auto const &pair: *map) {
        std::cout << "{" << pair.first << ": " << pair.second->get_resource_uuid() << "}\n";
    }

    /* Removing a resource */
    remove_resource(samples::json_resource);

    /* Updating the device in Edge Module */
    update_location(samples::json_device);

    /* Sending data of sensors */
    send_resource_data(samples::json_resource_data);

    return 0;
}