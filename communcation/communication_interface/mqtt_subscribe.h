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

const int	N_RETRY_ATTEMPTS = 5;
//const auto TIMEOUT = std::chrono::seconds(10);

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
//                *this(cli_, connOpts_);
//                cli_.set_callback(*this);
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
                cli_.subscribe(ufcity::get_topic_to_receive_commands(), ufcity::QOS, nullptr, subListener_);
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
                ufcity::message_receiver::get_instance()->receive_message(msg->get_topic(), msg->to_string());
            }

            void delivery_complete(mqtt::delivery_token_ptr token) override {}

        public:
            callback(mqtt::async_client& cli, mqtt::connect_options& connOpts)
                    : nretry_(0), cli_(cli), connOpts_(connOpts), subListener_("Subscription") {}
        };

    public:
        void subscribe(const std::string& _address, const std::string& _sub_client_id){
            mqtt::async_client cli(_address, _sub_client_id);

            mqtt::connect_options connOpts;
            connOpts.set_clean_session(false);

            callback cb(cli, connOpts);
            cli.set_callback(cb);

            try {
                std::cout << "SUB: Connecting to the MQTT server..." << std::endl;
                cli.connect(connOpts, nullptr, cb);
//                std::cout << "Ok :SUB" << std::endl;
            }
            catch (const mqtt::exception& exc) {
                std::cerr << "SUB: ERROR: Unable to connect to MQTT server: '"
                          << ufcity::get_fog_node_address() << "'" << exc << std::endl;
//                return 1; //TODO put code error correctly
            }
            //TODO esse while é para ler as mensagens que chegam. Caso contrário, a thread funcionará, porém não será visível, pois outras atividades em paralelo tornarão visíveis.
            //TODO Fazer um mecanismo para destruir essa thread quando o programa principal for finalizado.
            while(true);
//            while (std::tolower(std::cin.get()) != 'q');
//            try {
//                std::cout << "\nDisconnecting from the MQTT server..." << std::flush;
//                cli.disconnect()->wait();
//                std::cout << "OK" << std::endl;
//            }
//            catch (const mqtt::exception& exc) {
//                std::cerr << exc << std::endl;
//                return;
//            }
        }
    };

//    class mqtt_publish {
//
//    public:
//        static int publish(const std::string &_address, const std::string &_pub_client_id, const std::string _message) {
//            mqtt::async_client cli(_address, _pub_client_id);
//
//            int QOS = 0;
//            //TODO alterar o TOPIC
//            std::string TOPIC = "commands_received/a/b";
//
//            auto connOpts = mqtt::connect_options_builder()
//                    .clean_session()
//                    .will(mqtt::message(TOPIC, "", QOS))
//                    .finalize();
//
//            try {
//                if(!cli.is_connected()) {
//                    std::cout << "\nConnecting..." << std::flush;
//                    mqtt::token_ptr conntok = cli.connect(connOpts);
////                std::cout << "Waiting for the connection..." << std::flush;
//                    conntok->wait();
//                    std::cout << "  OK" << std::endl;
//                }
//
//                std::cout << "Sending message..." << std::flush;
//                mqtt::message_ptr pubmsg = mqtt::make_message(TOPIC, _message);
//                pubmsg->set_qos(QOS);
//                cli.publish(pubmsg)->wait_for(TIMEOUT);
//                std::cout << "  OK" << std::endl;
//
//                // Disconnect
////                std::cout << "Disconnecting..." << std::flush;
////                cli.disconnect()->wait();
////                std::cout << "  OK" << std::endl;
//            }
//            catch (const mqtt::exception &exc) {
//                std::cerr << exc.what() << std::endl;
//                return 1;
//            }
//
//            return 0;
//        }
//    };
}

#endif //UFCITY_MQTT_SUBSCRIBE_H