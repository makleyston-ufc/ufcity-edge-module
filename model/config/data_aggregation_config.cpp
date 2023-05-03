//
// Created by makleyston on 03/05/23.
//

#include <iostream>
#include "data_aggregation_config.h"
#include "methods.h"

namespace ufcity {
    data_aggregation_config::data_aggregation_config() {}

    data_aggregation_config::data_aggregation_config(char _method) {
        this->method = _method;
    }

    void data_aggregation_config::set_method(char _method) {
        this->method = _method;
    }

    char data_aggregation_config::get_method_char() const {
        return this->method;
    }

    std::string data_aggregation_config::get_method_str() const {
        if(!this->method && this->method=='\0') {
            std::cout << "Method not yet chosen." << std::endl;
            return nullptr;
        }
        switch (this->method) {
            case methods::MAX_AGGREGATION_METHOD:
                return "MAX VALUE";
            case methods::MEAN_AGGREGATION_METHOD:
                return "MEAN VALUE";
            case methods::MEDIAN_AGGREGATION_METHOD:
                return "MEDIAN VALUE";
            case methods::MIN_AGGREGATION_METHOD:
                return "MIN VALUE";
            case methods::NONE:
                return "NONE";
        }
        return "";
    }
} // ufcity