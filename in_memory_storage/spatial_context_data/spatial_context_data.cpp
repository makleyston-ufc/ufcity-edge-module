//
// Created by makleyston on 24/08/22.
//

#include "spatial_context_data.h"

namespace ufcity_db {

    ufcity::device * spatial_context_data::get_device(){
        return this->device;
    }

    void spatial_context_data::save_device(ufcity::device * location){
        this->device = location;
    }

    spatial_context_data::spatial_context_data() = default;

    spatial_context_data* spatial_context_data::instance = nullptr;
    spatial_context_data* spatial_context_data::get_instance(){
        if (instance == nullptr){
            instance = new spatial_context_data();
        }
        return instance;
    }

    int spatial_context_data::add_spatial_context_data(const std::string& semantic) {
        //TODO
        return 0;
    }

} // ufcity_db