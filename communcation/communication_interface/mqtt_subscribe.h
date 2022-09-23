//
// Created by makleyston on 23/09/22.
//

#include <string>
#include <iostream>
#include <mqtt/callback.h>
#include <mqtt/async_client.h>
#include "../../in_memory_storage/common/fog_node_address.h"
#include "../lib/mqtt_settings.h"
#include "../../error/error_list.h"

namespace ufcity_mqtt {

    class callback : public virtual mqtt::callback {
    public:
        void connection_lost(const std::string &cause) override {
            std::cout << "\nConnection lost" << std::endl;
            if (!cause.empty())
                std::cout << "\tcause: " << cause << std::endl;
        }

        void delivery_complete(mqtt::delivery_token_ptr tok) override {
            std::cout << "\tDelivery complete for token: "
                      << (tok ? tok->get_message_id() : -1) << std::endl;
        }
    };

    int subscribe() {
        std::string _address = ufcity::get_fog_node_address();
        std::cout << "Initializing for server '" << _address << "'..." << std::endl;
        mqtt::async_client cli(_address, ufcity::get_sub_client_id());

        auto connOpts = mqtt::connect_options_builder()
                .clean_session(false)
                .finalize();

        try {
            // Start consumer before connecting to make sure to not miss messages
            cli.start_consuming();

            // Connect to the server
            std::cout << "Connecting to the MQTT server..." << std::flush;
            auto tok = cli.connect(connOpts);

            // Getting the connect response will block waiting for the
            // connection to complete.
            auto rsp = tok->get_connect_response();

            // If there is no session present, then we need to subscribe, but if
            // there is a session, then the server remembers us and our
            // subscriptions.
            if (!rsp.is_session_present())
                cli.subscribe(ufcity::get_topic_receive_commands(), ufcity::QOS)->wait();

            std::cout << "OK" << std::endl;

            // Consume messages
            // This just exits if the client is disconnected.
            // (See some other examples for auto or manual reconnect)
            std::cout << "Waiting for messages on topic: '" << ufcity::get_topic_receive_commands() << "'" << std::endl;
            while (true) {
                auto msg = cli.consume_message();
                if (!msg) break;
                std::cout << msg->get_topic() << ": " << msg->to_string() << std::endl;
            }

            // If we're here, the client was almost certainly disconnected.
            // But we check, just to make sure.
            if (cli.is_connected()) {
                std::cout << "\nShutting down and disconnecting from the MQTT server..." << std::flush;
                cli.unsubscribe(ufcity::get_topic_receive_commands())->wait();
                cli.stop_consuming();
                cli.disconnect()->wait();
                std::cout << "OK" << std::endl;
            } else {
                std::cout << "\nClient was disconnected" << std::endl;
            }
        }
        catch (const mqtt::exception &exc) {
            std::cerr << "\n  " << exc << std::endl;
            return ERROR_SUBSCRIBE;
        }
        return  0;
    }
}