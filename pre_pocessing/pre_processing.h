//
// Created by makleyston on 26/08/22.
//

#ifndef UFCITY_PRE_PROCESSING_H
#define UFCITY_PRE_PROCESSING_H

#include <string>
#include "../model/resource.h"

namespace pre_proc {

    int handler(const ufcity::resource * _resource);

    int remove_outliers(const ufcity::resource * semantic);

    int missing_data_insertion(const ufcity::resource * semantic);

}

#endif //UFCITY_PRE_PROCESSING_H
