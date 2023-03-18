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
        std::string device_uuid;
    public:
        std::string get_device_uuid();
        ufcity::location * get_location();
        void set_location(ufcity::location * _location);
        void set_device_uuid(std::string device_uuid);
    };

} // ufcity


#endif //UFCITY_DEVICE_H
