//new spatial_context_data();
// Created by makleyston on 24/08/22.
//

#ifndef UFCITY_PARSER_JSON_H
#define UFCITY_PARSER_JSON_H

#include "../model/device.h"
#include "../model/resource.h"
#include "lib/json.hpp"
#include "../error/error_list.h"


#include <iostream>

namespace ufcity {

    device * device_from_json(const std::string& data);
    resource * resource_from_json(const std::string& data);
    std::string resource_to_json(ufcity::resource * _device);
    std::string device_to_json(ufcity::resource * _device);

}

#endif //UFCITY_PARSER_JSON_H
