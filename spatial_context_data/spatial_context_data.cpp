//
// Created by makleyston on 24/08/22.
//

#include "spatial_context_data.h"

namespace ufcity_db {

    ufcity::location * spatial_context_data::get_location(){
        return this->location;
    }

    void spatial_context_data::save_location(ufcity::location * l){
        this->location = l;
    }

    spatial_context_data::spatial_context_data() = default;

    spatial_context_data* spatial_context_data::instance = nullptr;
    spatial_context_data* spatial_context_data::get_instance(){
        if (instance == nullptr){
            instance = new spatial_context_data();
        }
        return instance;
    }

} // ufcity_db