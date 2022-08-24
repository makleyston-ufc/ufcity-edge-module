//
// Created by makleyston on 07/07/22.
//
#include <iostream>
#include "../ufcity_interface.h"


#include "../spatial_context_data/spatial_context_data.h"

using namespace ufcity_interface;

int main(){

    /* Inicializando o Edge Module */
    int r = init(json_spatial_data);
    std::cout << r << std::endl;














//    orchestrator* orchestrator = orchestrator::get_instance();
//    std::cout << orchestrator << std::endl;

//    ufcity::location_model * location = new ufcity::location_model("latXXX", "lngYYY");
//    std::cout << location->get_lat() + " ## " + location->get_lng() << std::endl;

//    init("latXXX, lngYYY");
//    register_resource("test");

    return 0;
}