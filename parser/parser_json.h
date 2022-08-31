//new spatial_context_data();
// Created by makleyston on 24/08/22.
//

#ifndef UFCITY_PARSER_JSON_H
#define UFCITY_PARSER_JSON_H

#include "../model/location.h"
#include "../model/resource.h"
#include "lib/json.hpp"
#include "../error/error_list.h"


#include <iostream>

namespace ufcity {

    location * location_from_json(const std::string& data);
    resource * resource_from_json(const std::string& data);

}

#endif //UFCITY_PARSER_JSON_H
