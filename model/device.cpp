//
// Created by makleyston on 23/08/22.
//

#include "device.h"
#include "../parser/parser_json.h"
#include "../util/util.h"
#include <utility>

namespace ufcity {

    void ufcity::device::set_uuid_device(std::string uuid_device) {
        this->uuid_device = std::move(uuid_device);
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

    device::device() {
        this->set_uuid_device(uuid_generator());
    }


} // ufcity