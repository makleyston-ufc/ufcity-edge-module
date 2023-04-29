//
// Created by makleyston on 28/04/23.
//

#include <iostream>
#include "data_aggregation_config.h"
#include "methods.h"

void ufcity::data_aggregation_config::set_method(char _method) {
    this->method = _method;
}

void ufcity::data_aggregation_config::set_size(int _size) {
    this->size = _size;
}

void ufcity::data_aggregation_config::set_time(int _sec) {
    this->time = _sec;
}

std::string ufcity::data_aggregation_config::get_method_str() {
    if(!this->method && this->method=='\0') {
        std::cout << "Method not yet chosen." << std::endl;
        return nullptr;
    }
    switch (this->method) {
        case methods::FIXED_TIME:
            return "TIME METHOD";
        case methods::FIXED_SIZE:
            return "SIZE METHOD";
        case methods::HAPPENS_FIRST:
            return "HAPPENS FIRST METHOD";
        case methods::NONE:
            return "NONE";
    }
    return "";
}

char ufcity::data_aggregation_config::get_method_char() {
    return this->method;
}

ufcity::data_aggregation_config::data_aggregation_config() {

}

void ufcity::data_aggregation_config::set_missing_data_config(ufcity::missing_data_config *_ms_config) {
    this->ms_config = _ms_config;
}

ufcity::remove_outliers_config *ufcity::data_aggregation_config::get_remove_outliers_config() {
    return this->ro_config;
}

ufcity::missing_data_config *ufcity::data_aggregation_config::get_missing_data_config() {
    return this->ms_config;
}

void ufcity::data_aggregation_config::set_remove_outliers_config(ufcity::remove_outliers_config *_ro_config) {
    this->ro_config = _ro_config;
}
