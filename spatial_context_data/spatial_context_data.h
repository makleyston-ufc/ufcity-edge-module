//
// Created by makleyston on 24/08/22.
//

#ifndef UFCITY_SPATIAL_CONTEXT_DATA_H
#define UFCITY_SPATIAL_CONTEXT_DATA_H

#include "../model/location.h"

namespace ufcity_db {

    class spatial_context_data {
    private:
        ufcity::location * location;
        static spatial_context_data* instance;
        spatial_context_data();

    public:
        static spatial_context_data* get_instance();

        ufcity::location * get_location();
        void save_location(ufcity::location * location);
        void add_spatial_context_data();
    };

} // ufcity_db

#endif //UFCITY_SPATIAL_CONTEXT_DATA_H
