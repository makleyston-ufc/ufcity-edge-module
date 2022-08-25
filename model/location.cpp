//
// Created by makleyston on 23/08/22.
//

#include "location.h"

namespace ufcity {

//    ufcity::location(std::string lat const, std::stringlng const){}

    std::string ufcity::location::get_lat() {
        return this->lat;
    }

    std::string ufcity::location::get_lng() {
        return this->lng;
    }

    void ufcity::location::set_lat(std::string l) {
        this->lat = l;
    }

    void ufcity::location::set_lng(std::string l) {
        this->lng = l;
    }

} // ufcity