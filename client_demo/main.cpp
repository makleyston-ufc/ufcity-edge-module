//
// Created by makleyston on 07/07/22.
//

#include <iostream>
#include "../ufcity_interface.h"
#include "json_data_sample.hpp"

using namespace ufcity_interface;

int main(){

    /* Initializing the Edge Module */
    init(samples::json_spatial_context_data);

    /* Registering a resource */
    register_resource(samples::json_resource);

    /* Printing all stored resources */
    std::unordered_map<std::string, std::string> * map = get_resources_map();
    for (auto const &pair: *map) {
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
    }

    /* Removing a resource */
//    remove_resource(samples::json_resource);

    /* Updating the location in Edge Module */
    location_update(samples::json_spatial_context_data);

    /* Sending data of sensors */
//    send_resource_data(samples::json_resource_data);

//    int a = 0 || 0 || 0;
//    std::cout << a << std::endl;

    return 0;
}