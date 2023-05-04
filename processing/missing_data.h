//
// Created by makleyston on 28/04/23.
//

#ifndef UFCITY_MISSING_DATA_H
#define UFCITY_MISSING_DATA_H

#include <vector>
#include "../model/resource.h"

namespace proc {

    void missing_data_handler(std::vector<double>& _values);

    void mean_impute(std::vector<double>& data);
    void median_impute(std::vector<double>& data);
    void mode_impute(std::vector<double>& data);
    void locf_impute(std::vector<double>& data);
    void nocb_impute(std::vector<double>& data);
    void interpolation_impute(std::vector<double>& data);

} // proc

#endif //UFCITY_MISSING_DATA_H
