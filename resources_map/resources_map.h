//
// Created by makleyston on 25/08/22.
//

#ifndef UFCITY_RESOURCES_MAP_H
#define UFCITY_RESOURCES_MAP_H

#include <unordered_map>
#include <string>
#include <iostream>
#include "../model/resource.h"
//#include "../util/util.h"

namespace ufcity_db {

    class resources_map {
    private:
        std::unordered_map<std::string , std::string> * map;
        resources_map();

    public:
        static resources_map * get_instance();
        static resources_map* instance;

        bool find_resource_by_uuid(std::string uuid) const;
        std::string get_resource_by_uuid(std::string uuid) const;
        int register_resource(std::string uuid, std::string semantic) const;
        int remove_resource(std::string uuid) const;
    };

} // ufcity_db

#endif //UFCITY_RESOURCES_MAP_H
