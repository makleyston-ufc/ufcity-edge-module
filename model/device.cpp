//
// Created by makleyston on 23/08/22.
//

#include "device.h"
#include "../parser/parser_json.h"

#include <utility>

namespace ufcity {

    void ufcity::device::set_uuid_device(std::string device_uuid) {
        this->uuid_device = std::move(device_uuid);
    }

    std::string ufcity::device::get_uuid_device() {
        return this->uuid_device;
    }

    ufcity::location * ufcity::device::get_location(){
        return this->location;
    }

    void ufcity::device::set_location(ufcity::location * _location){
        this->location = _location;
    }

    std::string ufcity::device::to_string() {
        auto _json = device_to_json(this);
        return _json;
    }

} // ufcity