//
// Created by makleyston on 28/04/23.
//

#include <iostream>
#include "remove_outliers_config.h"
#include "data_aggregation_config.h"
#include "methods.h"

void ufcity::remove_outliers_config::set_method(char _method) {
    this->method = _method;
}

void ufcity::remove_outliers_config::set_threshold(double _threshold) {
    this->threshold = _threshold;
}


std::string ufcity::remove_outliers_config::get_method_str() {
    if(!this->method && this->method=='\0') {
        std::cout << "Method not yet chosen." << std::endl;
        return nullptr;
    }
    switch (this->method) {
        case methods::Z_SCORE_METHOD:
            return "Z-SCORE METHOD";
        case methods::IQR_METHOD:
            return "IQR METHOD";
        case methods::PERCENTILE_METHOD:
            return "PERCENTILE METHOD";
        case methods::TUKEY_METHOD:
            return "TUKEY'S METHOD";
        case methods::NONE:
            return "NONE";
    }
    return "";
}

char ufcity::remove_outliers_config::get_method_char() {
    return this->method;
}

ufcity::remove_outliers_config::remove_outliers_config() {

}

void ufcity::remove_outliers_config::set_lower_percentile(double _lower) {
    this->lower_percentile = _lower;
}

void ufcity::remove_outliers_config::set_upper_percentile(double _upper) {
    this->upper_percentile = _upper;
}






