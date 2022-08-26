//
// Created by makleyston on 24/08/22.
//

#include "parser_json.h"

namespace ufcity {

    location * location_from_json(const std::string& string) {
        //TODO
        auto *l = new location();
        l->set_lat("LAT-XXX");
        l->set_lng("LNG-YYY");
        return l;
    }


    resource * resource_from_json(const std::string& string){
        //TODO
        auto * services_uuid_map = new std::unordered_map<std::string, std::unordered_map<std::string, std::string>>();
        auto * temp_data = new std::unordered_map<std::string, std::string>();
        temp_data->insert(std::pair<std::string, std::string>("temp_tag", "23"));
        services_uuid_map->insert(std::pair<std::string, std::unordered_map<std::string, std::string>>("temp_uuid", *temp_data));

        auto * rr = new resource("d_111", "r_222", services_uuid_map);
        return rr;
    }

    } // ufcity