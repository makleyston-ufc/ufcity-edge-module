//
// Created by makleyston on 25/08/22.
//

#ifndef UFCITY_RESOURCES_MAP_H
#define UFCITY_RESOURCES_MAP_H

#include <unordered_map>
#include <string>
#include <iostream>
#include "../../model/resource.h"

namespace ufcity_db {

    class resources_map {
    private:
        //The key is UUID and the value is unordered_map<resource *, string semantic>
        std::unordered_map<std::string, const ufcity::resource *> * map_resource;
        resources_map();

    public:
        static resources_map * get_instance();
        static resources_map* instance;

        bool find_by_uuid_resource(const std::string& uuid) const;
        ufcity::resource * get_resource_by_uuid(const std::string& uuid);
        std::unordered_map<std::string, const ufcity::resource *> * get_resources_map() ;
        int register_resource(ufcity::resource * _resource);
        int remove_by_uuid(const std::string& uuid) const;

        void send_register_to_fog(ufcity::resource * _resource);
        void send_register_to_fog(const std::string& uuid_resource);

        void send_data_to_fog(ufcity::resource * _resource);
    };

} // ufcity_db

#endif //UFCITY_RESOURCES_MAP_H
