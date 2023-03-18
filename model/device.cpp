//
// Created by makleyston on 23/08/22.
//

#include "device.h"

#include <utility>

namespace ufcity {

    void ufcity::device::set_device_uuid(std::string _device_uuid) {
        this->device_uuid = std::move(_device_uuid);
    }

    std::string ufcity::device::get_device_uuid() {
        return this->device_uuid;
    }

    ufcity::location * ufcity::device::get_location(){
        return this->location;
    }

    void ufcity::device::set_location(ufcity::location * _location){
        this->location = _location;
    }

} // ufcity