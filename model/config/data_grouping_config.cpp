//
// Created by makleyston on 28/04/23.
//

#include <iostream>
#include "data_grouping_config.h"
#include "methods.h"

void ufcity::data_grouping_config::set_method(char _method) {
    this->method = _method;
}

void ufcity::data_grouping_config::set_size(int _size) {
    this->size = _size;
}

void ufcity::data_grouping_config::set_time(int _sec) {
    this->time = _sec;
}

std::string ufcity::data_grouping_config::get_method_str() const {
    if(!this->method) {
        std::cout << "Method not yet chosen." << std::endl;
        return nullptr;
    }
    switch (this->method) {
        case methods::AT_LEAST_TIME_GROUPING:
            return "AT LEAST X SEC (TIME) METHOD";
        case methods::AT_LEAST_TIME_AND_SIZE_GROUPING:
            return "AT LEAST X SEC (TIME) AND Y SIZE METHOD";
        case methods::FIXED_SIZE_GROUPING:
            return "SIZE METHOD";
        case methods::HAPPENS_FIRST_GROUPING:
            return "HAPPENS FIRST METHOD";
        case methods::NONE:
            return "NONE";
    }
    return "";
}

char ufcity::data_grouping_config::get_method_char() const {
    return this->method;
}

ufcity::data_grouping_config::data_grouping_config() = default;

//void ufcity::data_grouping_config::set_missing_data_config(ufcity::missing_data_config *_ms_config) {
//    this->ms_config = _ms_config;
//}
//
//ufcity::remove_outliers_config *ufcity::data_grouping_config::get_remove_outliers_config() {
//    return this->ro_config;
//}
//
//ufcity::missing_data_config *ufcity::data_grouping_config::get_missing_data_config() {
//    return this->ms_config;
//}
//
//void ufcity::data_grouping_config::set_remove_outliers_config(ufcity::remove_outliers_config *_ro_config) {
//    this->ro_config = _ro_config;
//}

long ufcity::data_grouping_config::get_size() const {
    return this->size;
}

long ufcity::data_grouping_config::get_time() const {
    return this->time;
}
//
//ufcity::data_aggregation_config *ufcity::data_grouping_config::get_data_aggregation_config() {
//    return this->da_config;
//}
//
//void ufcity::data_grouping_config::set_data_aggregation_config(ufcity::data_aggregation_config *_da_config) {
//    this->da_config = _da_config;
//}
