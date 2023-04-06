//
// Created by makleyston on 23/09/22.
//

#ifndef UFCITY_MQTT_SUBSCRIBE_H
#define UFCITY_MQTT_SUBSCRIBE_H

#include <string>
#include <iostream>
#include <mqtt/callback.h>
#include <mqtt/async_client.h>
#include "../../in_memory_storage/common/fog_node_address.h"
#include "../lib/mqtt_settings.h"
#include "../../error/error_list.h"
#include <thread>
#include <utility>
#include <unistd.h>
#include "../message_receiver/message_receiver.h"
#include "../../in_memory_storage/message_queue.h"

const int	N_RETRY_ATTEMPTS = 5;

namespace ufcity_mqtt {

    class mqtt_subscribe{
        class action_listener : public virtual mqtt::iaction_listener
        {
            std::string name_;
            void on_failure(const mqtt::token& tok) override {
                std::cout << name_ << " failure";
                if (tok.get_message_id() != 0)
                    std::cout << " for token: [" << tok.get_message_id() << "]" << std::endl;
                std::cout << std::endl;
            }

            void on_success(const mqtt::token& tok) override {
                std::cout << name_ << " success";
                if (tok.get_message_id() != 0)
                    std::cout << " for token: [" << tok.get_message_id() << "]" << std::endl;
                auto top = tok.get_topics();
                if (top && !top->empty())
                    std::cout << "\ttoken topic: '" << (*top)[0] << "', ..." << std::endl;
                std::cout << std::endl;
            }

        public:
            explicit action_listener(std::string  name) : name_(std::move(name)) {}
        };

        class callback : public virtual mqtt::callback,
                         public virtual mqtt::iaction_listener
        {
            int nretry_;
            mqtt::async_client& cli_;
            mqtt::connect_options& connOpts_;
            action_listener subListener_;

            void reconnect() {
                std::this_thread::sleep_for(std::chrono::milliseconds(2500));
                try {
                    connOpts_.set_clean_session(false);
                    cli_.connect(connOpts_, nullptr, *this);
                }
                catch (const mqtt::exception& exc) {
                    std::cerr << "Error: " << exc.what() << std::endl;
                    exit(1);
                }
            }

            // Re-connection failure
            void on_failure(const mqtt::token& tok) override {
                std::cout << "Connection attempt failed" << std::endl;
                if (++nretry_ > N_RETRY_ATTEMPTS)
                    exit(1);
                reconnect();
            }

            // (Re)connection success
            // Either this or connected() can be used for callbacks.
            void on_success(const mqtt::token& tok) override {}

            // (Re)connection success
            void connected(const std::string& cause) override {
                auto topics = mqtt::string_collection::create(ufcity::mqtt_settings::get_topics());
                const std::vector<int> qos { 0, 0, 0};
                cli_.subscribe(topics, qos, nullptr, subListener_);
            }

            void connection_lost(const std::string& cause) override {
                std::cout << "Connection lost" << std::endl;
                if (!cause.empty())
                    std::cout << "cause: " << cause << std::endl;

                std::cout << "Reconnecting..." << std::endl;
                nretry_ = 0;
                reconnect();
            }

            void message_arrived(mqtt::const_message_ptr msg) override {
                ufcity_db::message_queue::get_instance()->push_to_queue_received_messages(msg->get_topic(), msg->to_string());
            }

            void delivery_complete(mqtt::delivery_token_ptr token) override {}

        public:
            callback(mqtt::async_client& cli, mqtt::connect_options& connOpts)
                    : nretry_(0), cli_(cli), connOpts_(connOpts), subListener_("Subscription") {}
        };

    public:
        int subscribe(const std::string& _address, const std::string& _sub_client_id){
            mqtt::async_client cli(_address, _sub_client_id);
            mqtt::connect_options connOpts;
            connOpts.set_clean_session(false);
            callback cb(cli, connOpts);
            cli.set_callback(cb);
            try {
                std::cout << "SUB: Connecting to the MQTT server..." << std::endl;
                cli.connect(connOpts, nullptr, cb);
            }
            catch (const mqtt::exception& exc) {
                std::cerr << "SUB: ERROR: Unable to connect to MQTT server: '"
                          << ufcity::mqtt_settings::get_fog_node_address() << "'" << exc << std::endl;
                return ERROR_SUBSCRIBE;
            }

            while(ufcity_db::message_queue::get_instance()->get_run_state()); /* While alive */
            return 0;
        };
    };
}

#endif //UFCITY_MQTT_SUBSCRIBE_H