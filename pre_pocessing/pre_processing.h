//
// Created by makleyston on 26/08/22.
//

#ifndef UFCITY_PRE_PROCESSING_H
#define UFCITY_PRE_PROCESSING_H

#include <string>

namespace pre_proc {

    int handler(std::string semantic);

    int remove_outliers(std::string semantic);

    int missing_data_insertion(std::string semantic);

}

#endif //UFCITY_PRE_PROCESSING_H
