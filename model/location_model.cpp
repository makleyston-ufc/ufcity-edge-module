//
// Created by makleyston on 23/08/22.
//

#include "location_model.h"

namespace ufcity {

//    ufcity::location_model(std::string lat const, std::stringlng const){}

    std::string ufcity::location_model::get_lat() {
        return this->lat;
    }

    std::string ufcity::location_model::get_lng() {
        return this->lng;
    }

    void ufcity::location_model::set_lat(std::string l) {
        this->lat = l;
    }

    void ufcity::location_model::set_lng(std::string l) {
        this->lng = l;
    }

} // ufcity