//
// Created by makleyston on 28/04/23.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#include "missing_data.h"

namespace proc {

    void mean_impute(std::vector<double>& data){
        int n = data.size();
        if (n == 0) return;

        double sum = 0;
        for (double x : data) sum += x;
        double mean = sum / n;

        for (int i = 0; i < n; i++) {
            if (std::isnan(data[i])) {
                data[i] = mean;
            }
        }

    }
    void median_impute(std::vector<double>& data){
        int n = data.size();
        double median = 0;
        std::sort(data.begin(), data.end());
        if (n % 2 == 0) {
            median = (data[n/2 - 1] + data[n/2]) / 2;
        } else {
            median = data[n/2];
        }

        for (int i = 0; i < n; i++) {
            if (std::isnan(data[i])) {
                data[i] = median;
            }
        }
    }
    void mode_impute(std::vector<double>& data){
        int n = data.size();
        double mode = 0;
        int maxCount = 0;
        for (double x : data) {
            int count = 0;
            for (double y : data) {
                if (x == y) count++;
            }
            if (count > maxCount) {
                maxCount = count;
                mode = x;
            }
        }
        for (int i = 0; i < n; i++) {
            if (std::isnan(data[i])) {
                data[i] = mode;
            }
        }
    }
    void locf_impute(std::vector<double>& data){
        double prev_value = data[0];
        for (int i = 1; i < data.size(); i++) {
            if (std::isnan(data[i])) {
                data[i] = prev_value;
            }
            else {
                prev_value = data[i];
            }
        }
    }
    void nocb_impute(std::vector<double>& data){
        double next_value = data[data.size()-1];
        for (int i = data.size()-2; i >= 0; i--) {
            if (std::isnan(data[i])) {
                data[i] = next_value;
            }
            else {
                next_value = data[i];
            }
        }
    }

    // Linear interpolation function
    double linear_interpolation(double x0, double y0, double x1, double y1, double x) {
        return y0 + (y1 - y0) * ((x - x0) / (x1 - x0));
    }

    void interpolation_impute(std::vector<double>& data){
        // Iterate over the data vector
        for (int i = 0; i < data.size(); i++) {
            // If the current value is missing (represented by NaN), try to interpolate
            if (std::isnan(data[i])) {
                // Search for the next non-missing value to the right
                int j = i + 1;
                while (j < data.size() && std::isnan(data[j])) {
                    j++;
                }
                // If no non-missing value to the right is found, search to the left
                if (j == data.size()) {
                    int k = i - 1;
                    while (k >= 0 && std::isnan(data[k])) {
                        k--;
                    }
                    // If no non-missing value to the left is found, set the value to 0
                    if (k < 0) {
                        data[i] = 0;
                    }
                        // If a non-missing value to the left is found, set the missing value to that value
                    else {
                        data[i] = data[k];
                    }
                }
                    // If a non-missing value to the right is found, interpolate using the linear interpolation function
                else {
                    data[i] = linear_interpolation(j, data[j], i, data[i-1], i);
                }
            }
        }
    }

} // proc