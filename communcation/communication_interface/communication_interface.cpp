//
// Created by makleyston on 29/08/22.
//

#include "communication_interface.h"
#include "mqtt_subscribe.h"
#include "mqtt_publish.h"

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
        std::string _address = ufcity::get_fog_node_address();
        std::string _pub_client_id = ufcity::get_pub_client_id();

        auto * mp = new ufcity_mqtt::mqtt_publish();
        auto r= mp->publish(_address, _pub_client_id, data);
        if(r == 1)
            std::cout << "Error: message not published to MQTT broker!" << std::endl;
        else
            std::cout << "Message published to MQTT broker successfully!" << std::endl;
    }

    void communication_interface::publish_resource_registration(const std::string& data) {
//TODO
    }

    void communication_interface::publish_resource_removal(const std::string& data) {
//TODO
    }

    int communication_interface::subscribe_receive_command() {
        std::string _address = ufcity::get_fog_node_address();
        std::string _sub_client_id = ufcity::get_sub_client_id();

        auto * ms = new ufcity_mqtt::mqtt_subscribe();
        ms->subscribe(_address, _sub_client_id);

        return 0;
    }

} // ufcity
















