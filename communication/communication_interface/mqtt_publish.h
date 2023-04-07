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
    class mqtt_publish{
    private:

    public:
        static int publish(const std::string &_address, const std::string &_pub_client_id, const std::string& _message, const std::string& _topic) {
            mqtt::async_client cli(_address, _pub_client_id);
            int QOS = 0;
            auto connOpts = mqtt::connect_options_builder()
                    .clean_session()
                    .will(mqtt::message(_topic, "", QOS))
                    .finalize();
            try {
                if(!cli.is_connected()) {
                    mqtt::token_ptr conntok = cli.connect(connOpts);
                    conntok->wait();
                }
                mqtt::message_ptr pubmsg = mqtt::make_message(_topic, _message);
                pubmsg->set_qos(QOS);
                cli.publish(pubmsg)->wait_for(TIMEOUT);
                // Disconnect
                cli.disconnect()->wait();
            }
            catch (const mqtt::exception &exc) {
                std::cerr << exc.what() << std::endl;
                return 1;
            }
            return 0;
        }
    };
}

#endif //UFCITY_MQTT_PUBLISH_H
