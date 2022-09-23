//
// Created by makleyston on 23/08/22.
//

#ifndef UFCITY_DEVICE_H
#define UFCITY_DEVICE_H

#include <string>

namespace ufcity {

    class device {
    private:
        std::string lat;
        std::string lng;
        std::string device_uuid;
    public:

        std::string get_lat();
        std::string get_lng();
        std::string get_device_uuid();
        void set_lat(std::string lat);
        void set_lng(std::string lng);
        void set_device_uuid(std::string device_uuid);
    };

} // ufcity


#endif //UFCITY_DEVICE_H
