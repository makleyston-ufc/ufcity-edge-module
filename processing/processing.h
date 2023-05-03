//
// Created by makleyston on 26/08/22.
//

#ifndef UFCITY_PROCESSING_H
#define UFCITY_PROCESSING_H

#include <string>
#include <vector>
#include "../model/resource.h"

namespace proc {

    std::vector<ufcity::resource *> handler(std::vector<std::vector<ufcity::resource *>>& _data);

} // proc

#endif //UFCITY_PROCESSING_H
