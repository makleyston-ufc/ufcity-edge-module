//
// Created by makleyston on 28/04/23.
//

#include <iostream>
#include "missing_data_config.h"
#include "data_aggregation_config.h"
#include "methods.h"

namespace ufcity {
    void ufcity::missing_data_config::set_method(char _method) {
        this->method = _method;
    }

    std::string ufcity::missing_data_config::get_method_str() {
        if(!this->method && this->method=='\0') {
            std::cout << "Method not yet chosen." << std::endl;
            return nullptr;
        }
        switch (this->method) {
            case methods::MEAN_METHOD:
                return "MEAN METHOD";
            case methods::MEDIAN_METHOD:
                return "MEDIAN METHOD";
            case methods::LOCF_METHOD:
                return "LAST OBSERVATION CARRIED FORWARD (LOCF) METHOD";
            case methods::INTERPOLATION_METHOD:
                return "INTERPOLATION METHOD";
            case methods::NOCB_METHOD:
                return "NEXT OBSERVATION CARRIED BACKWARD (NOCB) METHOD";
            case methods::NONE:
                return "NONE";
            case methods::MODE_METHOD:
                return "MODE METHOD";
        }
        return "";
    }

    char ufcity::missing_data_config::get_method_char() {
        return this->method;
    }

    missing_data_config::missing_data_config() {

    }

    missing_data_config::missing_data_config(char _method) {
        this->method = _method;
    }

} // ufcity