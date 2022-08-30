//
// Created by makleyston on 29/08/22.
//

#include "north_interface.h"

#include <utility>

namespace ufcity {
    void north_interface::set_fog_node_address(std::string address) {
        this->fog_node_address = std::move(address);
    }

    std::string north_interface::get_fog_node_address() {
        return this->fog_node_address;
    }

    north_interface::north_interface() = default;
    north_interface * north_interface::instance = nullptr;

    north_interface *north_interface::get_instance() {
        if(instance == nullptr){
            instance = new north_interface();
            return instance;
        }
        return instance;
    }

    void north_interface::publish_resource_data(const std::string& data) {

    }

    void north_interface::publish_resource_registration(const std::string& data) {

    }

    void north_interface::publish_resource_removal(const std::string& data) {

    }

    void north_interface::receive_command() {

    }
} // ufcity