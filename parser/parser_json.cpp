//
// Created by makleyston on 24/08/22.
//

#include "parser_json.h"

using json = nlohmann::json;

namespace ufcity {

    location * location_from_json(const std::string& data) {

        try {
            auto j = json::parse(data);
            auto *l = new location();
            l->set_device_uuid(j.at("device_uuid"));
            l->set_lat(j.at("location").at("lat"));
            l->set_lng(j.at("location").at("lng"));
            return l;
        } catch (int error){
            return nullptr;
        }
    }


    resource * resource_from_json(const std::string& data_json){
        auto j = json::parse(data_json);

        auto *services_uuid_map = new std::unordered_map<std::string, std::unordered_map<std::string, std::string>>(); //service_uuid <-> values

        for(auto service : j.at("services")){
            auto *values = new std::unordered_map<std::string, std::string>(); //data_tag <-> value
            for(auto data : service.at("data")){
                values->insert(std::pair<std::string, std::string>(data.at("tag"), data.at("value")));
            }
            services_uuid_map->insert(
                    std::pair<std::string, std::unordered_map<std::string, std::string>>(service.at("service_uuid"), *values));
        }

        auto *_resource = new resource(j.at("resource_uuid"), services_uuid_map);
        return _resource;

    }

} // ufcity

//    nlohmann::json ex1 = nlohmann::json::parse(samples::json_spatial_context_data);
//    nlohmann::json ex2 = nlohmann::json::parse(samples::json_resource);
//    nlohmann::json ex3 = nlohmann::json::parse(samples::json_resource_data);
//
//    std::cout << ex1.at("device_uuid") << std::endl;
//    std::cout << ex2.at("device_uuid") << std::endl;
//    std::cout << ex3.at("resource_uuid") << std::endl;