//
// Created by makleyston on 03/05/23.
//

#ifndef UFCITY_DATA_AGGREGATION_H
#define UFCITY_DATA_AGGREGATION_H

#include <vector>
#include <string>

namespace proc {

    double data_aggregation_handler(std::vector<double>& _values);
    std::string data_aggregation_handler(std::vector<std::string>& _values);
    double max_aggregation(std::vector<double>& _values);
    double min_aggregation(std::vector<double>& _values);
    double mean_aggregation(std::vector<double>& _values);
    double median_aggregation(std::vector<double>& _values);
    std::string most_frequency(std::vector<std::string> _values);

} // proc

#endif //UFCITY_DATA_AGGREGATION_H
