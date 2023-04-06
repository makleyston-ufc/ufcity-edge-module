//
// Created by makleyston on 29/08/22.
//

#include "message_receiver.h"
#include "../lib/mqtt_settings.h"
#include "../message_sender/message_sender.h"
#include "../../orchestrator/orchestrator.h"
#include "../communication_interface/mqtt_subscribe.h"
#include <sstream>
#include <iostream>
#include <vector>

namespace ufcity {

    void message_receiver::running_thread_subscribe() {
        auto _address = ufcity::mqtt_settings::get_fog_node_address();
        auto _sub_client_id = ufcity::mqtt_settings::get_sub_client_id();
        /* Subscribing to fog computing. */
        auto * ms = new ufcity_mqtt::mqtt_subscribe();
        auto _error = ms->subscribe(_address, _sub_client_id);
        if(_error != 0)
            std::cout << "Error: " + std::to_string(_error) << std::endl;
    }
} // ufcity