//
// Created by makleyston on 24/08/22.
//

#ifndef UFCITY_DEVICE_DATA_H
#define UFCITY_DEVICE_DATA_H

#include "../../model/device.h"
#include "../../model/resource.h"

namespace ufcity_db {

    class device_data {
    private:
        ufcity::device * device{};
        static device_data* instance;
        device_data();

    public:
        static device_data* get_instance();

        ufcity::device * get_device();
        void save_device(ufcity::device * _device);
        int add_spatial_context_data(ufcity::resource * _resource);
    };

} // ufcity_db

#endif //UFCITY_DEVICE_DATA_H
