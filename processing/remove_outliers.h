//
// Created by makleyston on 28/04/23.
//

#ifndef UFCITY_REMOVE_OUTLIERS_H
#define UFCITY_REMOVE_OUTLIERS_H

namespace proc {
    void remove_outliers_handler(std::vector<double>& _values);
    void remove_outliers_iqr(std::vector<double>& data, const double threshold);
    void remove_outliers_percentile(std::vector<double>& data, const double lower_percentile, const double upper_percentile);
    void remove_outliers_zscore(std::vector<double>& data, double threshold);
    void remove_outliers_tukey(std::vector<double>& data, double k);
} // proc

#endif //UFCITY_REMOVE_OUTLIERS_H
