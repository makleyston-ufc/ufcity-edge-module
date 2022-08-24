//
// Created by makleyston on 24/08/22.
//

#include "parserJSON.h"
#include <iostream>

namespace ufcity {

    location_model * fromJSON(std::string string){
    //TODO
    location_model * location = new location_model();
    location->set_lat("LAT-XXX");
    location->set_lng("LNG-YYY");
    return location;
}

} // ufcity