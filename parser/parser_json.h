//new spatial_context_data();
// Created by makleyston on 24/08/22.
//

#ifndef UFCITY_PARSER_JSON_H
#define UFCITY_PARSER_JSON_H

#include "../model/location.h"
#include "../model/resource.h"

namespace ufcity {

    location * location_from_json(const std::string& string);
    resource * resource_from_json(const std::string& string);

}

#endif //UFCITY_PARSER_JSON_H
