//
// Created by makleyston on 07/07/22.
//

#include "../ufcity_interface.h"
#include "ext/observer_client.h"
#include "ext/json_data_sample.hpp"
#include "../communcation/message_receiver/message_receiver.h"

using namespace ufcity_interface;

int main(){

    /* Initializing the Edge Module */
    init(samples::json_spatial_context_data, "localhost");
//
//    /* Registering a resource */
//    register_resource(samples::json_resource);
//
//    /* Printing all stored resources */
//    auto * map = get_resources_map();
////    for (auto const &pair: *map) {
////        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
////    }
//
//    /* Removing a resource */
//    remove_resource(samples::json_resource);
//
//    /* Updating the device in Edge Module */
//    update_location(samples::json_spatial_context_data);
//
//    /* Sending data of sensors */
//    send_resource_data(samples::json_resource_data);
//
//    /* Testing the observer client */
//    observer_client * observerClient = new observer_client(123);
//    register_observer(observerClient);
//    ufcity::message_receiver::get_instance()->receive_message("Test OK!");
//
//    /* Removing an observer client */
//    remove_observer(observerClient);
//

    return 0;
}