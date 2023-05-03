//
// Created by makleyston on 29/04/23.
//

#ifndef UFCITY_BUFFER_H
#define UFCITY_BUFFER_H

#include <vector>
#include <chrono>
#include "../../model/resource.h"

namespace ufcity_db {

    class buffer {
    private:
        static buffer* instance;
        buffer();
        std::vector<std::vector<ufcity::resource *>> selected_resources;
        std::vector<std::chrono::time_point<std::chrono::system_clock>> times;
        int get_index_by_uuid_resource(std::string uuid_resource);

    public:
        static buffer* get_instance();
        void add_resource(ufcity::resource * _resource);
        long number_items_in_buffer(std::string uuid_resource);
        std::vector<std::vector<ufcity::resource *>> get_resource_buffer();

        std::vector<std::vector<ufcity::resource *>> fixed_size_function(long size);
        std::vector<std::vector<ufcity::resource *>> at_least_time_function(long time);
        std::vector<std::vector<ufcity::resource *>> al_least_time_and_size_function(long time, long size);
        std::vector<std::vector<ufcity::resource *>> happens_first_function(long time, long size);
    };

} // ufcity_db

#endif //UFCITY_BUFFER_H
