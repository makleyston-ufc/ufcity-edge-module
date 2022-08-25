//
// Created by makleyston on 07/07/22.
//
#include <iostream>
#include "../ufcity_interface.h"
#include "json_data_sample.hpp"

using namespace ufcity_interface;

int main(){

    int r; //return

    /* Initializing the Edge Module */
    r = init(samples::json_spatial_data);
//    std::cout << r << std::endl;

    /* Registering a resource */
    r = register_resource(samples::json_register_resource);
//    std::cout << r << std::endl;


    return 0;
}