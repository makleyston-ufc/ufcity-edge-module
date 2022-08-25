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
        auto * services_uuid_list = new std::vector<std::string>();
        services_uuid_list->push_back("s_123");
        services_uuid_list->push_back("s_1321");
        auto * rr = new resource("d_111", "r_222", services_uuid_list);
        return rr;
    }

    } // ufcity