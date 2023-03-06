//
// Created by makleyston on 24/08/22.
//

#include "device_data.h"

namespace ufcity_db {

    ufcity::device * device_data::get_device(){
        return this->device;
    }

    void device_data::save_device(ufcity::device * location){
        this->device = location;
    }

    device_data::device_data() = default;

    device_data* device_data::instance = nullptr;
    device_data* device_data::get_instance(){
        if (instance == nullptr){
            instance = new device_data();
        }
        return instance;
    }

    int device_data::add_spatial_context_data(const std::string& semantic) {
        //TODO
        return 0;
    }

} // ufcity_db