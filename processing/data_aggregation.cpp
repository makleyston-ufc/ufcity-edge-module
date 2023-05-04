//
// Created by makleyston on 03/05/23.
//

#include "data_aggregation.h"
#include "../model/config/methods.h"
#include "../orchestrator/orchestrator.h"
#include <vector>
#include <algorithm>
#include <stdexcept>

namespace proc {


    double max_aggregation(std::vector<double>& _values) {
        // Check if the vector is empty
        if (_values.empty()) {
            throw std::invalid_argument("Empty vector passed to max_aggregation function.");
        }

        // Find the maximum element in the vector
        double max_value = *std::max_element(_values.begin(), _values.end());

        return max_value;
    }

    double min_aggregation(std::vector<double>& _values) {
        // Check if the vector is empty
        if (_values.empty()) {
            throw std::invalid_argument("Empty vector passed to min_aggregation function.");
        }

        // Find the minimum element in the vector
        double min_value = *std::min_element(_values.begin(), _values.end());

        return min_value;
    }

    double mean_aggregation(std::vector<double>& _values) {
        // Check if the vector is empty
        if (_values.empty()) {
            throw std::invalid_argument("Empty vector passed to mean_aggregation function.");
        }

        // Calculate the sum of all elements in the vector
        double sum = 0.0;
        for (double value : _values) {
            sum += value;
        }

        // Calculate the mean
        double mean = sum / _values.size();

        return mean;
    }

    double median_aggregation(std::vector<double>& _values) {
        // Check if the vector is empty
        if (_values.empty()) {
            throw std::invalid_argument("Empty vector passed to median_aggregation function.");
        }

        // Sort the vector
        std::sort(_values.begin(), _values.end());

        // Find the median value
        double median;
        if (_values.size() % 2 == 0) {
            median = (_values[_values.size()/2 - 1] + _values[_values.size()/2]) / 2.0;
        } else {
            median = _values[_values.size()/2];
        }

        return median;
    }

    double data_aggregation_handler(std::vector<double> &_values) {
        auto * config = ufcity::orchestrator::get_instance()->get_config();
        switch (config->get_data_aggregation_config()->get_method_char()) {
            case methods::MAX_AGGREGATION_METHOD:
                return max_aggregation(_values);
            case methods::MIN_AGGREGATION_METHOD:
                return min_aggregation(_values);
            case methods::MEAN_AGGREGATION_METHOD:
                return mean_aggregation(_values);
            case methods::MEDIAN_AGGREGATION_METHOD:
                return median_aggregation(_values);
        }
        return -1;
    }

    std::string most_frequency(std::vector<std::string> _values) {
        // Create a map to store the frequency of each string
        std::unordered_map<std::string, int> freq_map;

        // Count the frequency of each string
        for (const auto& value : _values) {
            freq_map[value]++;
        }

        // Find the string with the highest frequency
        int max_freq = 0;
        std::string most_freq_value;
        for (const auto& pair : freq_map) {
            if (pair.second > max_freq) {
                max_freq = pair.second;
                most_freq_value = pair.first;
            }
        }

        return most_freq_value;
    }


    std::string data_aggregation_handler(std::vector<std::string> &_values) {
        return most_frequency(_values);
    }

} // proc