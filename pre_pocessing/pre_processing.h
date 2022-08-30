//
// Created by makleyston on 26/08/22.
//

#ifndef UFCITY_PRE_PROCESSING_H
#define UFCITY_PRE_PROCESSING_H

#include <string>

namespace pre_proc {

    int handler(const std::string& semantic);

    int remove_outliers(const std::string& semantic);

    int missing_data_insertion(const std::string& semantic);

}

#endif //UFCITY_PRE_PROCESSING_H
