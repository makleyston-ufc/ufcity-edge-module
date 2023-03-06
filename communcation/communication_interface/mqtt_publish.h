//
// Created by makleyston on 27/09/22.
//

#ifndef UFCITY_MQTT_PUBLISH_H
#define UFCITY_MQTT_PUBLISH_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <thread>
#include <atomic>
#include <chrono>
#include <cstring>
#include "mqtt/async_client.h"
#include "../../in_memory_storage/common/fog_node_address.h"
#include "../lib/mqtt_settings.h"
const auto TIMEOUT = std::chrono::seconds(10);

namespace ufcity_mqtt{
    int publish(std::string _topic, std::string _data){

        std::string _address = ufcity::get_fog_node_address();
        std::string _pub_client_id = ufcity::get_pub_client_id();

        std::cout << "Initializing for server '" << _address << "'..." << std::endl;
        mqtt::async_client client(_address, _pub_client_id);

        auto connOpts = mqtt::connect_options_builder()
                .clean_session()
                .finalize();

        std::cout << "  ...OK" << std::endl;

        try {
            std::cout << "Connecting..." << std::endl;
            mqtt::token_ptr conntok = client.connect(connOpts);
            std::cout << "Waiting for the connection...";
            conntok->wait();
            std::cout << "  OK" << std::endl;

            std::cout << "Sending message...";
            mqtt::message_ptr pubmsg = mqtt::make_message(_topic, _data);
            pubmsg->set_qos(ufcity::QOS);
            client.publish(pubmsg)->wait_for(TIMEOUT);
            std::cout << "  OK" << std::endl;

            // TODO
            // fazer a desconexão apenas quando não tiver nada para enviar (e.g., dados de recursos, registros de recursos, remoção de recursos, etc.)
            // Disconnect
            std::cout << "Disconnecting...";
            client.disconnect()->wait();
            std::cout << "  OK" << std::endl;
        }
        catch (const mqtt::exception& exc) {
            std::cerr << exc.what() << std::endl;
            return 1;
        }
        return 0;
    }
}
#endif //UFCITY_MQTT_PUBLISH_H
