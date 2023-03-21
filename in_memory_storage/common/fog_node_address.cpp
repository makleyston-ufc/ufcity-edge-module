//
// Created by makleyston on 23/09/22.
//

#include "fog_node_address.h"

#include <utility>

namespace ufcity_db {

    fog_node_address::fog_node_address() = default;

    fog_node_address* fog_node_address::instance = nullptr;

    fog_node_address::~fog_node_address() = default;

    fog_node_address *fog_node_address::get_instance() {
        if (instance == nullptr){
            instance = new fog_node_address();
        }
        return instance;
    }

    void fog_node_address::set_fog_node_address(std::string _address) {
        this->address = std::move(_address);
    }

    std::string fog_node_address::get_fog_node_address() {
        return this->address;
    }
} // ufcity_db