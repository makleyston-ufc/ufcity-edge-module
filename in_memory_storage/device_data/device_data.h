//
// Created by makleyston on 24/08/22.
//

#ifndef UFCITY_DEVICE_DATA_H
#define UFCITY_DEVICE_DATA_H

#include "../../model/device.h"

namespace ufcity_db {

    class device_data {
    private:
        ufcity::device * device{};
        static device_data* instance;
        device_data();

    public:
        static device_data* get_instance();

        ufcity::device * get_device();
        void save_device(ufcity::device * d);
        static int add_spatial_context_data(const std::string& semantic);
    };

} // ufcity_db

#endif //UFCITY_DEVICE_DATA_H
