//
// Created by makleyston on 24/08/22.
//

#ifndef UFCITY_SPATIAL_CONTEXT_DATA_H
#define UFCITY_SPATIAL_CONTEXT_DATA_H

#include "../../model/device.h"

namespace ufcity_db {

    class spatial_context_data {
    private:
        ufcity::device * device{};
        static spatial_context_data* instance;
        spatial_context_data();

    public:
        static spatial_context_data* get_instance();

        ufcity::device * get_device();
        void save_device(ufcity::device * d);
        static int add_spatial_context_data(const std::string& semantic);
    };

} // ufcity_db

#endif //UFCITY_SPATIAL_CONTEXT_DATA_H
