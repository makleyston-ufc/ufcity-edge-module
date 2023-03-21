//
// Created by makleyston on 17/03/23.
//

#include "location.h"

namespace ufcity {

    std::string ufcity::location::get_lat(){
        return this->lat;
    }

    std::string ufcity::location::get_lng(){
        return this->lng;
    }

    std::string ufcity::location::get_alt(){
        return this->alt;
    }

    void ufcity::location::set_lat(const std::string& _lat){
        this->lat = _lat;
    }

    void ufcity::location::set_lng(const std::string& _lng){
        this->lng = _lng;
    }

    void ufcity::location::set_alt(const std::string& _alt){
        this->alt = _alt;
    }

} // ufcity