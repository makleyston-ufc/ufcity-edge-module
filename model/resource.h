//
// Created by makleyston on 07/07/22.
//

#ifndef UFCITY_RESOURCE_H
#define UFCITY_RESOURCE_H

#include <string>
#include <unordered_map>
#include <iostream>
#include "../in_memory_storage/device_data/location.h"

namespace ufcity {

    class resource {
    private:
        std::string resource_uuid;
        ufcity::location * location;

        std::unordered_map<std::string, std::unordered_map<std::string, std::string>> * services_uuid_map{}; //<service_uuid, <data_tag, value>>

    public:
        explicit resource(std::string resource_uuid, std::unordered_map<std::string, std::unordered_map<std::string, std::string>> * map);

        std::string get_resource_uuid() const;
        std::unordered_map<std::string, std::unordered_map<std::string, std::string>> * get_services();
        std::unordered_map<std::string, std::string> get_service_by_uuid(const std::string& uuid);
        void set_location(ufcity::location * _location);
        ufcity::location * get_location();
        std::string to_string();

        void print(){
            std::cout <<         "resource_uuid:" << this->resource_uuid << std::endl;
            std::cout <<         "qt services..:" << this->services_uuid_map->size() << std::endl;
            for(const auto& service : *this->services_uuid_map){
                std::cout <<     "service_uuid.:" << service.first << std::endl;
                for(const auto& data : service.second){
                    std::cout << "data_tag.....:" << data.first << std::endl;
                    std::cout << "value........:" << data.second << std::endl;
                }
            }
        }

    };

} // ufcity

#endif //UFCITY_RESOURCE_H
