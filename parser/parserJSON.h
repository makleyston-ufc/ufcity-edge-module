//new spatial_context_data();
// Created by makleyston on 24/08/22.
//

#ifndef UFCITY_PARSERJSON_H
#define UFCITY_PARSERJSON_H

#include "../model/location_model.h"

namespace ufcity {

    location_model *fromJSON(std::string string);
}

#endif //UFCITY_PARSERJSON_H
