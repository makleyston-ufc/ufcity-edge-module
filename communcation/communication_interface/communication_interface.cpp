//
// Created by makleyston on 29/08/22.
//

#include "communication_interface.h"
#include "mqtt_subscribe.h"

namespace ufcity {

    communication_interface::communication_interface() = default;
    communication_interface * communication_interface::instance = nullptr;

    communication_interface *communication_interface::get_instance() {
        if(instance == nullptr){
            instance = new communication_interface();
            return instance;
        }
        return instance;
    }

    void communication_interface::publish_resource_data(const std::string& data) {

    }

    void communication_interface::publish_resource_registration(const std::string& data) {

    }

    void communication_interface::publish_resource_removal(const std::string& data) {

    }

    int communication_interface::subscribe_receive_command() {
        return ufcity_mqtt::subscribe();
    }
} // ufcity
















