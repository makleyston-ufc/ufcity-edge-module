//
// Created by makleyston on 26/08/22.
//

#ifndef UFCITY_PROCESSING_H
#define UFCITY_PROCESSING_H

#include <string>
#include "../model/resource.h"

namespace proc {

    int handler(const ufcity::resource * _resource);
    int data_filter(const ufcity::resource * _resource);
    int data_grouping(const ufcity::resource * _resource);

} // proc

#endif //UFCITY_PROCESSING_H
