//
// Created by makleyston on 23/08/22.
//

#ifndef UFCITY_DEVICE_H
#define UFCITY_DEVICE_H

#include <string>
#include "../in_memory_storage/device_data/location.h"

namespace ufcity {

    class device {
    private:
        ufcity::location * location;
        std::string uuid_device;

    public:
        device();
        std::string get_uuid_device();
        ufcity::location * get_location();
        void set_location(ufcity::location * _location);
        void set_uuid_device(std::string uuid_device);
        std::string to_string();
    };

} // ufcity


#endif //UFCITY_DEVICE_H
