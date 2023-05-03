//
// Created by makleyston on 02/05/23.
//

#include "service_data.h"

namespace ufcity {
    service_data::service_data(std::string _tag, std::string _value) {
        this->tag = _tag;
        this->value = _value;
    }

    std::string service_data::get_tag() {
        return this->tag;
    }

    std::string service_data::get_value() {
        return this->value;
    }
} // ufcity