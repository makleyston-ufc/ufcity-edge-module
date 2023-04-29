//
// Created by makleyston on 28/04/23.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#include "remove_outliers.h"

namespace proc {

    void remove_outliers_iqr(std::vector<double>& data, const double threshold) {
        std::sort(data.begin(), data.end());
        const size_t n = data.size();
        const size_t q1_index = static_cast<size_t>(std::floor(0.25 * (n + 1)));
        const size_t q3_index = static_cast<size_t>(std::floor(0.75 * (n + 1)));
        const double q1 = data[q1_index - 1];
        const double q3 = data[q3_index - 1];
        const double iqr = q3 - q1;
        const double lower_threshold = q1 - threshold * iqr;
        const double upper_threshold = q3 + threshold * iqr;

        auto new_end = std::remove_if(data.begin(), data.end(),
                                      [lower_threshold, upper_threshold](const double value) {
                                          return value < lower_threshold || value > upper_threshold;
                                      });

        data.erase(new_end, data.end());
    }

    void remove_outliers_percentile(std::vector<double>& data, const double lower_percentile, const double upper_percentile) {
        std::sort(data.begin(), data.end());
        const size_t n = data.size();
        const size_t lower_index = static_cast<size_t>(std::floor(lower_percentile * (n - 1)));
        const size_t upper_index = static_cast<size_t>(std::floor(upper_percentile * (n - 1)));
        const double lower_threshold = data[lower_index];
        const double upper_threshold = data[upper_index];

        auto new_end = std::remove_if(data.begin(), data.end(),
                                      [lower_threshold, upper_threshold](const double value) {
                                          return value < lower_threshold || value > upper_threshold;
                                      });

        data.erase(new_end, data.end());
    }

    double mean(std::vector<double>& vec) {
        double sum = 0;
        for (int i = 0; i < vec.size(); i++) {
            sum += vec[i];
        }
        return sum / vec.size();
    }

    double stdev(std::vector<double>& vec) {
        double sum = 0;
        double mean_val = mean(vec);
        for (int i = 0; i < vec.size(); i++) {
            sum += pow(vec[i] - mean_val, 2);
        }
        return sqrt(sum / vec.size());
    }

    void remove_outliers_zscore(std::vector<double>& vec, double threshold) {
        double mean_val = mean(vec);
        double stdev_val = stdev(vec);
        for (int i = 0; i < vec.size(); i++) {
            double zscore = (vec[i] - mean_val) / stdev_val;
            if (abs(zscore) > threshold) {
                vec.erase(vec.begin() + i);
                i--;
            }
        }
    }

    void remove_outliers_tukey(std::vector<double>& data, double k) {
        // Sort the data in ascending order
        std::sort(data.begin(), data.end());

        // Calculate the quartiles manually
        int n = data.size();
        int q1_index = std::floor((n + 1) / 4.0) - 1;
        int q2_index = std::floor((n + 1) / 2.0) - 1;
        int q3_index = std::floor(3 * (n + 1) / 4.0) - 1;
        double q1 = data[q1_index];
        double q2 = data[q2_index];
        double q3 = data[q3_index];

        // Calculate the interquartile range (IQR)
        double iqr = q3 - q1;

        // Define the lower and upper bounds for outliers
        double lower_bound = q1 - k * iqr;
        double upper_bound = q3 + k * iqr;

        // Remove any data points outside the bounds
        auto end_iter = std::remove_if(data.begin(), data.end(), [lower_bound, upper_bound](double x) {
            return (x < lower_bound) || (x > upper_bound);
        });
        data.erase(end_iter, data.end());
    }


} // proc