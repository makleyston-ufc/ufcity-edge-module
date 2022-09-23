//
// Created by makleyston on 23/08/22.
//

#include "device.h"

#include <utility>

namespace ufcity {

    std::string ufcity::device::get_lat() {
        return this->lat;
    }

    std::string ufcity::device::get_lng() {
        return this->lng;
    }

    void ufcity::device::set_lat(std::string l) {
        this->lat = std::move(l);
    }

    void ufcity::device::set_lng(std::string l) {
        this->lng = std::move(l);
    }

    void ufcity::device::set_device_uuid(std::string _device_uuid) {
        this->device_uuid = std::move(_device_uuid);
    }

    std::string ufcity::device::get_device_uuid() {
        return this->device_uuid;
    }


} // ufcity