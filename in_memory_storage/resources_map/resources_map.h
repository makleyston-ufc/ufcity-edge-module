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
        //The key is UUID and the value is a unordered_map<resource *, string semantic>
        std::unordered_map<std::string, const ufcity::resource *> * map_resource;
        std::unordered_map<std::string, const std::string> * map_semantic;
        resources_map();

    public:
        static resources_map * get_instance();
        static resources_map* instance;

        bool find_resource_uuid(const std::string& uuid) const;
        bool find_semantic_uuid(const std::string& uuid) const;

        const ufcity::resource * get_resource_by_uuid(const std::string& uuid);
        std::string get_semantic_by_uuid(const std::string& uuid) const;

        std::unordered_map<std::string, const ufcity::resource *> * get_resources_map() ;
        std::unordered_map<std::string, const std::string> * get_semantics_map() ;

        int register_resource(const ufcity::resource * _resource, const std::string& semantic) const;

        int remove_by_uuid(const std::string& uuid) const;
    };

} // ufcity_db

#endif //UFCITY_RESOURCES_MAP_H
